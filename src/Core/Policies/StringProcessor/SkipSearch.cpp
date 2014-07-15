#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/SkipSearch.hpp"

using namespace RadonFramework::Core::Policies::StringProcessor;

SkipSearch::StorageType::StorageType()
:Position(0)
,Occurrence(0)
,Next(0)
{
}

SkipSearch::StorageType::~StorageType()
{
    delete[] Occurrence;
    delete[] Next;
}

RF_Type::Bool SkipSearch::Init(RF_Type::String& Text, 
    const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    Storage->Position=Position;
    // preprocessing
    RF_Type::Int32 i=0,j=0;
    RF_Type::UInt8 a;
    if (Storage->Search.Length()>0)
    {
        delete[] Storage->Occurrence;
        delete[] Storage->Next;
        Storage->Occurrence=new RF_Type::Int32[256];     
        Storage->Next=new RF_Type::Int32[Storage->Search.Length()];
        for (;i<256;++i)
            Storage->Occurrence[i]=-1;

        for(;j<static_cast<RF_Type::Int32>(Storage->Search.Length());++j)
        {
            a=Storage->Search[j];
            Storage->Next[j]=Storage->Occurrence[a];
            Storage->Occurrence[a]=j;
        }
    }
    return true;
}

void SkipSearch::Reset(RF_Type::String& Text, 
    const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 SkipSearch::DoNext(RF_Type::String& Text, 
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
    {
        k=Storage->Occurrence[p1[Storage->Position]];
        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
        {
            if (RadonFramework::System::Memory::Compare(p1+Storage->Position-k,p2,searchLen))
                return Storage->Position-k;
            k=Storage->Next[k];
        }
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 SkipSearch::DoAll(RF_Type::String& Text, 
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
    {
        k=Storage->Occurrence[p1[Storage->Position]];
        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
        {
            if (RadonFramework::System::Memory::Compare(p1+Storage->Position-k,p2,searchLen)==0)
                ++hit;
            k=Storage->Next[k];
        }
    }
    return hit;
}