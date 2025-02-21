#include "APIHelp.h"
#include "BaseAPI.h"
#include "McAPI.h"
#include "BlockAPI.h"
#include "ContainerAPI.h"
#include "EntityAPI.h"
#include "BlockEntityAPI.h"
#include "NbtAPI.h"
#include <MC/Level.hpp>
#include <MC/Block.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/BlockSource.hpp>
#include <MC/BlockInstance.hpp>
#include <MC/BlockActor.hpp>
#include <exception>

//////////////////// Class Definition ////////////////////

ClassDefine<BlockClass> BlockClassBuilder =
    defineClass<BlockClass>("LXL_Block")
        .constructor(nullptr)
        .instanceFunction("getRawPtr", &BlockClass::getRawPtr)
        
        .instanceProperty("name", &BlockClass::getName)
        .instanceProperty("type", &BlockClass::getType)
        .instanceProperty("id", &BlockClass::getId)
        .instanceProperty("pos", &BlockClass::getPos)
        .instanceProperty("tileData", &BlockClass::getTileData)

        .instanceFunction("setNbt", &BlockClass::setNbt)
        .instanceFunction("getNbt", &BlockClass::getNbt)
        .instanceFunction("getBlockState", &BlockClass::getBlockState)
        .instanceFunction("hasContainer", &BlockClass::hasContainer)
        .instanceFunction("getContainer", &BlockClass::getContainer)
        .instanceFunction("hasBlockEntity", &BlockClass::hasBlockEntity)
        .instanceFunction("getBlockEntity", &BlockClass::getBlockEntity)
        .instanceFunction("removeBlockEntity", &BlockClass::removeBlockEntity)

        //For Compatibility
        .instanceFunction("setTag", &BlockClass::setNbt)
        .instanceFunction("getTag", &BlockClass::getNbt)
        .build();


//////////////////// Classes ////////////////////

BlockClass::BlockClass(Block *p)
    :ScriptClass(ScriptClass::ConstructFromCpp<BlockClass>{}),block(p)
{
    preloadData({ 0,0,0 }, -1);
}

BlockClass::BlockClass(Block *p, BlockPos bp, int dim)
    :ScriptClass(ScriptClass::ConstructFromCpp<BlockClass>{}),block(p)
{
    preloadData(bp, dim);
}

//生成函数
Local<Object> BlockClass::newBlock(Block *p, BlockPos *pos, int dim)
{
    auto newp = new BlockClass(p,*pos,dim);
    return newp->getScriptObject();
}
Local<Object> BlockClass::newBlock(BlockPos* pos, int dim)
{
    return BlockClass::newBlock(Level::getBlock(pos,dim), pos, dim);
}
Local<Object> BlockClass::newBlock(const BlockPos& pos, int dim)
{
    return newBlock((BlockPos*) & pos, dim);
}
Local<Object> BlockClass::newBlock(Block *p, BlockPos *pos, BlockSource *bs)
{
    auto newp = new BlockClass(p,*pos,bs->getDimensionId());
    return newp->getScriptObject();
}
Local<Object> BlockClass::newBlock(IntVec4 pos)
{
    BlockPos bp = { pos.x, pos.y, pos.z };
    return BlockClass::newBlock(Level::getBlock(bp,pos.dim), &bp, pos.dim);
}
Local<Object> BlockClass::newBlock(BlockInstance block)
{
    return BlockClass::newBlock(block.getPosition(), block.getDimensionId());
}
Block* BlockClass::extract(Local<Value> v)
{
    if(EngineScope::currentEngine()->isInstanceOf<BlockClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<BlockClass>(v)->get();
    else
        return nullptr;
}

//成员函数
void BlockClass::preloadData(BlockPos bp, int dim)
{
    name = block->getTypeName(); // TODO
    type = block->getTypeName();
    id = block->getId();
    pos = { bp.x,bp.y,bp.z,dim };
}

Local<Value> BlockClass::getName()
{
    try{
        // 已预加载
        return String::newString(name);
    }
    CATCH("Fail in getBlockName!");
}

Local<Value> BlockClass::getType()
{
    try{
        // 已预加载
        return String::newString(type);
    }
    CATCH("Fail in getBlockType!");
}

Local<Value> BlockClass::getId()
{
    try {
        // 已预加载
        return Number::newNumber(id);
    }
    CATCH("Fail in getBlockId!");
}

Local<Value> BlockClass::getPos()
{
    try{
        // 已预加载
        return IntPos::newPos(pos);
    }
    CATCH("Fail in getBlockPos!");
}

Local<Value> BlockClass::getTileData()
{
    try{
        // 已预加载
        return Number::newNumber(block->getTileData());
    }
    CATCH("Fail in getTileData!");
}

Local<Value> BlockClass::getRawPtr(const Arguments& args)
{
    try {
        return Number::newNumber((intptr_t)block);
    }
    CATCH("Fail in getRawPtr!");
}

Local<Value> BlockClass::getNbt(const Arguments& args)
{
    try {
        return NbtCompoundClass::pack(block->getNbt(), false);
    }
    CATCH("Fail in getNbt!");
}

Local<Value> BlockClass::setNbt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        auto nbt = NbtCompoundClass::extract(args[0]);
        if (!nbt)
            return Local<Value>();    //Null
        
        block->setNbt(nbt);
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in setNbt!")
}

Local<Value> BlockClass::getBlockState(const Arguments& args)
{
    try {
        CompoundTag* list = block->getNbt();
        try
        {
            return Tag2Value((Tag*)list->get<Tag>("states"), true);
        }
        catch (...)
        {
            return Array::newArray();
        }
    }
    catch (const std::out_of_range& e)
    {
        return Object::newObject();
    }
    CATCH("Fail in getBlockState!")
}

Local<Value> BlockClass::hasContainer(const Arguments& args)
{
    try {
        auto bl = Level::getBlockInstance({ pos.x, pos.y, pos.z }, pos.dim);
        return Boolean::newBoolean(bl.hasContainer());
    }
    CATCH("Fail in hasContainer!");
}

Local<Value> BlockClass::getContainer(const Arguments& args)
{
    try {
        Container *container = Level::getBlockInstance({ pos.x, pos.y, pos.z }, pos.dim).getContainer();
        return container ? ContainerClass::newContainer(container) : Local<Value>();
    }
    CATCH("Fail in getContainer!");
}

Local<Value> BlockClass::hasBlockEntity(const Arguments& args)
{
    try {
        return Boolean::newBoolean(block->hasBlockEntity());
    }
    CATCH("Fail in hasBlockEntity!");
}

Local<Value> BlockClass::getBlockEntity(const Arguments& args)
{
    try {
        BlockInstance bl = Level::getBlockInstance(pos.getBlockPos(), pos.dim);
        BlockActor* be = bl.getBlockEntity();
        return be ? BlockEntityClass::newBlockEntity(be,pos.dim) : Local<Value>();
    }
    CATCH("Fail in getBlockEntity!");
}

Local<Value> BlockClass::removeBlockEntity(const Arguments& args)
{
    try {
        BlockSource* bs = Level::getBlockSource(pos.dim);
        bs->removeBlockEntity(pos.getBlockPos());       //==========???
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in removeBlockEntity!");
}

//公用API
Local<Value> McClass::getBlock(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try{
        IntVec4 pos;
        if (args.size() == 1)
        {
            // IntPos
            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = posObj->toIntVec4();
                }
            }
            else
            {
                ERROR("Wrong type of argument in GetBlock!");
                return Local<Value>();
            }
        }
        else if(args.size() == 4)
        {
            // Number Pos
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
            pos = { args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt() };
        }
        else
        {
            ERROR("Wrong number of arguments in GetBlock!");
            return Local<Value>();
        }

        auto block = Level::getBlock(pos.getBlockPos(),pos.dim);
        if (!block)
        {
            ERROR("Wrong type of argument in SetBlock!");
            return Local<Value>();
        }
        else
        {
            BlockPos bp{ pos.x,pos.y,pos.z };
            return BlockClass::newBlock(block, &bp, pos.dim);
        }
    }
    CATCH("Fail in GetBlock!")
}

Local<Value> McClass::setBlock(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);

    try
    {
        IntVec4 pos;
        Local<Value> block;
        unsigned short tileData=0;
        if (args.size() == 2|| args.size() == 3)
        {
            if (args.size() == 3)
            {
                CHECK_ARG_TYPE(args[1], ValueKind::kString);
                CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
                tileData = args[2].toInt();
            }
            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                    block = args[1];
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = posObj->toIntVec4();
                    block = args[1];
                }
            }
            else
            {
                ERROR("Wrong type of argument in SetBlock!");
                return Local<Value>();
            }
        }
        else if (args.size() == 5|| args.size() == 6)
        {
            // Number Pos
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
            pos = { args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt() };
            block = args[4];
            if (args.size() == 6)
            {
                CHECK_ARG_TYPE(args[4], ValueKind::kString);
                CHECK_ARG_TYPE(args[5], ValueKind::kNumber);
                tileData = args[5].toInt();
            }
        }
        else
        {
            ERROR("Wrong number of arguments in SetBlock!");
            return Local<Value>();
        }


        if (block.isString())
        {
            //方块名
            return Boolean::newBoolean(Level::setBlock(pos.getBlockPos(), pos.dim, block.toStr(), tileData));
        }
        else if (IsInstanceOf<NbtCompoundClass>(block))
        {
            //Nbt
            Tag* nbt = NbtCompoundClass::extract(block);
            return Boolean::newBoolean(Level::setBlock(pos.getBlockPos(), pos.dim, (CompoundTag*)nbt));
        }
        else
        {
            //其他方块对象
            Block* bl = BlockClass::extract(block);
            if (!bl)
            {
                ERROR("Wrong type of argument in SetBlock!");
                return Local<Value>();
            }
            return Boolean::newBoolean(Level::setBlock(pos.getBlockPos(), pos.dim, bl));
        }
    }
    CATCH("Fail in SetBlock!")
}

Local<Value> McClass::spawnParticle(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)      

    try
    {
        FloatVec4 pos;
        Local<Value> type;

        if (args.size() == 2)
        {
            // IntPos
            CHECK_ARG_TYPE(args[1], ValueKind::kString);

            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos.x = posObj->x;
                    pos.y = posObj->y;
                    pos.z = posObj->z;
                    pos.dim = posObj->dim;
                    type = args[1];
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                    type = args[1];
                }
            }
            else
            {
                ERROR("Wrong type of argument in SpawnParticle!");
                return Local<Value>();
            }
        }
        else if (args.size() == 5)
        {
            // Number Pos
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[4], ValueKind::kString);

            pos = {  args[0].asNumber().toFloat(), args[1].asNumber().toFloat(), args[2].asNumber().toFloat(), args[3].toInt() };
            type = args[4];
        }
        else
        {
            ERROR("Wrong number of arguments in SpawnParticle!");
            return Local<Value>();
        }

        Level::spawnParticleEffect(type.toStr(), pos.getVec3(), Level::getDimension(pos.dim));
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in SpawnParticle!")
}