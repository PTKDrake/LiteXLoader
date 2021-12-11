#include "APIHelp.h"
#include "NbtAPI.h"
#include <vector>
#include <string>
#include <LiteXLoader/API/ItemAPI.h>
#include <LiteXLoader/API/BlockAPI.h>
#include <MC/EndTag.hpp>
#include <MC/ByteTag.hpp>
#include <MC/ShortTag.hpp>
#include <MC/IntTag.hpp>
#include <MC/Int64Tag.hpp>
#include <MC/FloatTag.hpp>
#include <MC/DoubleTag.hpp>
#include <MC/ByteArrayTag.hpp>
#include <MC/StringTag.hpp>
#include <MC/ListTag.hpp>
#include <MC/CompoundTag.hpp>
using namespace script;
using namespace std;


//////////////////// Class Definition ////////////////////

ClassDefine<void> NbtStaticBuilder =
	defineClass("NBT")
		.function("newTag", &NbtStatic::newTag)
		.function("parseSNBT", &NbtStatic::parseSNBT)
		.function("parseBinaryNBT", &NbtStatic::parseBinaryNBT)
		.property("End", &NbtStatic::getType<Tag::Type::End>)
		.property("Byte", &NbtStatic::getType<Tag::Type::Byte>)
		.property("Short", &NbtStatic::getType<Tag::Type::Short>)
		.property("Int", &NbtStatic::getType<Tag::Type::Int>)
		.property("Long", &NbtStatic::getType<Tag::Type::Int64>)
		.property("Float", &NbtStatic::getType<Tag::Type::Float>)
		.property("Double", &NbtStatic::getType<Tag::Type::Double>)
		.property("ByteArray", &NbtStatic::getType<Tag::Type::ByteArray>)
		.property("String", &NbtStatic::getType<Tag::Type::String>)
		.property("List", &NbtStatic::getType<Tag::Type::List>)
		.property("Compound", &NbtStatic::getType<Tag::Type::Compound>)

		//For Compatibility
		.function("createTag", &NbtStatic::newTag)
		.build();

ClassDefine<NbtEndClass> NbtEndClassBuilder =
	defineClass<NbtEndClass>("NbtEnd")
		.constructor(&NbtEndClass::constructor)
		.instanceFunction("getType", &NbtEndClass::getType)
		.instanceFunction("toString", &NbtEndClass::toString)
		.instanceFunction("set", &NbtEndClass::set)
		.instanceFunction("get", &NbtEndClass::get)
		.build();

ClassDefine<NbtByteClass> NbtByteClassBuilder =
	defineClass<NbtByteClass>("NbtByte")
		.constructor(&NbtByteClass::constructor)
		.instanceFunction("getType", &NbtByteClass::getType)
		.instanceFunction("toString", &NbtByteClass::toString)
		.instanceFunction("set", &NbtByteClass::set)
		.instanceFunction("get", &NbtByteClass::get)
		.build();

ClassDefine<NbtShortClass> NbtShortClassBuilder =
	defineClass<NbtShortClass>("NbtShort")
		.constructor(&NbtShortClass::constructor)
		.instanceFunction("getType", &NbtShortClass::getType)
		.instanceFunction("toString", &NbtShortClass::toString)
		.instanceFunction("set", &NbtShortClass::set)
		.instanceFunction("get", &NbtShortClass::get)
		.build();

ClassDefine<NbtIntClass> NbtIntClassBuilder =
	defineClass<NbtIntClass>("NbtInt")
		.constructor(&NbtIntClass::constructor)
		.instanceFunction("getType", &NbtIntClass::getType)
		.instanceFunction("toString", &NbtIntClass::toString)
		.instanceFunction("set", &NbtIntClass::set)
		.instanceFunction("get", &NbtIntClass::get)
		.build();

ClassDefine<NbtLongClass> NbtLongClassBuilder =
	defineClass<NbtLongClass>("NbtLong")
		.constructor(&NbtLongClass::constructor)
		.instanceFunction("getType", &NbtLongClass::getType)
		.instanceFunction("toString", &NbtLongClass::toString)
		.instanceFunction("set", &NbtLongClass::set)
		.instanceFunction("get", &NbtLongClass::get)
		.build();

ClassDefine<NbtFloatClass> NbtFloatClassBuilder =
	defineClass<NbtFloatClass>("NbtFloat")
		.constructor(&NbtFloatClass::constructor)
		.instanceFunction("getType", &NbtFloatClass::getType)
		.instanceFunction("toString", &NbtFloatClass::toString)
		.instanceFunction("set", &NbtFloatClass::set)
		.instanceFunction("get", &NbtFloatClass::get)
		.build();

ClassDefine<NbtDoubleClass> NbtDoubleClassBuilder =
	defineClass<NbtDoubleClass>("NbtDouble")
		.constructor(&NbtDoubleClass::constructor)
		.instanceFunction("getType", &NbtDoubleClass::getType)
		.instanceFunction("toString", &NbtDoubleClass::toString)
		.instanceFunction("set", &NbtDoubleClass::set)
		.instanceFunction("get", &NbtDoubleClass::get)
		.build();

ClassDefine<NbtStringClass> NbtStringClassBuilder =
	defineClass<NbtStringClass>("NbtString")
		.constructor(&NbtStringClass::constructor)
		.instanceFunction("getType", &NbtStringClass::getType)
		.instanceFunction("toString", &NbtStringClass::toString)
		.instanceFunction("set", &NbtStringClass::set)
		.instanceFunction("get", &NbtStringClass::get)
		.build();

ClassDefine<NbtByteArrayClass> NbtByteArrayClassBuilder =
	defineClass<NbtByteArrayClass>("NbtByteArray")
		.constructor(&NbtByteArrayClass::constructor)
		.instanceFunction("getType", &NbtByteArrayClass::getType)
		.instanceFunction("toString", &NbtByteArrayClass::toString)
		.instanceFunction("set", &NbtByteArrayClass::set)
		.instanceFunction("get", &NbtByteArrayClass::get)
		.build();

ClassDefine<NbtListClass> NbtListClassBuilder =
	defineClass<NbtListClass>("NbtList")
		.constructor(&NbtListClass::constructor)
		.instanceFunction("getType", &NbtListClass::getType)
		.instanceFunction("toString", &NbtListClass::toString)
		.instanceFunction("getSize", &NbtListClass::getSize)
		.instanceFunction("getTypeOf", &NbtListClass::getTypeOf)
		.instanceFunction("setEnd", &NbtListClass::setEnd)
		.instanceFunction("setByte", &NbtListClass::setByte)
		.instanceFunction("setInt", &NbtListClass::setInt)
		.instanceFunction("setShort", &NbtListClass::setShort)
		.instanceFunction("setLong", &NbtListClass::setLong)
		.instanceFunction("setFloat", &NbtListClass::setFloat)
		.instanceFunction("setDouble", &NbtListClass::setDouble)
		.instanceFunction("setString", &NbtListClass::setString)
		.instanceFunction("setByteArray", &NbtListClass::setByteArray)
		.instanceFunction("setTag", &NbtListClass::setTag)
		.instanceFunction("addTag", &NbtListClass::addTag)
		.instanceFunction("removeTag", &NbtListClass::removeTag)
		.instanceFunction("getData", &NbtListClass::getData)
		.instanceFunction("getTag", &NbtListClass::getTag)
		.instanceFunction("toArray", &NbtListClass::toArray)
		.instanceFunction("destroy", &NbtListClass::destroy)
		.build();

ClassDefine<NbtCompoundClass> NbtCompoundClassBuilder =
	defineClass<NbtCompoundClass>("NbtCompound")
		.constructor(&NbtCompoundClass::constructor)
		.instanceFunction("getType", &NbtCompoundClass::getType)
		.instanceFunction("toString", &NbtCompoundClass::toString)
		.instanceFunction("getKeys", &NbtCompoundClass::getKeys)
		.instanceFunction("getTypeOf", &NbtCompoundClass::getTypeOf)
		.instanceFunction("setEnd", &NbtCompoundClass::setEnd)
		.instanceFunction("setByte", &NbtCompoundClass::setByte)
		.instanceFunction("setInt", &NbtCompoundClass::setInt)
		.instanceFunction("setShort", &NbtCompoundClass::setShort)
		.instanceFunction("setLong", &NbtCompoundClass::setLong)
		.instanceFunction("setFloat", &NbtCompoundClass::setFloat)
		.instanceFunction("setDouble", &NbtCompoundClass::setDouble)
		.instanceFunction("setString", &NbtCompoundClass::setString)
		.instanceFunction("setByteArray", &NbtCompoundClass::setByteArray)
		.instanceFunction("setTag", &NbtCompoundClass::setTag)
		.instanceFunction("removeTag", &NbtCompoundClass::removeTag)
		.instanceFunction("getData", &NbtCompoundClass::getData)
		.instanceFunction("getTag", &NbtCompoundClass::getTag)
		.instanceFunction("toObject", &NbtCompoundClass::toObject)
		.instanceFunction("toSNBT", &NbtCompoundClass::toSNBT)
		.instanceFunction("toBinaryNBT", &NbtCompoundClass::toBinaryNBT)
		.instanceFunction("destroy", &NbtCompoundClass::destroy)
		.build();


//////////////////// Classes NbtBase ////////////////////

Local<Value> NbtBase::toString(const Arguments& args)
{
	if (args.size() >= 1)
		CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	try {
		return String::newString(TagToJson(nbt, args.size() >= 1 ? args[0].toInt() : -1));
	}
	CATCH("Fail in NBTtoJson!");
}

Local<Value> NbtBase::destroy(const Arguments& args)
{
	//if (canDelete)
	//{
	//    nbt->destroy();
		//delete nbt;
	//}
	return Boolean::newBoolean(true);
}


//////////////////// Classes NbtEnd ////////////////////

NbtEndClass::NbtEndClass(const Local<Object>& scriptObj, EndTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtEndClass::NbtEndClass(EndTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtEndClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtEndClass* NbtEndClass::constructor(const Arguments& args)
{
	try {
		EndTag* tag = EndTag::create();

		if (args.size() >= 1)
			if (!TagSetValue(Tag::Type::End, tag, args[0]))
			{
				ERROR("Fail to Set value of EndTag!");
			}

		return new NbtEndClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create EndTag!");
}

EndTag* NbtEndClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtEndClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtEndClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtEndClass::pack(EndTag* tag, bool canDelete)
{
	try
	{
		return (new NbtEndClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtEnd!");
}

Local<Value> NbtEndClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::End);
}

Local<Value> NbtEndClass::get(const Arguments& args)
{
	try {
		return Local<Value>();
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtEndClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)

	try {
		return Boolean::newBoolean(true);
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtByte ////////////////////

NbtByteClass::NbtByteClass(const Local<Object>& scriptObj, ByteTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtByteClass::NbtByteClass(ByteTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtByteClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtByteClass* NbtByteClass::constructor(const Arguments& args)
{
	try {
		ByteTag* tag = ByteTag::create((char)args[0].toInt());
		return new NbtByteClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create ByteTag!");
}

ByteTag* NbtByteClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtByteClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtByteClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtByteClass::pack(ByteTag* tag, bool canDelete)
{
	try
	{
		return (new NbtByteClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtByte!");
}

Local<Value> NbtByteClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Byte);
}

Local<Value> NbtByteClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtByteClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set((char)args[0].toInt()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtInt ////////////////////

NbtIntClass::NbtIntClass(const Local<Object>& scriptObj, IntTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtIntClass::NbtIntClass(IntTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtIntClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtIntClass* NbtIntClass::constructor(const Arguments& args)
{
	try {
		IntTag* tag = IntTag::create(args[0].toInt());
		return new NbtIntClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create IntTag!");
}

IntTag* NbtIntClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtIntClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtIntClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtIntClass::pack(IntTag* tag, bool canDelete)
{
	try
	{
		return (new NbtIntClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtInt!");
}

Local<Value> NbtIntClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Int);
}

Local<Value> NbtIntClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtIntClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)

	try {
		return Boolean::newBoolean(nbt->set(args[0].toInt()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtShort ////////////////////

NbtShortClass::NbtShortClass(const Local<Object>& scriptObj, ShortTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtShortClass::NbtShortClass(ShortTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtShortClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtShortClass* NbtShortClass::constructor(const Arguments& args)
{
	try {
		ShortTag* tag = ShortTag::create(args[0].toInt());
		return new NbtShortClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create ShortTag!");
}

ShortTag* NbtShortClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtShortClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtShortClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtShortClass::pack(ShortTag* tag, bool canDelete)
{
	try
	{
		return (new NbtShortClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtShort!");
}

Local<Value> NbtShortClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Short);
}

Local<Value> NbtShortClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtShortClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set(args[0].toInt()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtLong ////////////////////

NbtLongClass::NbtLongClass(const Local<Object>& scriptObj, Int64Tag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtLongClass::NbtLongClass(Int64Tag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtLongClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtLongClass* NbtLongClass::constructor(const Arguments& args)
{
	try {
		Int64Tag* tag = Int64Tag::create(args[0].asNumber().toInt64());
		return new NbtLongClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create LongTag!");
}

Int64Tag* NbtLongClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtLongClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtLongClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtLongClass::pack(Int64Tag* tag, bool canDelete)
{
	try
	{
		return (new NbtLongClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtLong!");
}

Local<Value> NbtLongClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Int64);
}

Local<Value> NbtLongClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtLongClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set(args[0].asNumber().toInt64()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtFloat ////////////////////

NbtFloatClass::NbtFloatClass(const Local<Object>& scriptObj, FloatTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtFloatClass::NbtFloatClass(FloatTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtFloatClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtFloatClass* NbtFloatClass::constructor(const Arguments& args)
{
	try {
		FloatTag* tag = FloatTag::create(args[0].asNumber().toFloat());
		return new NbtFloatClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create FloatTag!");
}

FloatTag* NbtFloatClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtFloatClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtFloatClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtFloatClass::pack(FloatTag* tag, bool canDelete)
{
	try
	{
		return (new NbtFloatClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtFloat!");
}

Local<Value> NbtFloatClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Float);
}

Local<Value> NbtFloatClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtFloatClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set(args[0].asNumber().toFloat()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtDouble ////////////////////

NbtDoubleClass::NbtDoubleClass(const Local<Object>& scriptObj, DoubleTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtDoubleClass::NbtDoubleClass(DoubleTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtDoubleClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtDoubleClass* NbtDoubleClass::constructor(const Arguments& args)
{
	try {
		DoubleTag* tag = DoubleTag::create(args[0].asNumber().toDouble());
		return new NbtDoubleClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create DoubleTag!");
}

DoubleTag* NbtDoubleClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtDoubleClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtDoubleClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtDoubleClass::pack(DoubleTag* tag, bool canDelete)
{
	try
	{
		return (new NbtDoubleClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtDouble!");
}

Local<Value> NbtDoubleClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Double);
}

Local<Value> NbtDoubleClass::get(const Arguments& args)
{
	try {
		return Number::newNumber(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtDoubleClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set(args[0].asNumber().toDouble()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtString ////////////////////

NbtStringClass::NbtStringClass(const Local<Object>& scriptObj, StringTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtStringClass::NbtStringClass(StringTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtStringClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtStringClass* NbtStringClass::constructor(const Arguments& args)
{
	try {
		StringTag* tag = StringTag::create(args[0].toStr());
		return new NbtStringClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create StringTag!");
}

StringTag* NbtStringClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtStringClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtStringClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtStringClass::pack(StringTag* tag, bool canDelete)
{
	try
	{
		return (new NbtStringClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtString!");
}

Local<Value> NbtStringClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::String);
}

Local<Value> NbtStringClass::get(const Arguments& args)
{
	try {
		return String::newString(nbt->get());
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtStringClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		return Boolean::newBoolean(nbt->set(args[0].toStr()));
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtByteArray ////////////////////

NbtByteArrayClass::NbtByteArrayClass(const Local<Object>& scriptObj, ByteArrayTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtByteArrayClass::NbtByteArrayClass(ByteArrayTag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtByteArrayClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtByteArrayClass* NbtByteArrayClass::constructor(const Arguments& args)
{
	try {
		auto buf = args[0].asByteBuffer();
		ByteArrayTag* tag = ByteArrayTag::create(TagMemoryChunk(buf.byteLength(), (uint8_t*)buf.getRawBytes()));
		return new NbtByteArrayClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create ByteArrayTag!");
}

ByteArrayTag* NbtByteArrayClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtByteArrayClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtByteArrayClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtByteArrayClass::pack(ByteArrayTag* tag, bool canDelete)
{
	try
	{
		return (new NbtByteArrayClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtByteArray!");
}

Local<Value> NbtByteArrayClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::ByteArray);
}

Local<Value> NbtByteArrayClass::get(const Arguments& args)
{
	try {
		return ByteBuffer::newByteBuffer()
	}
	CATCH("Fail in NbtValueGet!")
}

Local<Value> NbtByteArrayClass::set(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)

		try {
		return Boolean::newBoolean(nbt->set());
	}
	CATCH("Fail in NbtValueSet!")
}


//////////////////// Classes NbtList ////////////////////

NbtListClass::NbtListClass(const Local<Object>& scriptObj, ListTag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtListClass::NbtListClass(Tag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtListClass>{})
{
	this->nbt = p;
	this->canDelete = canDelete;
}

NbtListClass* NbtListClass::constructor(const Arguments& args)
{
	try {
		Tag* tag = Tag::createTag(Tag::Type::List);

		if (args.size() >= 1)
			if (!TagSetValue(Tag::Type::List, tag, args[0]))
			{
				ERROR("Fail to Set value of ListTag!");
			}

		return new NbtListClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create ListTag!");
}

ListTag* NbtListClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtListClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtListClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtListClass::pack(ListTag* tag, bool canDelete)
{
	try
	{
		return (new NbtListClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtList!");
}

Local<Value> NbtListClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::List);
}

Local<Value> NbtListClass::getSize(const Arguments& args)
{
	try
	{
		return Number::newNumber(int(nbt->asList().size()));
	}
	CATCH("Fail in NBT GetSize!");
}

Local<Value> NbtListClass::getTypeOf(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			return Local<Value>();
		}

		return Number::newNumber(int(list[index]->getTag::Type()));
	}
	CATCH("Fail in NBT GetTypeOf!");
}

Local<Value> NbtListClass::setEnd(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::End, list[index]))
		{
			ERROR("Fail to Set End in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetEnd!");
}

Local<Value> NbtListClass::setByte(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Byte, list[index], args[1]))
		{
			ERROR("Fail to Set Byte in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetByte!");
}

Local<Value> NbtListClass::setInt(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Int, list[index], args[1]))
		{
			ERROR("Fail to Set Int in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetInt!");
}

Local<Value> NbtListClass::setShort(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Short, list[index], args[1]))
		{
			ERROR("Fail to Set Short in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetShort!");
}

Local<Value> NbtListClass::setLong(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Long, list[index], args[1]))
		{
			ERROR("Fail to Set Long in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetLong!");
}

Local<Value> NbtListClass::setFloat(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Float, list[index], args[1]))
		{
			ERROR("Fail to Set Float in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetFloat!");
}

Local<Value> NbtListClass::setDouble(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::Double, list[index], args[1]))
		{
			ERROR("Fail to Set Double in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetDouble!");
}

Local<Value> NbtListClass::setString(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::String, list[index], args[1]))
		{
			ERROR("Fail to Set String in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetString!");
}

Local<Value> NbtListClass::setByteArray(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
		}

		if (!TagSetValue(Tag::Type::ByteArray, list[index], args[1]))
		{
			ERROR("Fail to Set ByteArray in NBT List!");
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetByteArray!");
}

Local<Value> NbtListClass::setTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
			return Local<Value>();
		}

		if (IsInstanceOf<NbtEndClass>(args[1]))
		{
			list[index] = NbtEndClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtByteClass>(args[1]))
		{
			list[index] = NbtByteClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtShortClass>(args[1]))
		{
			list[index] = NbtShortClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtIntClass>(args[1]))
		{
			list[index] = NbtIntClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtLongClass>(args[1]))
		{
			list[index] = NbtLongClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtFloatClass>(args[1]))
		{
			list[index] = NbtFloatClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtDoubleClass>(args[1]))
		{
			list[index] = NbtDoubleClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtStringClass>(args[1]))
		{
			list[index] = NbtStringClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtByteArrayClass>(args[1]))
		{
			list[index] = NbtByteArrayClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtListClass>(args[1]))
		{
			list[index] = NbtListClass::extract(args[1]);
		}
		else if (IsInstanceOf<NbtCompoundClass>(args[1]))
		{
			list[index] = NbtCompoundClass::extract(args[1]);
		}
		else
		{
			ERROR("Unknown type! Cannot set Tag into List");
			return Local<Value>();
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetTag!");
}

Local<Value> NbtListClass::addTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try
	{
		if (IsInstanceOf<NbtEndClass>(args[0]))
		{
			nbt->add(NbtEndClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtByteClass>(args[0]))
		{
			nbt->add(NbtByteClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtShortClass>(args[0]))
		{
			nbt->add(NbtShortClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtIntClass>(args[0]))
		{
			nbt->add(NbtIntClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtLongClass>(args[0]))
		{
			nbt->add(NbtLongClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtFloatClass>(args[0]))
		{
			nbt->add(NbtFloatClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtDoubleClass>(args[0]))
		{
			nbt->add(NbtDoubleClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtStringClass>(args[0]))
		{
			nbt->add(NbtStringClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtByteArrayClass>(args[0]))
		{
			nbt->add(NbtByteArrayClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtListClass>(args[0]))
		{
			nbt->add(NbtListClass::extract(args[0]));
		}
		else if (IsInstanceOf<NbtCompoundClass>(args[0]))
		{
			nbt->add(NbtCompoundClass::extract(args[0]));
		}
		else
		{
			ERROR("Unknown type! Cannot add Tag into List");
			return Local<Value>();
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT AddTag!");
}

Local<Value> NbtListClass::removeTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			ERROR("Bad Index of NBT List!");
			return Local<Value>();
		}

		list.erase(list.begin() + index);
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetTag!");
}

Local<Value> NbtListClass::getData(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			return Local<Value>();
		}

		return Tag2Value(list[index]);
	}
	CATCH("Fail in NBTgetData!")
}

Local<Value> NbtListClass::getTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asList();
		auto index = args[0].toInt();

		if (index >= list.size() || index < 0)
		{
			return Local<Value>();
		}

		Local<Value> res;
		switch (list[index]->getTag::Type())
		{
		case Tag::Type::End:
			res = NbtEndClass::pack(list[index]);
			break;
		case Tag::Type::Byte:
			res = NbtByteClass::pack(list[index]);
			break;
		case Tag::Type::Short:
			res = NbtShortClass::pack(list[index]);
			break;
		case Tag::Type::Int:
			res = NbtIntClass::pack(list[index]);
			break;
		case Tag::Type::Long:
			res = NbtLongClass::pack(list[index]);
			break;
		case Tag::Type::Float:
			res = NbtFloatClass::pack(list[index]);
			break;
		case Tag::Type::Double:
			res = NbtDoubleClass::pack(list[index]);
			break;
		case Tag::Type::String:
			res = NbtStringClass::pack(list[index]);
			break;
		case Tag::Type::ByteArray:
			res = NbtByteArrayClass::pack(list[index]);
			break;
		case Tag::Type::List:
			res = NbtListClass::pack(list[index]);
			break;
		case Tag::Type::Compound:
			res = NbtCompoundClass::pack(list[index]);
			break;
		default:
			res = Local<Value>();
			break;
		}
		return res;
	}
	CATCH("Fail in NBT GetTag!");
}

Local<Value> NbtListClass::toArray(const Arguments& args)
{
	try
	{
		auto& list = nbt->asList();
		Local<Array> arr = Array::newArray();

		for (auto& tag : list)
		{
			arr.add(Tag2Value(tag, true));
		}
		return arr;
	}
	CATCH("Fail in NBTtoArray!");
}


//////////////////// Classes NbtCompound ////////////////////

NbtCompoundClass::NbtCompoundClass(const Local<Object>& scriptObj, Tag* p, bool canDelete)
	:ScriptClass(scriptObj)
{
	nbt = p;
	this->canDelete = canDelete;
}

NbtCompoundClass::NbtCompoundClass(Tag* p, bool canDelete)
	:ScriptClass(ScriptClass::ConstructFromCpp<NbtCompoundClass>{})
{
	nbt = p;
	this->canDelete = canDelete;
}

NbtCompoundClass* NbtCompoundClass::constructor(const Arguments& args)
{
	try {
		Tag* tag = Tag::createTag(Tag::Type::Compound);

		if (args.size() >= 1)
			if (!TagSetValue(Tag::Type::Compound, tag, args[0]))
			{
				ERROR("Fail to Set value of CompoundTag!");
			}

		return new NbtCompoundClass(args.thiz(), tag, true);
	}
	CATCH_C("Fail in Create ListTag!");
}

Tag* NbtCompoundClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<NbtCompoundClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<NbtCompoundClass>(v)->nbt;
	else
		return nullptr;
}

Local<Value> NbtCompoundClass::pack(Tag* tag, bool canDelete)
{
	try
	{
		return (new NbtCompoundClass(tag, canDelete))->getScriptObject();
	}
	CATCH("Fail in construct NbtCompound!");
}

Local<Value> NbtCompoundClass::getType(const Arguments& args)
{
	return Number::newNumber((int)Tag::Type::Compound);
}


Local<Value> NbtCompoundClass::getKeys(const Arguments& args)
{
	try
	{
		Local<Array> arr = Array::newArray();
		auto& list = nbt->asCompound();
		for (auto& [k, v] : list)
		{
			arr.add(String::newString(k));
		}

		return arr;
	}
	CATCH("Fail in NBT GetKeys!");
}

Local<Value> NbtCompoundClass::getTypeOf(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto& list = nbt->asCompound();
		auto key = args[0].toStr();

		return Number::newNumber(int(list.at(key).getTag::Type()));
	}
	catch (const out_of_range& e)
	{
		return Local<Value>();
	}
	CATCH("Fail in NBT GetTypeOf!");
}

Local<Value> NbtCompoundClass::setEnd(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto key = args[0].toStr();
		nbt->putByte(key, (char)0);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetEnd!");
}

Local<Value> NbtCompoundClass::setByte(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto key = args[0].toStr();
		auto data = char(args[1].toInt());
		nbt->putByte(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetByte!");
}

Local<Value> NbtCompoundClass::setInt(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto key = args[0].toStr();
		auto data = int(args[1].toInt());
		nbt->putInt(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetInt!");
}

Local<Value> NbtCompoundClass::setShort(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto key = args[0].toStr();
		auto data = short(args[1].toInt());
		nbt->putShort(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetShort!");
}

Local<Value> NbtCompoundClass::setLong(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto key = args[0].toStr();
		auto data = args[1].asNumber().toInt64();
		nbt->putLong(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetLong!");
}

Local<Value> NbtCompoundClass::setFloat(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto key = args[0].toStr();
		auto data = args[1].asNumber().toFloat();
		nbt->putFloat(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetFloat!");
}

Local<Value> NbtCompoundClass::setDouble(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

	try
	{
		auto& list = nbt->asCompound();
		auto key = args[0].toStr();
		auto data = args[1].asNumber().toDouble();

		list[key].asDouble() = data;
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetDouble!");
}

Local<Value> NbtCompoundClass::setString(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kString);

	try
	{
		auto key = args[0].toStr();
		auto data = args[1].toStr();
		nbt->putString(key, data);

		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetString!");
}

Local<Value> NbtCompoundClass::setByteArray(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);
	CHECK_ARG_TYPE(args[1], ValueKind::kByteBuffer);

	try
	{
		auto key = args[0].toStr();
		auto data = args[1].asByteBuffer();

		nbt->putByteArray(key, data.getRawBytes(), data.byteLength());
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetString!");
}

Local<Value> NbtCompoundClass::setTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto key = args[0].toStr();

		if (IsInstanceOf<NbtEndClass>(args[1]))
		{
			nbt->put(key, NbtEndClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtByteClass>(args[1]))
		{
			nbt->put(key, NbtByteClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtShortClass>(args[1]))
		{
			nbt->put(key, NbtShortClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtIntClass>(args[1]))
		{
			nbt->put(key, NbtIntClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtLongClass>(args[1]))
		{
			nbt->put(key, NbtLongClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtFloatClass>(args[1]))
		{
			nbt->put(key, NbtFloatClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtDoubleClass>(args[1]))
		{
			nbt->put(key, NbtDoubleClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtStringClass>(args[1]))
		{
			nbt->put(key, NbtStringClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtByteArrayClass>(args[1]))
		{
			nbt->put(key, NbtByteArrayClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtListClass>(args[1]))
		{
			nbt->put(key, NbtListClass::extract(args[1]));
		}
		else if (IsInstanceOf<NbtCompoundClass>(args[1]))
		{
			nbt->put(key, NbtCompoundClass::extract(args[1]));
		}
		else
		{
			ERROR("Unknown type! Cannot set Tag into Compound");
			return Local<Value>();
		}
		return this->getScriptObject();
	}
	CATCH("Fail in NBT SetTag!");
}

Local<Value> NbtCompoundClass::removeTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto& list = nbt->asCompound();
		auto key = args[0].toStr();

		list.erase(key);
		return this->getScriptObject();
	}
	catch (const out_of_range& e)
	{
		ERROR("Key no found in NBT Compound!");
		return Local<Value>();
	}
	CATCH("Fail in NBT RemoveTag!");
}

Local<Value> NbtCompoundClass::getData(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto& list = nbt->asCompound();
		auto key = args[0].toStr();

		return Tag2Value(&(list.at(key)));
	}
	catch (const out_of_range& e)
	{
		return Local<Value>();
	}
	CATCH("Fail in NBT GetData!")
}

Local<Value> NbtCompoundClass::getTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try
	{
		auto& list = nbt->asCompound();
		auto key = args[0].toStr();

		Local<Value> res;
		switch (list.at(key).getTag::Type())
		{
		case Tag::Type::End:
			res = NbtEndClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Byte:
			res = NbtByteClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Short:
			res = NbtShortClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Int:
			res = NbtIntClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Long:
			res = NbtLongClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Float:
			res = NbtFloatClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Double:
			res = NbtDoubleClass::pack(&(list.at(key)));
			break;
		case Tag::Type::String:
			res = NbtStringClass::pack(&(list.at(key)));
			break;
		case Tag::Type::ByteArray:
			res = NbtByteArrayClass::pack(&(list.at(key)));
			break;
		case Tag::Type::List:
			res = NbtListClass::pack(&(list.at(key)));
			break;
		case Tag::Type::Compound:
			res = NbtCompoundClass::pack(&(list.at(key)));
			break;
		default:
			res = Local<Value>();
			break;
		}
		return res;
	}
	catch (const out_of_range& e)
	{
		return Local<Value>();
	}
	CATCH("Fail in NBT GetTag!");
}

Local<Value> NbtCompoundClass::toObject(const Arguments& args)
{
	try
	{
		auto& comp = nbt->asCompound();
		Local<Object> obj = Object::newObject();

		for (auto& [k, v] : comp)
		{
			obj.set(k, Tag2Value(&v, true));
		}
		return obj;
	}
	CATCH("Fail in NBT ToObject!");
}

Local<Value> NbtCompoundClass::toSNBT(const Arguments& args)
{
	try
	{
		return String::newString(TagToSNBT(nbt));
	}
	CATCH("Fail in toSNBT!");
}

Local<Value> NbtCompoundClass::toBinaryNBT(const Arguments& args)
{
	try
	{
		auto res = TagToBinaryNBT(nbt);
		return ByteBuffer::newByteBuffer(res.data(), res.size());
	}
	CATCH("Fail in toBinaryNBT!");
}

//////////////////// APIs ////////////////////

Local<Value> NbtStatic::newTag(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

	try {
		auto type = args[0].toInt();

		Tag* tag;
		switch (type)
		{
		case Tag::Type::End:
			tag = Tag::createTag(Tag::Type::End);
			break;
		case Tag::Type::Byte:
			tag = Tag::createTag(Tag::Type::Byte);
			break;
		case Tag::Type::Short:
			tag = Tag::createTag(Tag::Type::Short);
			break;
		case Tag::Type::Int:
			tag = Tag::createTag(Tag::Type::Int);
			break;
		case Tag::Type::Long:
			tag = Tag::createTag(Tag::Type::Long);
			break;
		case Tag::Type::Float:
			tag = Tag::createTag(Tag::Type::Float);
			break;
		case Tag::Type::Double:
			tag = Tag::createTag(Tag::Type::Double);
			break;
		case Tag::Type::String:
			tag = Tag::createTag(Tag::Type::String);
			break;
		case Tag::Type::ByteArray:
			tag = Tag::createTag(Tag::Type::ByteArray);
			break;
		case Tag::Type::List:
			tag = Tag::createTag(Tag::Type::List);
			break;
		case Tag::Type::Compound:
			tag = Tag::createTag(Tag::Type::Compound);
			break;
		default:
			return Local<Value>();
		}

		if (args.size() >= 2)
		{
			if (!TagSetValue((Tag::Type)type, tag, args[1]))
			{
				ERROR("Fail to set value of tag!");
				return Local<Value>();
			}
		}

		Local<Value> res;
		switch (type)
		{
		case Tag::Type::End:
			res = NbtEndClass::pack(tag);
			break;
		case Tag::Type::Byte:
			res = NbtByteClass::pack(tag);
			break;
		case Tag::Type::Short:
			res = NbtShortClass::pack(tag);
			break;
		case Tag::Type::Int:
			res = NbtIntClass::pack(tag);
			break;
		case Tag::Type::Long:
			res = NbtLongClass::pack(tag);
			break;
		case Tag::Type::Float:
			res = NbtFloatClass::pack(tag);
			break;
		case Tag::Type::Double:
			res = NbtDoubleClass::pack(tag);
			break;
		case Tag::Type::String:
			res = NbtStringClass::pack(tag);
			break;
		case Tag::Type::ByteArray:
			res = NbtByteArrayClass::pack(tag);
			break;
		case Tag::Type::List:
			res = NbtListClass::pack(tag);
			break;
		case Tag::Type::Compound:
			res = NbtCompoundClass::pack(tag);
			break;
		default:
			res = Local<Value>();
		}
		return res;
	}
	CATCH("Fail in NBT CreateTag!");
}

Local<Value> NbtStatic::parseSNBT(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try {
		Tag* tag = SNBTToTag(args[0].toStr());
		if (tag)
			return NbtCompoundClass::pack(tag);
		else
			return Local<Value>();
	}
	CATCH("Fail in parseSNBT!");
}

Local<Value> NbtStatic::parseBinaryNBT(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kByteBuffer);

	try {
		auto data = args[0].asByteBuffer();
		Tag* tag = BinaryNBTToTag(data.getRawBytes(), data.byteLength());
		if (tag)
			return NbtCompoundClass::pack(tag);
		else
			return Local<Value>();
	}
	CATCH("Fail in parseBinaryNBT!");
}


//////////////////// Helper ////////////////////

bool IsNbtClass(Local<Value> value)
{
	return IsInstanceOf<NbtEndClass>(value) || IsInstanceOf<NbtByteClass>(value)
		|| IsInstanceOf<NbtShortClass>(value) || IsInstanceOf<NbtIntClass>(value)
		|| IsInstanceOf<NbtLongClass>(value) || IsInstanceOf<NbtFloatClass>(value)
		|| IsInstanceOf<NbtDoubleClass>(value) || IsInstanceOf<NbtStringClass>(value)
		|| IsInstanceOf<NbtByteArrayClass>(value) || IsInstanceOf<NbtListClass>(value)
		|| IsInstanceOf<NbtCompoundClass>(value);
}


//////////////////// Tag To Value ////////////////////

Local<Value> Tag2Value_CompoundHelper(Tag* nbt, bool autoExpansion = false);

Local<Value> Tag2Value_ListHelper(Tag* nbt, bool autoExpansion = false)
{
	Local<Array> res = Array::newArray();

	auto& list = nbt->asList();
	for (auto& tag : list)
	{
		switch (tag->getTag::Type())
		{
		case Tag::Type::End:
			res.add(Local<Value>());
			break;
		case Tag::Type::Byte:
			res.add(Number::newNumber(tag->asByte()));
			break;
		case Tag::Type::Short:
			res.add(Number::newNumber(tag->asShort()));
			break;
		case Tag::Type::Int:
			res.add(Number::newNumber(tag->asInt()));
			break;
		case Tag::Type::Long:
			res.add(Number::newNumber(tag->asLong()));
			break;
		case Tag::Type::Float:
			res.add(Number::newNumber(tag->asFloat()));
			break;
		case Tag::Type::Double:
			res.add(Number::newNumber(tag->asDouble()));
			break;
		case Tag::Type::String:
			res.add(String::newString(tag->asString()));
			break;
		case Tag::Type::ByteArray:
		{
			auto& data = tag->asByteArray();
			res.add(ByteBuffer::newByteBuffer(data.data.get(), data.size));
			break;
		}
		case Tag::Type::List:
			if (!autoExpansion)
				res.add(NbtListClass::pack(tag));
			else
				res.add(Tag2Value_ListHelper(tag, autoExpansion));
			break;
		case Tag::Type::Compound:
			if (!autoExpansion)
				res.add(NbtCompoundClass::pack(tag));
			else
				res.add(Tag2Value_CompoundHelper(tag, autoExpansion));
		default:
			res.add(Local<Value>());
			break;
		}
	}
	return res;
}

Local<Value> Tag2Value_CompoundHelper(Tag* nbt, bool autoExpansion)
{
	Local<Object> res = Object::newObject();

	auto& list = nbt->asCompound();
	for (auto& [key, tag] : list)
	{
		switch (tag.getTag::Type())
		{
		case Tag::Type::End:
			res.set(key, Local<Value>());
			break;
		case Tag::Type::Byte:
			res.set(key, Number::newNumber(tag.asByte()));
			break;
		case Tag::Type::Short:
			res.set(key, Number::newNumber(tag.asShort()));
			break;
		case Tag::Type::Int:
			res.set(key, Number::newNumber(tag.asInt()));
			break;
		case Tag::Type::Long:
			res.set(key, Number::newNumber(tag.asLong()));
			break;
		case Tag::Type::Float:
			res.set(key, Number::newNumber(tag.asFloat()));
			break;
		case Tag::Type::Double:
			res.set(key, Number::newNumber(tag.asDouble()));
			break;
		case Tag::Type::String:
			res.set(key, String::newString(tag.asString()));
			break;
		case Tag::Type::ByteArray:
		{
			auto& data = tag.asByteArray();
			res.set(key, ByteBuffer::newByteBuffer(data.data.get(), data.size));
			break;
		}
		case Tag::Type::List:
			if (!autoExpansion)
				res.set(key, NbtListClass::pack(&tag));
			else
				res.set(key, Tag2Value_ListHelper(&tag, autoExpansion));
			break;
		case Tag::Type::Compound:
			if (!autoExpansion)
				res.set(key, NbtCompoundClass::pack(&tag));
			else
				res.set(key, Tag2Value_CompoundHelper(&tag, autoExpansion));
		default:
			res.set(key, Local<Value>());
			break;
		}
	}
	return res;
}

Local<Value> Tag2Value(Tag* nbt, bool autoExpansion)
{
	Local<Value> value;

	switch (nbt->getTag::Type())
	{
	case Tag::Type::End:
		value = Number::newNumber(0);
		break;
	case Tag::Type::Byte:
		value = Number::newNumber(nbt->asByte());
		break;
	case Tag::Type::Short:
		value = Number::newNumber(nbt->asShort());
		break;
	case Tag::Type::Int:
		value = Number::newNumber(nbt->asInt());
		break;
	case Tag::Type::Long:
		value = Number::newNumber(nbt->asLong());
		break;
	case Tag::Type::Float:
		value = Number::newNumber(nbt->asFloat());
		break;
	case Tag::Type::Double:
		value = Number::newNumber(nbt->asDouble());
		break;
	case Tag::Type::String:
		value = String::newString(nbt->asString());
		break;
	case Tag::Type::ByteArray:
	{
		auto& data = nbt->asByteArray();
		value = ByteBuffer::newByteBuffer(data.data.get(), data.size);
		break;
	}
	case Tag::Type::List:
		if (!autoExpansion)
			value = NbtListClass::pack(nbt);
		else
			value = Tag2Value_ListHelper(nbt, autoExpansion);
		break;
	case Tag::Type::Compound:
		if (!autoExpansion)
			value = NbtCompoundClass::pack(nbt);
		else
			value = Tag2Value_CompoundHelper(nbt, autoExpansion);
		break;
	default:
		value = Local<Value>();
		break;
	}
	return value;
}


//////////////////// Tag Set Value ////////////////////

bool TagSetValue_CompoundHelper(Tag* compNbt, Local<Object> value);

bool TagSetValue_ListHelper(Tag* listNbt, Tag::Type listType, Local<Array> value)
{
	for (int i = 0; i < value.size(); ++i)
	{
		switch (listType)
		{
		case Tag::Type::End:
			listNbt->addEnd();
			break;
		case Tag::Type::Byte:
			listNbt->add(NbtByteClass::extract(value.get(i)));
			break;
		case Tag::Type::Short:
			listNbt->add(NbtShortClass::extract(value.get(i)));
			break;
		case Tag::Type::Int:
			listNbt->add(NbtIntClass::extract(value.get(i)));
			break;
		case Tag::Type::Long:
			listNbt->add(NbtLongClass::extract(value.get(i)));
			break;
		case Tag::Type::Float:
			listNbt->add(NbtFloatClass::extract(value.get(i)));
			break;
		case Tag::Type::Double:
			listNbt->add(NbtDoubleClass::extract(value.get(i)));
			break;
		case Tag::Type::String:
			listNbt->add(NbtStringClass::extract(value.get(i)));
			break;
		case Tag::Type::ByteArray:
			listNbt->add(NbtByteArrayClass::extract(value.get(i)));
			break;
		case Tag::Type::List:
		{
			Tag* arrTag = Tag::createTag(Tag::Type::List);

			if (value.get(i).isArray())
			{
				auto arr = value.get(i).asArray();
				if (arr.size() > 0)
				{
					if (IsInstanceOf<NbtEndClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::End, arr);
					else if (IsInstanceOf<NbtByteClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Byte, arr);
					else if (IsInstanceOf<NbtShortClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Short, arr);
					else if (IsInstanceOf<NbtIntClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Int, arr);
					else if (IsInstanceOf<NbtLongClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Long, arr);
					else if (IsInstanceOf<NbtFloatClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Float, arr);
					else if (IsInstanceOf<NbtDoubleClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Double, arr);
					else if (IsInstanceOf<NbtStringClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::String, arr);
					else if (IsInstanceOf<NbtByteArrayClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::ByteArray, arr);
					else if (IsInstanceOf<NbtListClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::List, arr);
					else if (IsInstanceOf<NbtCompoundClass>(arr.get(0)))
						TagSetValue_ListHelper(arrTag, Tag::Type::Compound, arr);
					else
					{
						ERROR("Wrong Type of Data to Set into list!");
					}
				}
			}
			else
			{
				ERROR("Wrong Type of Data!");
				return false;
			}

			listNbt->add(arrTag);
			break;
		}
		case Tag::Type::Compound:
		{
			Tag* objTag = Tag::createTag(Tag::Type::Compound);

			if (value.get(i).isObject())
			{
				auto obj = value.get(i).asObject();
				auto keys = obj.getKeyNames();

				if (keys.size() > 0)
				{
					if (IsNbtClass(obj.get(keys[0])))
					{
						TagSetValue_CompoundHelper(objTag, obj);
					}
					else
					{
						ERROR("Wrong Type of Data to Set into compound!");
					}
				}
			}
			else
			{
				ERROR("Wrong Type of Data!");
				return false;
			}

			listNbt->add(objTag);
			break;
		}
		default:
			return false;
			break;
		}
	}
	return true;
}

bool TagSetValue_CompoundHelper(Tag* compNbt, Local<Object> value)
{
	auto keys = value.getKeyNames();
	for (auto& key : keys)
	{
		auto data = value.get(key);
		if (IsInstanceOf<NbtEndClass>(data))
			compNbt->putEnd(key);
		else if (IsInstanceOf<NbtByteClass>(data))
			compNbt->put(key, NbtByteClass::extract(data));
		else if (IsInstanceOf<NbtShortClass>(data))
			compNbt->put(key, NbtShortClass::extract(data));
		else if (IsInstanceOf<NbtIntClass>(data))
			compNbt->put(key, NbtIntClass::extract(data));
		else if (IsInstanceOf<NbtLongClass>(data))
			compNbt->put(key, NbtLongClass::extract(data));
		else if (IsInstanceOf<NbtFloatClass>(data))
			compNbt->put(key, NbtFloatClass::extract(data));
		else if (IsInstanceOf<NbtDoubleClass>(data))
			compNbt->put(key, NbtDoubleClass::extract(data));
		else if (IsInstanceOf<NbtStringClass>(data))
			compNbt->put(key, NbtStringClass::extract(data));
		else if (IsInstanceOf<NbtByteArrayClass>(data))
			compNbt->put(key, NbtByteArrayClass::extract(data));

		else if (IsInstanceOf<NbtListClass>(data))
			compNbt->put(key, NbtListClass::extract(data));
		else if (IsInstanceOf<NbtCompoundClass>(data))
			compNbt->put(key, NbtCompoundClass::extract(data));
		else if (data.isArray())
		{
			Tag* arrTag = Tag::createTag(Tag::Type::List);

			auto arr = data.asArray();
			if (arr.size() > 0)
			{
				if (IsInstanceOf<NbtEndClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::End, arr);
				else if (IsInstanceOf<NbtByteClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Byte, arr);
				else if (IsInstanceOf<NbtShortClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Short, arr);
				else if (IsInstanceOf<NbtIntClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Int, arr);
				else if (IsInstanceOf<NbtLongClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Long, arr);
				else if (IsInstanceOf<NbtFloatClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Float, arr);
				else if (IsInstanceOf<NbtDoubleClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Double, arr);
				else if (IsInstanceOf<NbtStringClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::String, arr);
				else if (IsInstanceOf<NbtByteArrayClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::ByteArray, arr);
				else if (IsInstanceOf<NbtListClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::List, arr);
				else if (IsInstanceOf<NbtCompoundClass>(arr.get(0)))
					TagSetValue_ListHelper(arrTag, Tag::Type::Compound, arr);
				else
				{
					ERROR("Wrong Type of Data to Set into list!");
				}
			}

			compNbt->put(key, arrTag);
		}
		else if (data.isObject())
		{
			Tag* objTag = Tag::createTag(Tag::Type::Compound);

			auto obj = data.asObject();
			auto keys = obj.getKeyNames();

			if (keys.size() > 0)
			{
				if (IsNbtClass(obj.get(keys[0])))
				{
					TagSetValue_CompoundHelper(objTag, obj);
				}
				else
				{
					ERROR("Wrong Type of Data to Set into compound!");
				}
			}

			compNbt->put(key, objTag);
		}
		else
		{
			ERROR("Wrong Type of Data to Set into compound!");
		}
	}
	return true;
}

bool TagSetValue(Tag::Type type, Tag* nbt, Local<Value> value)
{
	switch (type)
	{
	case Tag::Type::End:
		nbt->asByte() = 0;
		break;
	case Tag::Type::Byte:
		nbt->asByte() = (char)(value.asNumber().toInt32());
		break;
	case Tag::Type::Short:
		nbt->asShort() = (short)(value.asNumber().toInt32());
		break;
	case Tag::Type::Int:
		nbt->asInt() = (int)(value.asNumber().toInt32());
		break;
	case Tag::Type::Long:
		nbt->asLong() = value.asNumber().toInt64();
		break;
	case Tag::Type::Float:
		nbt->asFloat() = value.asNumber().toFloat();
		break;
	case Tag::Type::Double:
		nbt->asDouble() = value.asNumber().toDouble();
		break;
	case Tag::Type::String:
		nbt->asString() = value.toStr();
		break;
	case Tag::Type::ByteArray:
	{
		auto data = value.asByteBuffer();
		TagMemoryChunk& memory = nbt->asByteArray();

		int size = data.byteLength();
		uint8_t* written = new uint8_t[size];
		memcpy(written, data.getRawBytes(), size);

		memory.size = memory.capacity = size;
		memory.data.reset(written);
		break;
	}
	case Tag::Type::List:
	{
		if (value.isArray())
		{
			auto arr = value.asArray();
			if (arr.size() > 0)
			{
				if (IsInstanceOf<NbtEndClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::End, arr);
				else if (IsInstanceOf<NbtByteClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Byte, arr);
				else if (IsInstanceOf<NbtShortClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Short, arr);
				else if (IsInstanceOf<NbtIntClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Int, arr);
				else if (IsInstanceOf<NbtLongClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Long, arr);
				else if (IsInstanceOf<NbtFloatClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Float, arr);
				else if (IsInstanceOf<NbtDoubleClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Double, arr);
				else if (IsInstanceOf<NbtStringClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::String, arr);
				else if (IsInstanceOf<NbtByteArrayClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::ByteArray, arr);
				else if (IsInstanceOf<NbtListClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::List, arr);
				else if (IsInstanceOf<NbtCompoundClass>(arr.get(0)))
					TagSetValue_ListHelper(nbt, Tag::Type::Compound, arr);
				else
				{
					ERROR("Wrong Type of Data to Set into list!");
				}
			}
		}
		else
		{
			ERROR("Wrong Type of Data!");
			return false;
		}
		break;
	}
	case Tag::Type::Compound:
	{
		if (value.isObject())
		{
			auto obj = value.asObject();
			auto keys = obj.getKeyNames();

			if (keys.size() > 0)
			{
				if (IsNbtClass(obj.get(keys[0])))
				{
					TagSetValue_CompoundHelper(nbt, obj);
				}
				else
				{
					ERROR("Wrong Type of Data to Set into compound!");
				}
			}
		}
		else
		{
			ERROR("Wrong Type of Data!");
			return false;
		}
		break;
	}
	default:
		return false;
		break;
	}
	return true;
}