#pragma once
#include "APIHelp.h"

#include <MC/Tag.hpp>

extern struct Tag;
extern ClassDefine<void> NbtStaticBuilder;

//NBT Static
class NbtStatic : public ScriptClass
{
public:
    static Local<Value> newTag(const Arguments& args);
    static Local<Value> parseSNBT(const Arguments& args);
    static Local<Value> parseBinaryNBT(const Arguments& args);

    template<Tag::Type T>
    static Local<Value> getType()
    {
        return Number::newNumber((int)T);
    }
};
extern ClassDefine<void> NbtStaticBuilder;


//NBT End
class EndTag;
class NbtEndClass : public ScriptClass
{
public:
    std::unique_ptr<EndTag> nbt;
    explicit NbtEndClass(const Local<Object>& scriptObj, std::unique_ptr<EndTag> p);
    explicit NbtEndClass(std::unique_ptr<EndTag> p);
    ~NbtEndClass() = default;
    static NbtEndClass* constructor(const Arguments& args);
    static EndTag* extract(Local<Value> v);
    static Local<Value> pack(EndTag* tag);
    static Local<Value> pack(std::unique_ptr<EndTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtEndClass> NbtEndClassBuilder;


//NBT Byte
class NbtByteClass : public ScriptClass 
{
public:
    std::unique_ptr<ByteTag> nbt;
    explicit NbtByteClass(const Local<Object>& scriptObj, std::unique_ptr<ByteTag> p);
    explicit NbtByteClass(std::unique_ptr<ByteTag> p);
    NbtByteClass() = default;
    static NbtByteClass* constructor(const Arguments& args);
    static ByteTag* extract(Local<Value> v);
    static Local<Value> pack(ByteTag* tag);
    static Local<Value> pack(std::unique_ptr<ByteTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtByteClass> NbtByteClassBuilder;


//NBT Short
class NbtShortClass : public ScriptClass
{
public:
    std::unique_ptr<ShortTag> nbt;
    explicit NbtShortClass(const Local<Object>& scriptObj, std::unique_ptr<ShortTag> p);
    explicit NbtShortClass(std::unique_ptr<ShortTag> p);
    ~NbtShortClass() = default;
    static NbtShortClass* constructor(const Arguments& args);
    static ShortTag* extract(Local<Value> v);
    static Local<Value> pack(ShortTag* tag);
    static Local<Value> pack(std::unique_ptr<ShortTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtShortClass> NbtShortClassBuilder;


//NBT Int
class NbtIntClass : public ScriptClass
{
public:
    std::unique_ptr<IntTag> nbt;
    explicit NbtIntClass(const Local<Object>& scriptObj, std::unique_ptr<IntTag> p);
    explicit NbtIntClass(std::unique_ptr<IntTag> p);
    ~NbtIntClass() = default;
    static NbtIntClass* constructor(const Arguments& args);
    static IntTag* extract(Local<Value> v);
    static Local<Value> pack(IntTag* tag);
    static Local<Value> pack(std::unique_ptr<IntTag> tag);
    
    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtIntClass> NbtIntClassBuilder;


//NBT Long
class NbtLongClass : public ScriptClass
{
public:
    std::unique_ptr<Int64Tag> nbt;
    explicit NbtLongClass(const Local<Object>& scriptObj, std::unique_ptr<Int64Tag> p);
    explicit NbtLongClass(std::unique_ptr<Int64Tag> p);
    ~NbtLongClass() = default;
    static NbtLongClass* constructor(const Arguments& args);
    static Int64Tag* extract(Local<Value> v);
    static Local<Value> pack(Int64Tag* tag);
    static Local<Value> pack(std::unique_ptr<Int64Tag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtLongClass> NbtLongClassBuilder;


//NBT Float
class NbtFloatClass : public ScriptClass
{
public:
    std::unique_ptr<FloatTag> nbt;
    explicit NbtFloatClass(const Local<Object>& scriptObj, std::unique_ptr<FloatTag> p);
    explicit NbtFloatClass(std::unique_ptr<FloatTag> p);
    ~NbtFloatClass() = default;
    static NbtFloatClass* constructor(const Arguments& args);
    static FloatTag* extract(Local<Value> v);
    static Local<Value> pack(FloatTag* tag);
    static Local<Value> pack(std::unique_ptr<FloatTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtFloatClass> NbtFloatClassBuilder;


//NBT Double
class NbtDoubleClass : public ScriptClass
{
public:
    std::unique_ptr<DoubleTag> nbt;
    explicit NbtDoubleClass(const Local<Object>& scriptObj, std::unique_ptr<DoubleTag> p);
    explicit NbtDoubleClass(std::unique_ptr<DoubleTag> p);
    ~NbtDoubleClass() = default;
    static NbtDoubleClass* constructor(const Arguments& args);
    static DoubleTag* extract(Local<Value> v);
    static Local<Value> pack(DoubleTag* tag);
    static Local<Value> pack(std::unique_ptr<DoubleTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtDoubleClass> NbtDoubleClassBuilder;


//NBT String
class NbtStringClass : public ScriptClass
{
public:
    std::unique_ptr<StringTag> nbt;
    explicit NbtStringClass(const Local<Object>& scriptObj, std::unique_ptr<StringTag> p);
    explicit NbtStringClass(std::unique_ptr<StringTag> p);
    ~NbtStringClass() = default;
    static NbtStringClass* constructor(const Arguments& args);
    static StringTag* extract(Local<Value> v);
    static Local<Value> pack(StringTag* tag);
    static Local<Value> pack(std::unique_ptr<StringTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtStringClass> NbtStringClassBuilder;


//NBT ByteArray
class NbtByteArrayClass : public ScriptClass
{
public:
    std::unique_ptr<ByteArrayTag> nbt;
    explicit NbtByteArrayClass(const Local<Object>& scriptObj, std::unique_ptr<ByteArrayTag> p);
    explicit NbtByteArrayClass(std::unique_ptr<ByteArrayTag> p);
    ~NbtByteArrayClass() = default;
    static NbtByteArrayClass* constructor(const Arguments& args);
    static ByteArrayTag* extract(Local<Value> v);
    static Local<Value> pack(ByteArrayTag* tag);
    static Local<Value> pack(std::unique_ptr<ByteArrayTag> tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtByteArrayClass> NbtByteArrayClassBuilder;


//NBT List
class NbtListClass : public ScriptClass
{
public:
    std::unique_ptr<ListTag> nbt;
    explicit NbtListClass(const Local<Object>& scriptObj, std::unique_ptr<ListTag> p);
    explicit NbtListClass(std::unique_ptr<ListTag> p);
    ~NbtListClass() = default;
    static NbtListClass* constructor(const Arguments& args);
    static ListTag* extract(Local<Value> v);
    static Local<Value> pack(ListTag* tag);
    static Local<Value> pack(std::unique_ptr<ListTag> tag);
    
    Local<Value> getType(const Arguments& args);
    Local<Value> getSize(const Arguments& args);
    Local<Value> getTypeOf(const Arguments& args);

    Local<Value> setEnd(const Arguments& args);
    Local<Value> setByte(const Arguments& args);
    Local<Value> setInt(const Arguments& args);
    Local<Value> setShort(const Arguments& args);
    Local<Value> setLong(const Arguments& args);
    Local<Value> setFloat(const Arguments& args);
    Local<Value> setDouble(const Arguments& args);
    Local<Value> setString(const Arguments& args);
    Local<Value> setByteArray(const Arguments& args);
    Local<Value> setTag(const Arguments& args);
    Local<Value> addTag(const Arguments& args);
    Local<Value> removeTag(const Arguments& args);

    Local<Value> getData(const Arguments& args);
    Local<Value> getTag(const Arguments& args);

    Local<Value> toArray(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtListClass> NbtListClassBuilder;


//NBT Compound
class NbtCompoundClass : public ScriptClass
{
public:
    std::unique_ptr<CompoundTag> nbt;
    explicit NbtCompoundClass(const Local<Object>& scriptObj, std::unique_ptr<CompoundTag> p);
    explicit NbtCompoundClass(std::unique_ptr<CompoundTag> p);
    ~NbtCompoundClass() = default;
    static NbtCompoundClass* constructor(const Arguments& args);
    static CompoundTag* extract(Local<Value> v);
    static Local<Value> pack(CompoundTag* tag);
    static Local<Value> pack(std::unique_ptr<CompoundTag> tag);
    static Local<Value> pack(std::unique_ptr<CompoundTag> &&tag);

    Local<Value> getType(const Arguments& args);
    Local<Value> getKeys(const Arguments& args);
    Local<Value> getTypeOf(const Arguments& args);

    Local<Value> setEnd(const Arguments& args);
    Local<Value> setByte(const Arguments& args);
    Local<Value> setInt(const Arguments& args);
    Local<Value> setShort(const Arguments& args);
    Local<Value> setLong(const Arguments& args);
    Local<Value> setFloat(const Arguments& args);
    Local<Value> setDouble(const Arguments& args);
    Local<Value> setString(const Arguments& args);
    Local<Value> setByteArray(const Arguments& args);
    Local<Value> setTag(const Arguments& args);
    Local<Value> removeTag(const Arguments& args);

    Local<Value> getData(const Arguments& args);
    Local<Value> getTag(const Arguments& args);

    Local<Value> toObject(const Arguments& args);
    Local<Value> toSNBT(const Arguments& args);
    Local<Value> toBinaryNBT(const Arguments& args);
    Local<Value> toString(const Arguments& args);

    Local<Value> destroy(const Arguments& args);
};
extern ClassDefine<NbtCompoundClass> NbtCompoundClassBuilder;


//Helper
bool IsNbtClass(Local<Value> value);
Local<Value> Tag2Value(Tag* nbt, bool autoExpansion = false);
bool TagSetValue(Tag::Type type, Tag* nbt, Local<Value> value = Local<Value>());