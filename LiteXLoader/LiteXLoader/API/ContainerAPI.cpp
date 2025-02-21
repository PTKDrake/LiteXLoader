#include "ContainerAPI.h"
#include "APIHelp.h"
#include "ItemAPI.h"
#include <MC/ItemStack.hpp>
#include <MC/Container.hpp>
using namespace std;

//////////////////// Class Definition ////////////////////

ClassDefine<ContainerClass> ContainerClassBuilder =
	defineClass<ContainerClass>("LXL_Container")
		.constructor(nullptr)
		.instanceFunction("getRawPtr", &ContainerClass::getRawPtr)

		.instanceProperty("size", &ContainerClass::getSize)
		.instanceProperty("type", &ContainerClass::getType)

		.instanceFunction("addItem", &ContainerClass::addItem)
		.instanceFunction("addItemToFirstEmptySlot", &ContainerClass::addItemToFirstEmptySlot)
		.instanceFunction("hasRoomFor", &ContainerClass::hasRoomFor)
		.instanceFunction("removeItem", &ContainerClass::removeItem)
		.instanceFunction("getItem", &ContainerClass::getItem)
		.instanceFunction("setItem", &ContainerClass::setItem)
		.instanceFunction("getAllItems", &ContainerClass::getAllItems)
		.instanceFunction("removeAllItems", &ContainerClass::removeAllItems)
		.instanceFunction("isEmpty", &ContainerClass::isEmpty)

		//For Compatibility
		.instanceFunction("getSlot", &ContainerClass::getItem)
		.instanceFunction("getAllSlots", &ContainerClass::getAllItems)
		.build();

//////////////////// Classes ////////////////////

ContainerClass::ContainerClass(Container* p)
	:ScriptClass(ScriptClass::ConstructFromCpp<ContainerClass>{}), container(p)
{ }

//生成函数
Local<Object> ContainerClass::newContainer(Container* p)
{
	auto newp = new ContainerClass(p);
	return newp->getScriptObject();
}
Container* ContainerClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<ContainerClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<ContainerClass>(v)->get();
	else
		return nullptr;
}

//成员函数
Local<Value> ContainerClass::getSize()
{
	try {
		return Number::newNumber(container->getSize());
	}
	CATCH("Fail in getSize!")
}

Local<Value> ContainerClass::getType()
{
	try {
		return String::newString(container->getTypeName());
	}
	CATCH("Fail in getType!")
}

Local<Value> ContainerClass::getRawPtr(const Arguments& args)
{
	try {
		return Number::newNumber((intptr_t)container);
	}
	CATCH("Fail in getRawPtr!")
}

Local<Value> ContainerClass::addItem(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		ItemStack* item = ItemClass::extract(args[0]);
		if (!item)
		{
			ERROR("Wrong type of argument in addItem!");
			return Local<Value>();
		}
		return Boolean::newBoolean(container->addItem_s(item));
	}
	CATCH("Fail in addItem!");
}

Local<Value> ContainerClass::addItemToFirstEmptySlot(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		ItemStack* item = ItemClass::extract(args[0]);
		if (!item)
		{
			ERROR("Wrong type of argument in addItemToFirstEmptySlot!");
			return Local<Value>();
		}
		return Boolean::newBoolean(container->addItemToFirstEmptySlot_s(item));
	}
	CATCH("Fail in addItemToFirstEmptySlot!");
}

Local<Value> ContainerClass::hasRoomFor(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		ItemStack* item = ItemClass::extract(args[0]);
		if (!item)
		{
			ERROR("Wrong type of argument in hasRoomFor!");
			return Local<Value>();
		}
		return Boolean::newBoolean(container->hasRoomForItem(*item));
	}
	CATCH("Fail in hasRoomFor!");
}

Local<Value> ContainerClass::removeItem(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try {
		container->removeItem(args[0].toInt(), args[1].toInt());
		return Boolean::newBoolean(true);
	}
	CATCH("Fail in removeItem!");
}

Local<Value> ContainerClass::getItem(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try {
		ItemStack* item = (ItemStack*) & container->getItem(args[0].toInt());
		if (!item)
		{
			ERROR("Fail to get slot from container!");
			return Local<Value>();
		}
		return ItemClass::newItem(item);
	}
	CATCH("Fail in getItem!");
}

Local<Value> ContainerClass::setItem(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try {
		ItemStack* item = ItemClass::extract(args[1]);
		if (!item)
		{
			ERROR("Wrong type of argument in setItem!");
			return Local<Value>();
		}

		ItemStack* itemOld = (ItemStack*)&container->getItem(args[0].toInt());
		if (!itemOld)
			return Boolean::newBoolean(false);

		return Boolean::newBoolean(itemOld->setItem(item));
	}
	CATCH("Fail in getItem!");
}

Local<Value> ContainerClass::getAllItems(const Arguments& args)
{
	try {
		auto list = container->getAllSlots();

		Local<Array> res = Array::newArray();
		for (auto& item : list)
		{
			res.add(ItemClass::newItem((ItemStack*)item));
		}
		return res;
	}
	CATCH("Fail in getAllItems!");
}

Local<Value> ContainerClass::removeAllItems(const Arguments& args)
{
	try {
		container->removeAllItems();
		return Boolean::newBoolean(true);
	}
	CATCH("Fail in removeAllItems!");
}

Local<Value> ContainerClass::isEmpty(const Arguments& args)
{
	try {
		return Boolean::newBoolean(container->isEmpty());
	}
	CATCH("Fail in isEmpty!");
}