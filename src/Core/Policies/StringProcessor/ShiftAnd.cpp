#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/ShiftAnd.hpp"

using namespace RadonFramework::Core::Policies::StringProcessor;

ShiftAnd::StorageType::StorageType()
:Position(0)
,Lastbit(0)
,Shift(0)
{

}

ShiftAnd::StorageType::~StorageType()
{
    delete[] Shift;
}

RF_Type::Bool ShiftAnd::Init(RF_Type::String& Text, 
    const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    if (Storage->Search.Length()>0)
    {
        if (Storage->Search.Length()>32)
            return false;
        Storage->Position=0;
        delete[] Storage->Shift;
        Storage->Shift=new RF_Type::UInt32[256];
        RF_Type::Int32 k=1;
        RF_Type::Int8 a;
        for (RF_Type::Int32 j=0;j<static_cast<RF_Type::Int32>(Storage->Search.Length());++j)
        {
            a=Storage->Search[j];
            Storage->Shift[a]|=k;
            Storage->Lastbit=k;
            k<<=1;
        }
    }
    return true;
}

void ShiftAnd::Reset(RF_Type::String& Text, 
    const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 ShiftAnd::DoNext(RF_Type::String& Text, 
    StorageType* Storage)
{
    RF_Type::UInt32 z=0;
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    for (;Storage->Position<static_cast<RF_Type::Int32>(Text.Length());++Storage->Position)
    {
        z=((z<<1)|1)&Storage->Shift[p1[Storage->Position]];
        if ((z&Storage->Lastbit)!=0)
            return Storage->Position-Storage->Search.Length()-1;
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 ShiftAnd::DoAll(RF_Type::String& Text, 
    StorageType* Storage)
{
    RF_Type::UInt32 z=0,hit=0;
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    for (;Storage->Position<static_cast<RF_Type::Int32>(Text.Length());++Storage->Position)
    {
        z=((z<<1)|1)&Storage->Shift[p1[Storage->Position]];
        if ((z&Storage->Lastbit)!=0)
            ++hit;
    }
    return hit;
}