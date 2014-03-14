#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/BruteForce.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Policies::StringProcessor;
using namespace RadonFramework::Core::Policies;

BruteForce::StorageType::StorageType()
:Position(0)
{
}

BruteForce::StorageType::~StorageType()
{
}

Bool BruteForce::Init(String& Text, const UInt32 Position, StorageType* Storage)
{
    Storage->Position=Position;
    return true;
}

void BruteForce::Reset(String& Text, const UInt32 Position, StorageType* Storage)
{
    Storage->Position=Position;
}

Int32 BruteForce::DoNext(String& Text, StorageType* Storage)
{
    UInt8 const* p1=(UInt8*)Text.c_str()+Storage->Position;
    UInt8 const* p2=(UInt8*)Storage->Search.c_str();
    while (Storage->Position+Storage->Search.Length()<Text.Length())
    {

        if (CMemoryOperation::Compare(p1,p2,Storage->Search.Length())==0)
            return Storage->Position;
        ++Storage->Position;
        ++p1;
    }
    Storage->Position=-1;
    return Storage->Position;
}

Int32 BruteForce::DoAll(String& Text, StorageType* Storage)
{
    Int32 hit=0;
    UInt8 const* p1=(UInt8*)Text.c_str()+Storage->Position;
    UInt8 const* p2=(UInt8*)Storage->Search.c_str();
    while (Storage->Position+Storage->Search.Length()<Text.Length())
    {

        if (CMemoryOperation::Compare(p1,p2,Storage->Search.Length())==0)
            ++hit;
        ++Storage->Position;
        ++p1;
    }
    return hit;
}