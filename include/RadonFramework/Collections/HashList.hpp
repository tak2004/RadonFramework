#ifndef RF_COLLECTIONS_HASHLIST_HPP
#define RF_COLLECTIONS_HASHLIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Policies {

class ValueAllocator
{
public:
    virtual void* Allocate(RF_Type::Size Bytes)=0;
    virtual void* Reallocate(void* Ptr, RF_Type::Size NewBytes)=0;
    virtual void Free(void* Memory)=0;
};

} } }

namespace RadonFramework { namespace Collections {

class HashList
{
public:
    typedef RF_Type::UInt32 KeyType;
    HashList() RF_NOEXCEPT;
    HashList(const RF_Type::Size PreAllocationElementCount) RF_NOEXCEPT;
    HashList(Core::Policies::ValueAllocator* Allocator,
        const RF_Type::Size PreAllocationElementCount) RF_NOEXCEPT;
    ~HashList() RF_NOEXCEPT;
    void Clear();
    RF_Type::Bool Add(const KeyType Key, void* DataStart);
    RF_Type::Bool ContainsKey(const KeyType Key)const;
    RF_Type::Size Count()const;
    RF_Type::Size Capacity()const;
    RF_Type::Bool Get(const KeyType Key, void*& Value)const;
    void Erase(const KeyType Key);
    void SetEmptyKey(const KeyType Key);
    KeyType GetEmptyKey()const;
    void Clone(const HashList& ThisInstance);
private:
    Core::Policies::ValueAllocator* m_Allocator;
    RF_Type::Size m_Count;
    RF_Type::Size m_Capacity;
    KeyType* m_Keys;
    void** m_Values;
    KeyType m_EmptyKey;

    // forbid copies, use Clone() method
    HashList(const HashList&) = delete;
    HashList& operator=(const HashList&) = delete;
    HashList& operator=(HashList) = delete;

    void Grow(const RF_Type::Size ToElementCount);
};

} }

#endif