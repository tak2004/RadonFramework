#ifndef RF_COLLECTIONS_HASHLIST_HPP
#define RF_COLLECTIONS_HASHLIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Policies {

class ValueAllocator
{
public:
    virtual void* Allocate(RF_Type::Size Bytes, RF_Type::Size Alignment)=0;
    virtual void* Reallocate(void* Ptr, RF_Type::Size NewBytes)=0;
    virtual void Free(void* Memory)=0;
};

}

namespace RadonFramework::Collections {

class HashList
{
public:
    typedef RF_Type::UInt32 KeyType;
    HashList();
    HashList(const RF_Type::Size PreAllocationElementCount);
    HashList(Core::Policies::ValueAllocator* Allocator,
        const RF_Type::Size PreAllocationElementCount);
    ~HashList();
    void Clear();
    RF_Type::Bool Add(const KeyType Key, void* DataStart);
    RF_Type::Bool ContainsKey(const KeyType Key)const;
    RF_Type::Size Count()const;
    RF_Type::Size Capacity()const;
    RF_Type::Bool Get(const KeyType Key, void*& Value)const;
    void Erase(const KeyType Key);
    KeyType GetEmptyKey()const;
    void Clone(const HashList& ThisInstance);
    void Reserve(const RF_Type::Size ElementCount);
private:
    Core::Policies::ValueAllocator* m_Allocator;
    RF_Type::Size m_Count;
    RF_Type::Size m_Capacity;
    // bucket count have to be power of 2 to avoid modulo operation
    RF_Type::Size m_BucketCount;
    RF_Type::Size m_BucketElements;
    KeyType* m_Keys;
    void** m_Values;

    // forbid copies, use Clone() method
    HashList(const HashList&) = delete;
    HashList& operator=(const HashList&) = delete;
    HashList& operator=(HashList) = delete;

    void Grow(const RF_Type::Size ToElementCount);
    RF_Type::Size GetLastBucketElement(RF_Type::Size index, RF_Type::Size j);
    RF_Type::Size FindBucket(const KeyType Key)const;
};

}

#endif