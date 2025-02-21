// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class RespawnPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_RESPAWNPACKET
public:
    class RespawnPacket& operator=(class RespawnPacket const&) = delete;
    RespawnPacket(class RespawnPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~RespawnPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    /*
    inline  ~RespawnPacket(){
         (RespawnPacket::*rv)();
        *((void**)&rv) = dlsym("??1RespawnPacket@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI RespawnPacket(class Vec3 const&, enum PlayerRespawnState const&);
    MCAPI RespawnPacket();

protected:

private:

};