#pragma once
#include <ScriptX/ScriptX.h>
using namespace script;

#include <Global.hpp>
#include <Engine/EngineOwnData.h>
#include <MC/Level.hpp>
#include <string>
#include <vector>
#include <exception>

// 方便提取类型
#define toStr() asString().toString()
#define toInt() asNumber().toInt32()

// 实例类类型检查
template <typename T>
bool inline IsInstanceOf(Local<Value> v)
{
    return EngineScope::currentEngine()->isInstanceOf<T>(v);
}

// 至少COUNT个参数
#define CHECK_ARGS_COUNT(ARGS,COUNT) \
    if(ARGS.size()<COUNT) \
    { \
        ERROR("Too Few arguments!"); \
        ERROR(std::string("In API: ") + __FUNCTION__); \
        ERROR("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    }

// 检查是否TYPE类型 
#define CHECK_ARG_TYPE(ARG,TYPE) \
    if(ARG.getKind() != TYPE) \
    { \
        Error("Wrong type of argument!"); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    }

// 截获引擎异常
#define CATCH(LOG) \
    catch(const Exception& e) \
    { \
        Error(LOG##"\n"); Error(e); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    } \
    catch(const std::exception &e) \
    { \
        Error("C++ Uncaught Exception Detected!"); \
        Error(e.what()); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    } \
    catch(const seh_exception &e) \
    { \
        Error("SEH Uncaught Exception Detected!"); \
        Error(e.what()); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    } \
    catch(...) \
    { \
        Error("Uncaught Exception Detected!"); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return Local<Value>(); \
    }

// 至少COUNT个参数_Constructor
#define CHECK_ARGS_COUNT_C(ARGS,COUNT) \
    if(ARGS.size()<COUNT) \
    { \
        Error("Too Few arguments!"); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    }

// 检查是否TYPE类型_Constructor
#define CHECK_ARG_TYPE_C(ARG,TYPE) \
    if(ARG.getKind() != TYPE) \
    { \
        Error("Wrong type of argument!"); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    }

// 截获引擎异常_Constructor
#define CATCH_C(LOG) \
    catch(const Exception& e) \
    { \
        Error(LOG##"\n"); Error(e); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    } \
    catch(const std::exception &e) \
    { \
        Error("C++ Uncaught Exception Detected!"); \
        Error(e.what()); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    } \
    catch(const seh_exception &e) \
    { \
        Error("SEH Uncaught Exception Detected!"); \
        Error(e.what()); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    } \
    catch(...) \
    { \
        Error("Uncaught Exception Detected!"); \
        Error(std::string("In API: ") + __FUNCTION__); \
        Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
        return nullptr; \
    }


// 判断是否为浮点数
bool CheckIsFloat(const Local<Value>& num);

// 序列化
void PrintValue(std::ostream &out, Local<Value> v);
std::string ValueToString(Local<Value> v);

// Json 序列化 反序列化
Local<Value> JsonToValue(std::string jsonStr);
Local<Value> JsonToValue(fifo_json j);
std::string ValueToJson(Local<Value> v,int formatIndent = -1);