#ifndef RF_MEMORY_SYSTEMALLOCATOR_HPP
#define RF_MEMORY_SYSTEMALLOCATOR_HPP

#include <RadonFramework/Memory/AllocatorBase.hpp>

namespace RadonFramework { namespace Memory {

/// Use this class only for large chunk allocation at the bottom of an allocator stack.
class SystemAllocator : public AllocatorBase
{
public:
    virtual void* Allocate(const RF_Type::Size Bytes, 
        const RF_Type::Size Alignment, const RF_Type::UInt32 Flag = 0) override;

    virtual void Free(void* Pointer) override;

    virtual RF_Type::Size Resize(void* Pointer, const RF_Type::Size NewSize) override;

    virtual void* ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize, 
        const RF_Type::Size Alignment) override;

    virtual RF_Type::Size AllocationSize(void* Pointer) override;

    virtual RF_Type::Size GetAllocatedBytes() const override;

    virtual RF_Type::Size GetUnusedBytes() const override;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_SYSTEMALLOCATOR_HPP