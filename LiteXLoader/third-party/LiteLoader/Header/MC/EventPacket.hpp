// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "MinecraftEventing.hpp"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EventPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EVENTPACKET
public:
    class EventPacket& operator=(class EventPacket const&) = delete;
    EventPacket(class EventPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~EventPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    /*
    inline  ~EventPacket(){
         (EventPacket::*rv)();
        *((void**)&rv) = dlsym("??1EventPacket@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI EventPacket(class Player const&, std::string const&);
    MCAPI EventPacket(class Player const&, std::string const&, int);
    MCAPI EventPacket(class Player const&, enum MovementEventType, float, float, float, float, float);
    MCAPI EventPacket(class Player const*, struct EventPacket::Data const&);
    MCAPI EventPacket(class Player const*, std::string const&, int, int, std::string const&);
    MCAPI EventPacket(class Player const*, class Raid const&, bool);
    MCAPI EventPacket(class Player const*, short, unsigned int, short);
    MCAPI EventPacket(class Player const*, int, int, int, int, int);
    MCAPI EventPacket(class Player const*, int, int, enum ActorDamageCause, bool);
    MCAPI EventPacket(class Player const*, int, class gsl::not_null<class Actor const* >);
    MCAPI EventPacket(class Player const*, class Actor const*, class gsl::not_null<class Mob const* >, enum ActorDamageCause, std::string, int, enum ActorType);
    MCAPI EventPacket(class Player const*, class Actor const*, class gsl::not_null<class Mob const* >, enum ActorDamageCause, enum ActorType);
    MCAPI EventPacket(class Player const*, class AutomaticID<class Dimension, int>, class AutomaticID<class Dimension, int>);
    MCAPI EventPacket(class Player const*, class AutomaticID<class Dimension, int>);
    MCAPI EventPacket(class Player const*, class gsl::not_null<class Actor const* >, enum MinecraftEventing::InteractionType);
    MCAPI EventPacket(class Player const*, class gsl::not_null<class Mob const* >);
    MCAPI EventPacket(class Player const*, enum MinecraftEventing::AchievementIds, bool);
    MCAPI EventPacket(class Player const*, enum EventPacket::AgentResult, std::string const&, std::string const&, std::string const&);
    MCAPI EventPacket(class Player const*, enum EventPacket::AgentResult, std::string const&, std::string const&, int);
    MCAPI EventPacket(class Player const*, bool, class Actor const*, class gsl::not_null<class Mob const* >, enum ActorDamageCause);
    MCAPI EventPacket();
    MCAPI class EventPacket& operator=(class EventPacket&&);

protected:

private:

};