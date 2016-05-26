#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringProcessor/Sunday.hpp"

namespace RadonFramework { namespace Text { namespace StringProcessors {

Sunday::StorageType::StorageType()
:Position(0)
,Occurrence(0)
{
}

Sunday::StorageType::~StorageType()
{
    delete[] Occurrence;
}

RF_Type::Bool Sunday::Init(RF_Type::String& Text,
    const RF_Type::UInt32 Position,
    StorageType* Storage)
{
    Storage->Position = Position;
    // preprocessing
    RF_Type::Int32 i = 0, j = 0;
    RF_Type::UInt8 a;
    if(Storage->Search.Length() > 0)
    {
        delete[] Storage->Occurrence;
        Storage->Occurrence = new RF_Type::Int32[256];
        for(; i < 256; ++i)
            Storage->Occurrence[i] = -1;

        for(; j < static_cast<RF_Type::Int32>(Storage->Search.Length()); ++j)
        {
            a = Storage->Search[j];
            Storage->Occurrence[a] = j;
        }
    }
    return true;
}

void Sunday::Reset(RF_Type::String& Text,
    const RF_Type::UInt32 Position,
    StorageType* Storage)
{
    Storage->Position = Position;
}

RF_Type::Int32 Sunday::DoNext(RF_Type::String& Text,
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen = Text.Length(), searchLen = Storage->Search.Length();
    RF_Type::Int32 hit = 0;
    while(Storage->Position <= txtLen - searchLen)
    {
        if(RadonFramework::System::Memory::Compare(p1 + Storage->Position, p2, searchLen) == 0)
        {
            Storage->Position += searchLen;
            return Storage->Position;
        }
        Storage->Position += searchLen;
        if(Storage->Position < txtLen)
            Storage->Position -= Storage->Occurrence[p1[Storage->Position]];
    }
    Storage->Position = -1;
    return Storage->Position;
}

RF_Type::Int32 Sunday::DoAll(RF_Type::String& Text,
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen = Text.Length(), searchLen = Storage->Search.Length();
    RF_Type::Int32 hit = 0;
    while(Storage->Position <= txtLen - searchLen)
    {
        if(RadonFramework::System::Memory::Compare(p1 + Storage->Position, p2, searchLen) == 0)
            ++hit;
        Storage->Position += searchLen;
        if(Storage->Position < txtLen)
            Storage->Position -= Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}

} } }