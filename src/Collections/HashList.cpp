#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/Math/Integer.hpp"
#include <xmmintrin.h>
#include <pmmintrin.h>

namespace RadonFramework { namespace Core { namespace Policies {

class DefaultValueAllocator:public ValueAllocator
{
public:
    void* Allocate(RF_Type::Size Bytes, RF_Type::Size Alignment) 
    {        
        return RF_SysMem::Allocate(Bytes, Alignment);
    }
    void* Reallocate(void* Ptr, RF_Type::Size NewBytes)
    { 
        return 0; 
    }
    void Free(void* Memory) 
    { 
        RF_SysMem::Free(Memory);
    }
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
{
    m_BucketElements = RFHDW::GetLevel1DataCache().LineSize / (sizeof(KeyType) * 4);
    Grow(PreAllocationElementCount);
}

void HashList::Grow(const RF_Type::Size ToElementCount)
{
    if(ToElementCount > m_Capacity)
    {
        RF_Type::Size cacheAlignment = RFHDW::GetLevel1DataCache().LineSize;
        RF_Type::Size pageSize = RF_SysMem::GetPageSize();
        m_BucketCount = ((ToElementCount - 1) / m_BucketElements) +1;
        m_BucketCount = RF_Math::Integer<RF_Type::Size>::NextPowerOfTwo(m_BucketCount);

        RF_Type::Size oldCapacity = m_Capacity;
        m_Capacity = m_BucketCount * m_BucketElements;

        RF_Type::Size neededPages = ((m_Capacity*sizeof(KeyType) - 1) / pageSize) + 1;
        RF_Type::Size valuePages = ((m_Capacity*sizeof(void*) - 1) / pageSize) + 1;

        void* p = m_Allocator->Allocate(pageSize*(neededPages + valuePages), cacheAlignment);
        RF_SysMem::Set(p, 0, pageSize * neededPages);
        KeyType* oldKeys = m_Keys;
        m_Keys = reinterpret_cast<KeyType*>(p);

        p = reinterpret_cast<RF_Type::UInt8*>(p) + pageSize*neededPages;
        RF_SysMem::Set(p, 0, pageSize*valuePages);
        void** oldValues = m_Values;
        m_Values = reinterpret_cast<void**>(p);

        if(oldKeys)
        {
            m_Count = 0;
            for(RF_Type::Size i = 0; i < oldCapacity; ++i)
            {
                if(oldKeys[i] != 0)
                    Add(oldKeys[i], m_Values[i]);
            }

            m_Allocator->Free(oldKeys);
        }
    }
}

inline RF_Type::Size HashList::FindBucket(const KeyType Key)const
{
    return (Key & (m_BucketCount - 1))*m_BucketElements;
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
        KeyType emptyKey = 0;
        RF_SysMem::Set(m_Keys, 0, m_Capacity * sizeof(KeyType));
        RF_SysMem::Set(m_Values, 0, m_Capacity * sizeof(void*));
        m_Count = 0;
    }
}

RF_Type::Bool HashList::Add(const KeyType Key, void* DataStart)
{
    if(m_Count == m_Capacity)
    {
        Grow(m_Capacity + 1);
    }

    RF_Type::Bool result = false;
    RF_Type::Size index = FindBucket(Key);

    __m128i key0 = _mm_set1_epi32(Key);
    __m128i key4 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m_Keys[index]));

    key0 = _mm_cmpeq_epi32(key0, key4);

    if(_mm_movemask_epi8(key0) == 0)
    {// key not found
        key0 = _mm_set1_epi32(0);
        key0 = _mm_cmpeq_epi32(key0, key4);

        if(_mm_movemask_epi8(key0) != 0)
        {// space left in the bucket
            result = true;            
            RF_Type::Size i = 0;
            for (; i < m_BucketElements; ++i)
            {
                if (m_Keys[index+i] == 0)
                    break;
            }
            m_Keys[index+i]=Key;
            m_Values[index+i]=DataStart;
            ++m_Count;
        }
        else
        {// no space left in bucket
            Grow(m_Capacity * 2 );
            result = Add(Key, DataStart);
        }
    }
    return result;
}

RF_Type::Bool HashList::ContainsKey(const KeyType Key) const
{
    RF_Type::Size index = FindBucket(Key);
    __m128i key4 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m_Keys[index]));
    __m128i key0 = _mm_set1_epi32(Key);
    key0 = _mm_cmpeq_epi32(key0, key4);
    return _mm_movemask_epi8(key0) != 0;
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
    RF_Type::Size index = FindBucket(Key);
    __m128i key4 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m_Keys[index]));
    __m128i key0 = _mm_set1_epi32(Key);
    key0 = _mm_cmpeq_epi32(key0, key4);
    int mask = _mm_movemask_epi8(key0);
    switch(mask)
    {
    case 15:
        Value = m_Values[index];
        result = true;
        break;
    case 240:
        Value = m_Values[index+1];
        result = true;
        break;
    case 3840:
        Value = m_Values[index+2];
        result = true;
        break;
    case 61440:
        Value = m_Values[index+3];
        result = true;
        break;
    }
    return result;
}

void HashList::Erase(const KeyType Key)
{
    RF_Type::Bool result = false;
    RF_Type::Size index = FindBucket(Key);
    __m128i key4 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m_Keys[index]));
    __m128i key0 = _mm_set1_epi32(Key);
    key0 = _mm_cmpeq_epi32(key0, key4);
    int mask = _mm_movemask_epi8(key0);
    switch(mask)
    {
    case 15:
        m_Keys[index] = 0;
        break;
    case 240:
        m_Keys[index + 1];
        break;
    case 3840:
        m_Keys[index + 2];
        break;
    case 61440:
        m_Keys[index + 3];
        break;
    }
}

HashList::KeyType HashList::GetEmptyKey() const
{
    return 0;
}

void HashList::Clone(const HashList& ThisInstance)
{
    m_Allocator->Free(m_Keys);
    m_Keys = 0;
    m_Values = 0;
    m_Capacity = 0;
    m_Count = 0;

    Grow(ThisInstance.m_Capacity);
    RF_SysMem::Copy(m_Keys, ThisInstance.m_Keys, m_Capacity * sizeof(KeyType));
    RF_SysMem::Copy(m_Values, ThisInstance.m_Values, m_Capacity * sizeof(void*));
    m_Count = ThisInstance.m_Count;

}

void HashList::Reserve(const RF_Type::Size ElementCount)
{
    Clear();
    Grow(ElementCount*4/3);
}

} }