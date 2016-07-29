#ifndef RF_MEMORY_ALLOCATORBASE_HPP
#define RF_MEMORY_ALLOCATORBASE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/Allocator.hpp>

namespace RadonFramework { namespace Memory {

class AllocatorBase
{
public:
    virtual void* Allocate(const RF_Type::Size Bytes, const RF_Type::Size Alignment,
        const RF_Type::UInt32 Flag = 0)=0;
    virtual void Free(void* Pointer)=0;
    /// Try to resize as closed as possible to the specified size of NewSize.
    virtual RF_Type::Size Resize(void* Pointer, const RF_Type::Size NewSize) = 0;
    /// Try to resize to the specified size of NewSize if not possible then
    /// allocate a new block and move the data.
    virtual void* ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize,
        const RF_Type::Size Alignment) = 0;
    /// Return the size of an user allocation.
    virtual RF_Type::Size AllocationSize(void* Pointer) = 0;
    /// Return the amount of bytes which are allocated and used.
    virtual RF_Type::Size GetAllocatedBytes()const = 0;
    /// Return the amount of bytes which are allocated but not used.
    virtual RF_Type::Size GetUnusedBytes()const = 0;
};

} }

#endif // RF_MEMORY_ALLOCATORBASE_HPP