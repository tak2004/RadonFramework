#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Policies/MallocAllocator.hpp"

using namespace RadonFramework::Core::Policies;
using namespace RadonFramework::Core::Traits;

void* MallocAllocator::Allocate(AllocatorTraits<void>::SizeType Size)
{
    Assert(Size < RF_Type::MemoryRangeMax,"Acquired memory block is to large.");
    return malloc(Size);
}

void MallocAllocator::Deallocate(void* Ptr, AllocatorTraits<void>::SizeType Size)
{
    free(Ptr);
}

void* MallocAllocator::Reallocate(void* Ptr, 
    AllocatorTraits<void>::SizeType OldSize, 
    AllocatorTraits<void>::SizeType NewSize)
{
    Assert(NewSize < RF_Type::MemoryRangeMax,"Acquired memory block is to large.");
    return realloc(Ptr,NewSize);
}