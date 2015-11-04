#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/HashList.hpp"

namespace RadonFramework { namespace Core { namespace Policies {

class ValueAllocator
{

};

} } }

namespace RadonFramework { namespace Collections {

HashList::HashList()
:m_Allocator(0)
,m_Count(0)
,m_Keys(0)
,m_Values(0)
{

}

HashList::HashList(const RF_Type::Size PreAllocationElementCount)
{

}

HashList::HashList(Core::Policies::ValueAllocator* Allocator, 
    const RF_Type::Size PreAllocationElementCount)
:m_Allocator(Allocator)
, m_Count(PreAllocationElementCount)
, m_Keys(0)
, m_Values(0)
{

}

HashList::~HashList()
{

}

void HashList::Clear()
{

}

RF_Type::Bool HashList::ContainsKey(const RF_Type::UInt32 Key) const
{
    return false;
}

RF_Type::Size HashList::Count() const
{
    return m_Count;
}

void* HashList::operator[](const RF_Type::UInt32 Key)
{
    return 0;
}

void HashList::Erase(const RF_Type::UInt32 Key)
{

}

void HashList::SetEmptyKey(const RF_Type::UInt32 Key)
{

}

} }