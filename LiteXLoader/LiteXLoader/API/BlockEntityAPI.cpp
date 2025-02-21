#include "APIHelp.h"
#include "BaseAPI.h"
#include "BlockAPI.h"
#include "BlockEntityAPI.h"
#include "NbtAPI.h"
#include <Global.hpp>
#include <MC/BlockActor.hpp>
#include <MC/CompoundTag.hpp>

//////////////////// Class Definition ////////////////////

ClassDefine<BlockEntityClass> BlockEntityClassBuilder =
	defineClass<BlockEntityClass>("LXL_BlockEntity")
		.constructor(nullptr)
		.instanceFunction("getRawPtr", &BlockEntityClass::getRawPtr)

		.instanceProperty("pos", &BlockEntityClass::getPos)
		.instanceProperty("type", &BlockEntityClass::getType)

		.instanceFunction("setNbt", &BlockEntityClass::setNbt)
		.instanceFunction("getNbt", &BlockEntityClass::getNbt)
		.instanceFunction("getBlock", &BlockEntityClass::getBlock)
		.build();


//////////////////// Classes ////////////////////

BlockEntityClass::BlockEntityClass(BlockActor* be, int dim)
	:ScriptClass(ScriptClass::ConstructFromCpp<BlockEntityClass>{}),blockEntity(be),dim(dim)
{ }

Local<Object> BlockEntityClass::newBlockEntity(BlockActor * be,int dim)
{
	auto newp = new BlockEntityClass(be, dim);
	return newp->getScriptObject();
}

//生成函数
BlockActor* BlockEntityClass::extract(Local<Value> v)
{
	if (EngineScope::currentEngine()->isInstanceOf<BlockEntityClass>(v))
		return EngineScope::currentEngine()->getNativeInstance<BlockEntityClass>(v)->get();
	else
		return nullptr;
}

//成员函数
Local<Value> BlockEntityClass::getRawPtr(const Arguments& args)
{
	try {
		return Number::newNumber((intptr_t)blockEntity);
	}
	CATCH("Fail in getRawPtr!")
}

Local<Value> BlockEntityClass::getPos()
{
	try {
		return IntPos::newPos(blockEntity->getPosition(), dim);
	}
	CATCH("Fail in getBlockEntityPos!")
}

Local<Value> BlockEntityClass::getType()
{
	try {
		return Number::newNumber((int)blockEntity->getType());
	}
	CATCH("Fail in getBlockEntityType!")
}

Local<Value> BlockEntityClass::getNbt(const Arguments& args)
{
	try {
		return NbtCompoundClass::pack(blockEntity->getNbt(), true);
	}
	CATCH("Fail in getNbt!")
}

Local<Value> BlockEntityClass::setNbt(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);

	try {
		auto nbt = NbtCompoundClass::extract(args[0]);
		if (!nbt)
			return Local<Value>();    //Null

		blockEntity->setNbt(nbt);
		return Boolean::newBoolean(true);
	}
	CATCH("Fail in setNbt!")
}

Local<Value> BlockEntityClass::getBlock(const Arguments& args)
{
	try {
		BlockPos bp = blockEntity->getPosition();
		return BlockClass::newBlock(Level::getBlock(bp, dim), &bp, dim);
	}
	CATCH("Fail in getBlock!")
}