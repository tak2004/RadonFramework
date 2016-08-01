#ifndef RF_MEMORY_SYSTEMALLOCATOR_HPP
#define RF_MEMORY_SYSTEMALLOCATOR_HPP

#include <RadonFramework/Memory/AllocatorBase.hpp>

namespace RadonFramework { namespace Memory {

/// Use this class only for large chunk allocation at the bottom of an allocator stack.
/// This allocator allocates blocks, use Allocate and AllocationSize to get the real size.
/// You can obtain the minimal block size with GetAllocationGranularity or RF_SysMem::GetRegionSize.
class SystemAllocator : public AllocatorBase
{
public:
    SystemAllocator();

    virtual void* Allocate(const RF_Type::Size Bytes, const RF_Type::UInt32 Flag = 0) override;

    virtual void Free(void* Pointer) override;
    /// Try to resize as close as possible to the specified size of NewSize.
    /// Resize has no effect this have to be implemented on higher level!
    virtual RF_Type::Size Resize(void* Pointer, const RF_Type::Size NewSize) override;
    /// Allocate a new block and move the data.
    virtual void* ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize) override;
    /// Return the size of an user allocation.
    virtual RF_Type::Size AllocationSize(void* Pointer) override;
    /// Return the amount of bytes which are allocated.
    virtual RF_Type::Size GetAllocatedBytes() const override;
    /// Return the amount of bytes which are used for allocation purpose.
    virtual RF_Type::Size GetUsedBytes() const override;
    /// Return the amount of bytes which the smallest allocation can handle.
    virtual RF_Type::Size GetAllocationGranularity() const override;
private:
    RF_Type::AtomicInt64 m_Size;
    static RF_Type::Size m_BlockSize;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_SYSTEMALLOCATOR_HPP