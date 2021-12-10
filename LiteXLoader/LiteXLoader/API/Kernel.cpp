#include <Global.hpp>
#include "Kernel.h"
#include <MC/Level.hpp>
#include <MC/Actor.hpp>
#include <MC/Player.hpp>
#include <MC/Minecraft.hpp>
#include <MC/Scoreboard.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <HookAPI.h>
#include <bitset>
#include <Utils/FileHelper.h>
#include <Utils/StringHelper.h>
#include <Utils/NetworkHelper.h>
#include <third-party/httplib/httplib.h>
#include <Engine/LocalShareData.h>
#include <filesystem>
#include <Utils.h>
class Mob;

bool Raw_HasContainer(FloatVec4 pos)
{
	return Raw_GetContainer(pos) != nullptr;
}

class DropperBlockActor;
Container* Raw_GetContainer(FloatVec4 pos)
{
	Vec3 vec{ pos.x, pos.y, pos.z };

	// This function didn't use 'this' pointer
	Container* container = SymCall("?_getContainerAt@DropperBlockActor@@AEAAPEAVContainer@@AEAVBlockSource@@AEBVVec3@@@Z",
		Container*, DropperBlockActor*, BlockSource*, Vec3*)(nullptr, Level::getBlockSource(pos.dim), &vec);

	return container;
}

Player* Raw_GetPlayerByUniqueId(struct ActorUniqueID id)
{
	return SymCall("?getPlayer@Level@@UEBAPEAVPlayer@@UActorUniqueID@@@Z", Player*, ActorUniqueID)(id);
}

IntVec4 Raw_GetEntityBlockPos(Actor* actor)
{
	auto pos = actor->getPosition();
	return { (int)pos.x, (int)(pos.y + 0.5), (int)pos.z, actor->getDimensionId() };
}

bool Raw_RefreshItems(Actor* ac)
{
	SymCall("?sendInventory@Mob@@UEAAX_N@Z", void, Mob*)((Mob*)ac);
	std::bitset<4> bits("1111");
	SymCall("?sendArmor@Mob@@UEAAXAEBV?$bitset@$03@std@@@Z", void, Mob*, std::bitset<4>*)((Mob*)ac, &bits);
	return true;
}

bool Raw_SetOnFire(Actor* actor, int time) {
	SymCall("?setOnFire@Actor@@UEAAXH@Z", void,
		Actor*, int)(actor, time);
	return true;
}

HANDLE GetHANDLEfromFstream(std::fstream& fs)
{
	auto cfile = ::_fileno(GetFILEfromFstream(fs));
	return (HANDLE)::_get_osfhandle(cfile);
}

vector<string> Raw_GetFilesList(const std::string& path)
{
	std::filesystem::directory_entry dir(path);
	if (!dir.is_directory())
		return {};

	vector<string> list;
	std::filesystem::directory_iterator deps(path);
	for (auto& i : deps)
	{
		list.push_back(i.path().filename().u8string());
	}
	return list;
}

bool Raw_AutoCreateDirs(const string path)
{
	std::error_code ec;
	return std::filesystem::create_directories(std::filesystem::path(path).remove_filename(), ec);
}

bool Raw_IsPlayerValid(Player* player)
{
	auto playerList = Level::getAllPlayers();
	for (auto p : playerList)
		if (p == player)
			return true;
	return false;
}

bool Raw_HttpPost(const string& url, const string& data, const string& type, std::function<void(int, string)> callback)
{
	string host, path;
	SplitHttpUrl(url, host, path);
	httplib::Client* cli = new httplib::Client(host.c_str());
	if (!cli->is_valid())
	{
		delete cli;
		return false;
	}
	pool.enqueue([cli, data{ std::move(data) }, type{ std::move(type) }, callback{ std::move(callback) },
		path{ std::move(path) }]()
	{
		auto response = cli->Post(path.c_str(), data, type.c_str());
		delete cli;
		if (!response)
			callback(-1, "");
		else
			callback(response->status, response->body);
	});
	return true;
}

bool Raw_SetSidebar(Player* player, std::string title, const std::vector<std::pair<std::string, int>>& data, int sortOrder)
{
	player->sendSetDisplayObjectivePacket(title, "FakeScoreObj", (char)sortOrder);

	vector<ScorePacketInfo> info;
	for (auto& x : data)
	{
		const ScoreboardId &id = ::Global<Scoreboard>->createScoreboardId(x.first);
		ScorePacketInfo i((ScoreboardId*) & id, x.second, x.first);
		info.emplace_back(i);
	}

	player->sendSetScorePacket(0, info);
	player->sendSetDisplayObjectivePacket(title, "FakeScoreObj", (char)sortOrder);
	return true;
}

bool Raw_RemoveSidebar(Player* player)
{
	player->sendSetDisplayObjectivePacket("", "", (char)0);
	return true;
}

#define READ_BUFFER_SIZE 4096

bool Raw_NewProcess(const std::string& cmd, std::function<void(int, std::string)> callback, int timeLimit)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return false;
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(STARTUPINFO);
	GetStartupInfoW(&si);
	si.hStdOutput = si.hStdError = hWrite;
	si.dwFlags = STARTF_USESTDHANDLES;

	auto wCmd = str2cwstr(cmd);
	if (!CreateProcessW(NULL, wCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		delete[] wCmd;
		return false;
	}
	CloseHandle(hWrite);
	CloseHandle(pi.hThread);

	pool.enqueue([hRead{ std::move(hRead) }, hProcess{ std::move(pi.hProcess) },
		callback{ std::move(callback) }, timeLimit{ std::move(timeLimit) }, wCmd{ std::move(wCmd) }]()
	{
		if (timeLimit == -1)
			WaitForSingleObject(hProcess, INFINITE);
		else
		{
			WaitForSingleObject(hProcess, timeLimit);
			TerminateProcess(hProcess, -1);
		}
		char buffer[READ_BUFFER_SIZE];
		string strOutput;
		DWORD bytesRead, exitCode;

		delete[] wCmd;
		GetExitCodeProcess(hProcess, &exitCode);
		while (true)
		{
			ZeroMemory(buffer, READ_BUFFER_SIZE);
			if (!ReadFile(hRead, buffer, READ_BUFFER_SIZE, &bytesRead, NULL))
				break;
			strOutput.append(buffer, bytesRead);
		}
		CloseHandle(hRead);
		CloseHandle(hProcess);

		callback((int)exitCode, strOutput);
	});

	return true;
}

bool Raw_SetServerMotd(const std::string& motd)
{
	ServerNetworkHandler* snh = ::Global<Minecraft>->getServerNetworkHandler();
	if (!snh)
		return false;

	snh->allowIncomingConnections(motd, true);
	return true;
}
