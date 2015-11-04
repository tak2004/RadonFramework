#ifndef RF_COLLECTIONS_HASHLIST_HPP
#define RF_COLLECTIONS_HASHLIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Policies {

class ValueAllocator;

} } }

namespace RadonFramework { namespace Collections {

class HashList
{
public:
    HashList() RF_NOEXCEPT;
    HashList(const RF_Type::Size PreAllocationElementCount) RF_NOEXCEPT;
    HashList(Core::Policies::ValueAllocator* Allocator,
        const RF_Type::Size PreAllocationElementCount) RF_NOEXCEPT;
    ~HashList() RF_NOEXCEPT;
    void Clear();
    RF_Type::Bool ContainsKey(const RF_Type::UInt32 Key)const;
    RF_Type::Size Count()const;
    void* operator[](const RF_Type::UInt32 Key);
    void Erase(const RF_Type::UInt32 Key);
    void SetEmptyKey(const RF_Type::UInt32 Key);
    void Clone(const HashList& ThisInstance);
private:
    Core::Policies::ValueAllocator* m_Allocator;
    RF_Type::Size m_Count;
    RF_Type::UInt32** m_Keys;
    void** m_Values;

    // forbid copies, use Clone() method
    HashList(const HashList& Copy) = delete;
    HashList& operator=(const HashList& Copy) = delete;
};

} }

#endif