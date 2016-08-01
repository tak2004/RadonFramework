#ifndef RF_MEMORY_POOLALLOCATOR_HPP
#define RF_MEMORY_POOLALLOCATOR_HPP

#include <RadonFramework/Memory/AllocatorBase.hpp>

namespace RadonFramework { namespace Memory {

/// Use this class only for allocation of the same size and alignment.
/// It reserves a large chunk from the specified arena and split it up.
/// By default it's using the SystemAllocator which provide large chunks with no
/// additional footprint.
class PoolAllocator: public AllocatorBase
{
public:
    PoolAllocator(const RF_Type::Size BlockSize, const RF_Type::Size Alignment, 
        AllocatorBase* Arena = nullptr);

    virtual void* Allocate(const RF_Type::Size Bytes, const RF_Type::UInt32 Flag = 0) override;

    virtual void Free(void* Pointer) override;
    /// Return the size of an user allocation.
    virtual RF_Type::Size AllocationSize(void* Pointer) override;
    /// Return the amount of bytes which are allocated.
    virtual RF_Type::Size GetAllocatedBytes() const override;
    /// Return the amount of bytes which are used for allocation purpose.
    virtual RF_Type::Size GetUsedBytes() const override;
    /// Return the amount of bytes which the smallest allocation can handle.
    virtual RF_Type::Size GetAllocationGranularity() const override;
protected:
    /// The size of the allocation is specified with the constructor and unchangeable.
    virtual RF_Type::Size Resize(void* Pointer, const RF_Type::Size NewSize) override;
    /// The size of the allocation is specified with the constructor and unchangeable.
    virtual void* ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize) override;
private:
    struct ObjList;
    ObjList* m_Chunks;
    AllocatorBase* m_Arena;
    RF_Type::AtomicInt64 m_Used;
    RF_Type::AtomicInt64 m_Reserved;
    RF_Type::Size m_BlockSize;
    RF_Type::Size m_Alignment;
    RF_Type::Size m_BlockOffset;
    RF_Type::Size m_ChunkCount;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_POOLALLOCATOR_HPP