#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringProcessor/BruteForce.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

namespace RadonFramework::Text::StringProcessors {

BruteForce::StorageType::StorageType()
:Position(0)
{
}

BruteForce::StorageType::~StorageType()
{
}

RF_Type::Bool BruteForce::Init(RF_Type::String& Text, const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    Storage->Position=Position;
    return true;
}

void BruteForce::Reset(RF_Type::String& Text, const RF_Type::UInt32 Position, 
    StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 BruteForce::DoNext(RF_Type::String& Text, StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str()+Storage->Position;
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    while (Storage->Position+Storage->Search.Length()<Text.Length())
    {

        if (RF_Policy::CMemoryOperation::Compare(p1,p2,Storage->Search.Length())==0)
            return Storage->Position;
        ++Storage->Position;
        ++p1;
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 BruteForce::DoAll(RF_Type::String& Text, StorageType* Storage)
{
    RF_Type::Int32 hit=0;
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str()+Storage->Position;
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    while (Storage->Position+Storage->Search.Length()<Text.Length())
    {

        if (RF_Policy::CMemoryOperation::Compare(p1,p2,Storage->Search.Length())==0)
            ++hit;
        ++Storage->Position;
        ++p1;
    }
    return hit;
}

}