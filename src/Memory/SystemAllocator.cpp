#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/SystemAllocator.hpp"

namespace RadonFramework { namespace Memory {

void* SystemAllocator::Allocate(const RF_Type::Size Bytes, 
    const RF_Type::Size Alignment, const RF_Type::UInt32 Flag /*= 0*/)
{
    return nullptr;
}

void SystemAllocator::Free(void* Pointer)
{
}

RF_Type::Size SystemAllocator::Resize(void* Pointer, const RF_Type::Size NewSize)
{
    return 0;
}

void* SystemAllocator::ResizeOrAllocate(void* Pointer, 
    const RF_Type::Size NewSize, const RF_Type::Size Alignment)
{
    return nullptr;
}

RF_Type::Size SystemAllocator::AllocationSize(void* Pointer)
{
    return 0;
}

RF_Type::Size SystemAllocator::GetAllocatedBytes() const
{
    return 0;
}

RF_Type::Size SystemAllocator::GetUnusedBytes() const
{
    return 0;
}

} }