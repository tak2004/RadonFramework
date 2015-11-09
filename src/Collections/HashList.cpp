#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/Math/Integer.hpp"

namespace RadonFramework { namespace Core { namespace Policies {

class DefaultValueAllocator:public ValueAllocator
{
public:
    void* Allocate(RF_Type::Size Bytes) { return malloc(Bytes); }
    void* Reallocate(void* Ptr, RF_Type::Size NewBytes) { return realloc(Ptr, NewBytes); }
    void Free(void* Memory) { free(Memory); }
};

} } }

RadonFramework::Core::Policies::DefaultValueAllocator defaultAllocator;

namespace RadonFramework { namespace Collections {

HashList::HashList()
:HashList(0)
{

}

HashList::HashList(const RF_Type::Size PreAllocationElementCount)
:HashList(&defaultAllocator, PreAllocationElementCount)
{

}

HashList::HashList(Core::Policies::ValueAllocator* Allocator, 
    const RF_Type::Size PreAllocationElementCount)
:m_Allocator(Allocator)
,m_Count(0)
,m_Capacity(0)
,m_Keys(0)
,m_Values(0)
,m_EmptyKey(0)
{
    Grow(PreAllocationElementCount);
}

void HashList::Grow(const RF_Type::Size ToElementCount)
{
    if(ToElementCount > m_Capacity)
    {
        RF_Type::Size powerOfTwoCapacity = RF_Math::Integer<RF_Type::Size>::NextPowerOfTwo(ToElementCount);
        RF_Type::Size pageSize = RF_SysMem::GetPageSize();
        RF_Type::Size capacityPerPage = ((pageSize - 1) / sizeof(KeyType)) +1;
        RF_Type::Size neededPages = ((powerOfTwoCapacity-1) / capacityPerPage)+1;
        RF_Type::Size valuePages = ((powerOfTwoCapacity * sizeof(void*) - 1) / pageSize) + 1;

        void* p = m_Allocator->Allocate(pageSize*(neededPages + valuePages));
        RF_SysMem::Fill(p, &m_EmptyKey, sizeof(KeyType), pageSize * neededPages);
        KeyType* oldKeys = m_Keys;
        m_Keys = reinterpret_cast<KeyType*>(p);

        p = reinterpret_cast<RF_Type::UInt8*>(p)+pageSize*neededPages;
        RF_SysMem::Set(p, 0, pageSize*valuePages);
        void** oldValues = m_Values;
        m_Values = reinterpret_cast<void**>(p);

        RF_Type::Size oldCapacity = m_Capacity;
        m_Capacity = powerOfTwoCapacity;

        if(oldKeys)
        {
            m_Count = 0;
            for(RF_Type::Size i = 0; i < oldCapacity; ++i)
            {
                if(oldKeys[i] != m_EmptyKey)
                    Add(oldKeys[i], m_Values[i]);
            }

            m_Allocator->Free(oldKeys);
        }
    }
}

HashList::~HashList()
{
    m_Allocator->Free(m_Keys);
    m_Keys = 0;
    m_Values = 0;
}

void HashList::Clear()
{
    if(m_Count > 0)
    {
        RF_SysMem::Fill(m_Keys, &m_EmptyKey, sizeof(KeyType), m_Capacity * sizeof(KeyType));
        RF_SysMem::Set(m_Values, 0, m_Capacity * sizeof(void*));
        m_Count = 0;
    }
}

RF_Type::Bool HashList::Add(const KeyType Key, void* DataStart)
{
    if(m_Count >= m_Capacity/3)
    {
        Grow(m_Capacity+1);
    }

    RF_Type::Bool result = false;
    RF_Type::Size index = Key & (m_Capacity - 1);
    KeyType offset = 0;
    while(m_Keys[index] != m_EmptyKey)
    {
        if(m_Keys[index] == Key)
        {
            break;
        }
        else
        {
            ++offset;
            index = (Key + (offset*(offset+1)/2)) & (m_Capacity - 1);
        }
    }

    if(m_Keys[index] == m_EmptyKey)
    {
        m_Keys[index] = Key;
        m_Values[index] = DataStart;
        result = true;
        ++m_Count;
    }

    return result;
}

RF_Type::Bool HashList::ContainsKey(const KeyType Key) const
{
    RF_Type::Bool result = false;
    RF_Type::Size index = Key & (m_Capacity-1);
    for(RF_Type::Size i = 0; i < m_Capacity; ++i)
    {
        if(m_Keys[index] == m_EmptyKey)
        {
            break;
        }
        else
        {
            if(m_Keys[index] == Key)
            {
                result = true;
                break;
            }
            index = (Key + i*i) & (m_Capacity - 1);
        }
    }
    return result;
}

RF_Type::Size HashList::Count() const
{
    return m_Count;
}

RF_Type::Size HashList::Capacity() const
{
    return m_Capacity;
}

RF_Type::Bool HashList::Get(const KeyType Key, void*& Value) const
{
    RF_Type::Bool result = false;
    RF_Type::Size index = Key & (m_Capacity - 1);
    for (RF_Type::Size i = 0; i < m_Capacity; ++i)
    {
        if(m_Keys[index] == m_EmptyKey)
        {
            break;
        }
        else
        {
            if(m_Keys[index] == Key)
            {
                result = true;
                Value = m_Values[index];
                break;
            }
            index = (Key + i*i) & (m_Capacity - 1);
        }
    }

    return result;
}

void HashList::Erase(const KeyType Key)
{
    RF_Type::Size index = Key & (m_Capacity - 1);
    for(RF_Type::Size i = 0; i < m_Capacity; ++i)
    {
        if(m_Keys[index] == Key || m_Keys[index] == m_EmptyKey)
        {
            m_Values[index] = 0;
            m_Keys[index] = m_EmptyKey;
            return;
        }
        index = (Key + i*i) & (m_Capacity - 1);
    }
}

void HashList::SetEmptyKey(const KeyType Key)
{
    for(RF_Type::Size i = 0; i < m_Capacity; ++i)
    {
        if(m_Keys[i] == m_EmptyKey)
        {
            m_Keys[i] = Key;
        }
    }
    m_EmptyKey = Key;
}

HashList::KeyType HashList::GetEmptyKey() const
{
    return m_EmptyKey;
}

void HashList::Clone(const HashList& ThisInstance)
{
    m_Allocator->Free(m_Keys);
    m_Keys = 0;
    m_Values = 0;
    m_Capacity = 0;
    m_EmptyKey = ThisInstance.m_EmptyKey;
    m_Count = 0;

    Grow(ThisInstance.m_Capacity);
    RF_SysMem::Copy(m_Keys, ThisInstance.m_Keys, m_Capacity * sizeof(KeyType));
    RF_SysMem::Copy(m_Values, ThisInstance.m_Values, m_Capacity * sizeof(void*));
    m_Count = ThisInstance.m_Count;

}

void HashList::Reserve(const RF_Type::Size ElementCount)
{
    Clear();
    Grow(ElementCount*3);
}

} }