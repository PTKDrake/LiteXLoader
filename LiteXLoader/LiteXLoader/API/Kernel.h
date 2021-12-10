#pragma once
#include <Global.hpp>
#include <minwindef.h>
#include <fstream>
class Container;
class Player;

bool Raw_HasContainer(FloatVec4 pos);
Container* Raw_GetContainer(FloatVec4 pos);
Player* Raw_GetPlayerByUniqueId(struct ActorUniqueID id);
IntVec4 Raw_GetEntityBlockPos(Actor* actor);
bool Raw_RefreshItems(Actor* ac);
bool Raw_SetOnFire(Actor* actor, int time);
HANDLE GetHANDLEfromFstream(std::fstream& fs);
vector<string> Raw_GetFilesList(const std::string& path);
bool Raw_IsPlayerValid(Player* player);
bool Raw_AutoCreateDirs(const string path);
bool Raw_HttpPost(const string& url, const string& data, const string& type, std::function<void(int, string)> callback);
bool Raw_SetSidebar(Player* player, std::string title, const std::vector<std::pair<std::string, int>>& data, int sortOrder);
bool Raw_RemoveSidebar(Player* player);
bool Raw_NewProcess(const std::string& cmd, std::function<void(int, std::string)> callback, int timeLimit);
bool Raw_SetServerMotd(const std::string& motd);

class Vec2
{
public:
	int x, z;
};