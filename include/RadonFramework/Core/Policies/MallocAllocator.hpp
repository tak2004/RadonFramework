#ifndef RF_CORE_POLICIES_MALLOCALLOCATOR_HPP
#define RF_CORE_POLICIES_MALLOCALLOCATOR_HPP

#include <RadonFramework/Core/Traits/AllocatorTraits.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <stdlib.h>

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            struct MallocAllocator
            {
                static void* Allocate(Traits::AllocatorTraits<void>::SizeType Size);
                static void Deallocate(void* Ptr,
                                       Traits::AllocatorTraits<void>::SizeType Size);
                static void* Reallocate(void* Ptr, 
                                        Traits::AllocatorTraits<void>::SizeType OldSize, 
                                        Traits::AllocatorTraits<void>::SizeType NewSize);
            };

            void* MallocAllocator::Allocate(Traits::AllocatorTraits<void>::SizeType Size)
            {
                Assert(Size < Core::Types::MemoryRangeMax,"Acquired memory block is to large.");
                return malloc(Size);
            }

            void MallocAllocator::Deallocate(void* Ptr,
                                             Traits::AllocatorTraits<void>::SizeType Size)
            {
                free(Ptr);
            }

            void* MallocAllocator::Reallocate(void* Ptr, 
                                              Traits::AllocatorTraits<void>::SizeType OldSize, 
                                              Traits::AllocatorTraits<void>::SizeType NewSize)
            {
                Assert(NewSize < Core::Types::MemoryRangeMax,"Acquired memory block is to large.");
                return realloc(Ptr,NewSize);
            }
        }
    }
}

#endif // RF_CORE_POLICIES_MALLOCALLOCATOR_HPP