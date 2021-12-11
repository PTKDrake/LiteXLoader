#include "APIHelp.h"
#include "GuiAPI.h"
#include "PlayerAPI.h"
#include "McAPI.h"
#include <Engine/GlobalShareData.h>
#include <Engine/LocalShareData.h>
#include <Engine/EngineOwnData.h>
#include <Engine/LoaderHelper.h>
#include <MC/Player.hpp>
#include <iostream>
using namespace script;
using namespace std;
using namespace Form;

//////////////////// Class Definition ////////////////////

ClassDefine<SimpleFormClass> SimpleFormClassBuilder =
    defineClass<SimpleFormClass>("LXL_SimpleForm")
        .constructor(nullptr)
        .instanceFunction("setTitle", &SimpleFormClass::setTitle)
        .instanceFunction("setContent", &SimpleFormClass::setContent)
        .instanceFunction("addButton", &SimpleFormClass::addButton)
        .build();

ClassDefine<CustomFormClass> CustomFormClassBuilder =
    defineClass<CustomFormClass>("LXL_CustomForm")
        .constructor(nullptr)
        .instanceFunction("setTitle", &CustomFormClass::setTitle)
        .instanceFunction("addLabel", &CustomFormClass::addLabel)
        .instanceFunction("addInput", &CustomFormClass::addInput)
        .instanceFunction("addSwitch", &CustomFormClass::addSwitch)
        .instanceFunction("addDropdown", &CustomFormClass::addDropdown)
        .instanceFunction("addSlider", &CustomFormClass::addSlider)
        .instanceFunction("addStepSlider", &CustomFormClass::addStepSlider)
        .build();

//////////////////// Simple Form ////////////////////

SimpleFormClass::SimpleFormClass()
    :ScriptClass(ScriptClass::ConstructFromCpp<SimpleFormClass>{}),form("","")
{ }

//生成函数
Local<Object> SimpleFormClass::newForm()
{
    auto newp = new SimpleFormClass();
    return newp->getScriptObject();
}

Form::SimpleForm* SimpleFormClass::extract(Local<Value> v)
{
    if (EngineScope::currentEngine()->isInstanceOf<SimpleFormClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<SimpleFormClass>(v)->get();
    else
        return nullptr;
}

bool SimpleFormClass::sendForm(Form::SimpleForm* form, Player* player, script::Local<Function> &callback)
{
    script::Global<Function> callbackFunc{ callback };

    return form->sendTo((ServerPlayer*)player,
        [id{ player->getUniqueID() }, engine{ EngineScope::currentEngine() }, callback{ std::move(callbackFunc) }]
        (int chosen)
        {
            Player* pl = Level::getPlayer(id);
            if (!pl)
                return;

            EngineScope scope(engine);
            try
            {
                callback.get().call({}, PlayerClass::newPlayer(pl), Number::newNumber(chosen));
            }
            catch (const Exception& e)
            {
                Error("Fail in form callback!");
                Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName);
                Error(e);
            }
        });
}

//成员函数
Local<Value> SimpleFormClass::setTitle(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        form.title = args[0].toStr();
        return this->getScriptObject();
    }
    CATCH("Fail in setTitle!")
}

Local<Value> SimpleFormClass::setContent(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        form.content = args[0].toStr();
        return this->getScriptObject();
    }
    CATCH("Fail in setTitle!")
}

Local<Value> SimpleFormClass::addButton(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    if (args.size() >= 2)
        CHECK_ARG_TYPE(args[1], ValueKind::kString);

    try {
        string image = args.size() >= 2 ? args[1].toStr() : "";
        form.append(Button(args[0].toStr(), image));
        return this->getScriptObject();
    }
    CATCH("Fail in addButton!")
}



//////////////////// Custom Form ////////////////////

CustomFormClass::CustomFormClass()
    :ScriptClass(ScriptClass::ConstructFromCpp<CustomFormClass>{}),form("")
{ }


//生成函数
Local<Object> CustomFormClass::newForm()
{
    auto newp = new CustomFormClass();
    return newp->getScriptObject();
}

CustomForm* CustomFormClass::extract(Local<Value> v)
{
    if(EngineScope::currentEngine()->isInstanceOf<CustomFormClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<CustomFormClass>(v)->get();
    else
        return nullptr;
}

vector<string> CustomFormResultToString(const std::map<string, std::shared_ptr<CustomFormElement>>& data, Local<Array> &arr)
{
    vector<string> res;
    for (auto& [k, v] : data)
    {
        switch (v->getType())
        {
        case CustomFormElement::Type::Label:
            arr.add(Local<Value>());
            break;
        case CustomFormElement::Type::Input:
            arr.add(String::newString(std::dynamic_pointer_cast<Input>(v)->getData()));
            break;
        case CustomFormElement::Type::Toggle:
            arr.add(Boolean::newBoolean(std::dynamic_pointer_cast<Toggle>(v)->getData()));
            break;
        case CustomFormElement::Type::Dropdown:
            arr.add(Number::newNumber(std::dynamic_pointer_cast<Dropdown>(v)->getData()));
            break;
        case CustomFormElement::Type::Slider:
            arr.add(Number::newNumber(std::dynamic_pointer_cast<Slider>(v)->getData()));
            break;
        case CustomFormElement::Type::StepSlider:
            arr.add(Number::newNumber(std::dynamic_pointer_cast<StepSlider>(v)->getData()));
            break;
        }
    }
}

//成员函数
bool CustomFormClass::sendForm(Form::CustomForm* form, Player* player, script::Local<Function>& callback)
{
    script::Global<Function> callbackFunc{ callback };

    return form->sendTo((ServerPlayer*)player,
        [id{ player->getUniqueID() }, engine{ EngineScope::currentEngine() }, callback{ std::move(callbackFunc) }]
    (const std::map<string, std::shared_ptr<CustomFormElement>>& data)
    {
        Player* pl = Level::getPlayer(id);
        if (!pl)
            return;

        EngineScope scope(engine);
        try
        {
            Local<Array> arr = Array::newArray();
            CustomFormResultToString(data, arr);        //========================= Change =========================
            callback.get().call({}, PlayerClass::newPlayer(pl), arr);
        }
        catch (const Exception& e)
        {
            Error("Fail in form callback!");
            Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName);
            Error(e);
        }
    });
}

Local<Value> CustomFormClass::setTitle(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try{
        form.title = args[0].toStr();
        return this->getScriptObject();
    }
    CATCH("Fail in setTitle!")
}

Local<Value> CustomFormClass::addLabel(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try{
        form.append(Label(args[0].toStr(), args[0].toStr()));
        return this->getScriptObject();
    }
    CATCH("Fail in addLabel!")
}

Local<Value> CustomFormClass::addInput(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)
    if(args.size() >= 2)
        CHECK_ARG_TYPE(args[1],ValueKind::kString);
    if(args.size() >= 3)
        CHECK_ARG_TYPE(args[2],ValueKind::kString);

    try{
        string placeholder = args.size() >= 2 ? args[1].toStr() : "";
        string def = args.size() >= 3 ? args[2].toStr() : "";
        
        form.append(Input(args[0].toStr(), args[0].toStr(), placeholder, def));
        return this->getScriptObject();
    }
    CATCH("Fail in addInput!")
}

Local<Value> CustomFormClass::addSwitch(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)
    if(args.size() >= 2)
        CHECK_ARG_TYPE(args[1],ValueKind::kBoolean);

    try{
        bool def = args.size() >= 2 ? args[1].asBoolean().value() : false;
        
        form.append(Toggle(args[0].toStr(), args[0].toStr(), def));
        return this->getScriptObject();
    }
    CATCH("Fail in addSwitch!")
}

Local<Value> CustomFormClass::addDropdown(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,2)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)
    CHECK_ARG_TYPE(args[1],ValueKind::kArray);
    if(args.size() >= 3)
        CHECK_ARG_TYPE(args[2],ValueKind::kNumber);

    try{
        auto optionsArr = args[1].asArray();
        vector<string> options;
        for (int i = 0; i < optionsArr.size(); ++i)
            options.push_back(optionsArr.get(i).toStr());

        int def = args.size() >= 3 ? args[2].asNumber().toInt32() : 0;
        
        form.append(Dropdown(args[0].toStr(), args[0].toStr(), options, def));
        return this->getScriptObject();
    }
    CATCH("Fail in addDropdown!")
}

Local<Value> CustomFormClass::addSlider(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,3)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)
    CHECK_ARG_TYPE(args[1],ValueKind::kNumber);
    CHECK_ARG_TYPE(args[2],ValueKind::kNumber);
    if(args.size() >= 4)
        CHECK_ARG_TYPE(args[3],ValueKind::kNumber);
    if(args.size() >= 5)
        CHECK_ARG_TYPE(args[4],ValueKind::kNumber);

    try{
        int minValue = args[1].asNumber().toInt32();
        int maxValue = args[2].asNumber().toInt32();
        if(minValue >= maxValue)
            maxValue = minValue + 1;
        
        int step = args.size() >= 4 ? args[3].asNumber().toInt32() : 1;
        int defValue = args.size() >= 5 ? args[4].asNumber().toInt32() : minValue;
        if (defValue < minValue || defValue > maxValue)
            defValue = minValue;
        
        form.append(Slider(args[0].toStr(), args[0].toStr(), minValue, maxValue, step, defValue));
        return this->getScriptObject();
    }
    CATCH("Fail in addSlider!")
}

Local<Value> CustomFormClass::addStepSlider(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,2)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)
    CHECK_ARG_TYPE(args[1],ValueKind::kArray);
    if(args.size() >= 3)
        CHECK_ARG_TYPE(args[2],ValueKind::kNumber);

    try{
        auto stepsArr = args[1].asArray();
        vector<string> steps;
        for (int i = 0; i < stepsArr.size(); ++i)
            steps.push_back(stepsArr.get(i).toStr());

        int defIndex = args.size() >= 3 ? args[2].asNumber().toInt32() : 0;
        
        form.append(StepSlider(args[0].toStr(), args[0].toStr(), steps, defIndex));
        return this->getScriptObject();
    }
    CATCH("Fail in addStepSlider!")
}


//////////////////// APIs ////////////////////

Local<Value> McClass::newSimpleForm(const Arguments& args)
{
    return SimpleFormClass::newForm();
}

Local<Value> McClass::newCustomForm(const Arguments& args)
{
    return CustomFormClass::newForm();
}


//表单回调
bool CallFormCallback(Player* player, unsigned formId, const string& data)
{
    bool passToBDS = true;

    try
    {
        for (auto engine : lxlModules)
        {
            EngineScope enter(engine);
            FormCallbackData callback;
            try
            {
                callback = ENGINE_GET_DATA(engine)->formCallbacks.at(formId);
            }
            catch (...)
            {
                continue;
            }

            EngineScope scope(callback.engine);
            Local<Value> res{};
            try
            {
                res = callback.func.get().call({}, PlayerClass::newPlayer(player), JsonToValue(data));
            }
            catch (const Exception& e)
            {
                Error("Form Callback Failed!");
                Error("In Plugin: " + ENGINE_OWN_DATA()->pluginName);
                Error(e);
            }
            if (res.isNull() || (res.isBoolean() && res.asBoolean().value() == false))
                passToBDS = false;

            ENGINE_OWN_DATA()->formCallbacks.erase(formId);
        }
    }
    catch (...)
    {
        ;
    }

    return passToBDS;
}