#include "APIHelp.h"
#include "APIHelp.h"
#include "ServerAPI.h"
#include <ServerAPI.h>
#include "McAPI.h"
#include <MC/ServerNetworkHandler.hpp>


Local<Value> McClass::setMotd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try{
        return Boolean::newBoolean(LL::setServerMotd(args[0].asString().toString()));
    }
    CATCH("Fail in SetServerMotd!")
}

Local<Value> McClass::crashBDS(const Arguments& args)               //===========???
{
    char* c = new char[10];
    delete c;
    delete c;
    return Boolean::newBoolean(true);
}