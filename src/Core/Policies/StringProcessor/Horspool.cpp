#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/Horspool.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Policies::StringProcessor;
using namespace RadonFramework::Core::Policies;

Horspool::StorageType::StorageType()
:Position(0)
,Occurrence(0)
{
}

Horspool::StorageType::~StorageType()
{
    delete[] Occurrence;
}

Bool Horspool::Init(String& Text, const Size Position, StorageType* Storage)
{
    Storage->Position=Position;
    // preprocessing
    Size i=0, j=0, m=Storage->Search.Length()-1;
    UInt8 a;
    if (Storage->Search.Length()>0)
    {
        delete[] Storage->Occurrence;
        Storage->Occurrence=new Size[256];
        for (;i<256;++i)
            Storage->Occurrence[i]=-1;

        for(;j<m;++j)
        {
            a=Storage->Search[j];
            Storage->Occurrence[a]=j;
        }
    }
    return true;
}

void Horspool::Reset(String& Text, const Size Position, StorageType* Storage)
{
    Storage->Position=Position;
}

Size Horspool::DoNext(String& Text, StorageType* Storage)
{
    UInt8 const* p1=(UInt8*)Text.c_str();
    UInt8 const* p2=(UInt8*)Storage->Search.c_str();
    Int32 i=0,txtLen=Text.Length(),searchLen=Storage->Search.Length(),
                    searchLenMinusOne=searchLen-1;
    while (Storage->Position<=txtLen-searchLen)
    {
        i=searchLenMinusOne;
        while(i>=0 && p2[i]==p1[Storage->Position+i])
            --i;
        if (i<0)
            return Storage->Position;
        Storage->Position+=searchLenMinusOne;
        Storage->Position-=Storage->Occurrence[p1[Storage->Position]];
    }
    Storage->Position=-1;
    return Storage->Position;
}

Size Horspool::DoAll(String& Text, StorageType* Storage)
{
    UInt8 const* p1=(UInt8*)Text.c_str();
    UInt8 const* p2=(UInt8*)Storage->Search.c_str();
    Int32 i=0,txtLen=Text.Length(),searchLen=Storage->Search.Length();
    Int32 hit=0,searchLenMinusOne=searchLen-1;
    while (Storage->Position<=txtLen-searchLen)
    {
        i=searchLenMinusOne;
        while(i>=0 && p2[i]==p1[Storage->Position+i])
            --i;
        if (i<0)
            ++hit;
        Storage->Position+=searchLenMinusOne;
        Storage->Position-=Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}

Size Horspool::DoAll(AutoPointerArray<Size>& Indices, String& Text, StorageType* Storage)
{
    UInt8 const* p1=(UInt8*)Text.c_str();
    UInt8 const* p2=(UInt8*)Storage->Search.c_str();
    Int32 i=0, txtLen=Text.Length(), searchLen=Storage->Search.Length();
    Int32 hit=0, searchLenMinusOne=searchLen-1;
    while (Storage->Position<=txtLen-searchLen)
    {
        i=searchLenMinusOne;
        while(i>=0 && p2[i]==p1[Storage->Position+i])
            --i;
        if (i<0)
        {// a hit
            if (hit<static_cast<Int32>(Indices.Count()))
                Indices[hit]=Storage->Position;
            else
            {// not enought space in array
                AutoPointerArray<Size> tmp;
                if (Indices.Count()>0)
                {// resize
                    tmp=AutoPointerArray<Size>(Indices.Count()<<1);
                    CMemoryOperation::Copy(tmp.Get(), Indices.Get(), Indices.Count());
                }
                else// initialize
                    tmp=AutoPointerArray<Size>(2);
                Indices.Swap(tmp);
                Indices[hit-1]=Storage->Position;
            }   
            ++hit;
        }
        Storage->Position+=searchLenMinusOne;
        Storage->Position-=Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}