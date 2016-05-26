#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringProcessor/Horspool.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

namespace RadonFramework { namespace Text { namespace StringProcessors {

Horspool::StorageType::StorageType()
:Position(0)
,Occurrence(0)
{
}

Horspool::StorageType::~StorageType()
{
    delete[] Occurrence;
}

RF_Type::Bool Horspool::Init(RF_Type::String& Text, const RF_Type::Size Position, 
    StorageType* Storage)
{
    Storage->Position = Position;
    // preprocessing
    RF_Type::Size i = 0, j = 0, m = Storage->Search.Length() - 1;
    RF_Type::UInt8 a;
    if(Storage->Search.Length() > 0)
    {
        delete[] Storage->Occurrence;
        Storage->Occurrence = new RF_Type::Size[256];
        for(; i < 256; ++i)
            Storage->Occurrence[i] = -1;

        for(; j < m; ++j)
        {
            a = Storage->Search[j];
            Storage->Occurrence[a] = j;
        }
    }
    return true;
}

void Horspool::Reset(RF_Type::String& Text, const RF_Type::Size Position, 
    StorageType* Storage)
{
    Storage->Position = Position;
}

RF_Type::Size Horspool::DoNext(RF_Type::String& Text, StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i = 0, txtLen = Text.Length(), searchLen = Storage->Search.Length(),
        searchLenMinusOne = searchLen - 1;
    while(Storage->Position <= txtLen - searchLen)
    {
        i = searchLenMinusOne;
        while(i >= 0 && p2[i] == p1[Storage->Position + i])
            --i;
        if(i < 0)
            return Storage->Position;
        Storage->Position += searchLenMinusOne;
        Storage->Position -= Storage->Occurrence[p1[Storage->Position]];
    }
    Storage->Position = -1;
    return Storage->Position;
}

RF_Type::Size Horspool::DoAll(RF_Type::String& Text, StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i = 0, txtLen = Text.Length(), searchLen = Storage->Search.Length();
    RF_Type::Int32 hit = 0, searchLenMinusOne = searchLen - 1;
    while(Storage->Position <= txtLen - searchLen)
    {
        i = searchLenMinusOne;
        while(i >= 0 && p2[i] == p1[Storage->Position + i])
            --i;
        if(i < 0)
            ++hit;
        Storage->Position += searchLenMinusOne;
        Storage->Position -= Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}

RF_Type::Size Horspool::DoAll(RF_Mem::AutoPointerArray<RF_Type::Size>& Indices, 
    RF_Type::String& Text, StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i = 0, txtLen = Text.Length(), searchLen = Storage->Search.Length();
    RF_Type::Int32 hit = 0, searchLenMinusOne = searchLen - 1;
    while(Storage->Position <= txtLen - searchLen)
    {
        i = searchLenMinusOne;
        while(i >= 0 && p2[i] == p1[Storage->Position + i])
            --i;
        if(i < 0)
        {// a hit
            if(hit < static_cast<RF_Type::Int32>(Indices.Count()))
                Indices[hit] = Storage->Position;
            else
            {// not enough space in array
                RF_Mem::AutoPointerArray<RF_Type::Size> tmp;
                if(Indices.Count() > 0)
                {// resize
                    tmp = RF_Mem::AutoPointerArray<RF_Type::Size>(Indices.Count() << 1);
                    RF_Policy::CMemoryOperation::Copy(tmp.Get(), Indices.Get(), Indices.Count());
                }
                else// initialize
                    tmp = RF_Mem::AutoPointerArray<RF_Type::Size>(2);
                Indices.Swap(tmp);
                Indices[hit - 1] = Storage->Position;
            }
            ++hit;
        }
        Storage->Position += searchLenMinusOne;
        Storage->Position -= Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}

} } }