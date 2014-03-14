#ifndef RF_STACKALLOCATOR_HPP
#define RF_STACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework
{
    namespace Memory
    {
        class StackAllocator
        {
            public:
                StackAllocator(RFTYPE::Size ReservedMemorySize);
                void Clear();
                void* Push(RFTYPE::Size MemorySize);
                void Pop();
                void* Peek()const;
                RFTYPE::Size PeekSize()const;

                void ZeroPopedMemory(RFTYPE::Bool choice);
                void ZeroFreedMemory(RFTYPE::Bool choice);
                RFTYPE::Bool ZeroFreedMemory()const;
                RFTYPE::Bool ZeroPopedMemory()const;
            protected:
                Memory::AutoPointerArray<RFTYPE::UInt8> m_ReservedMemory;
                RFTYPE::Size m_AllocatedMemorySize;
                RFTYPE::Bool m_ZeroFreedMemory;
                RFTYPE::Bool m_ZeroPopedMemory;

                RFTYPE::Size* GetSize()const;
        };

        inline RFTYPE::Bool StackAllocator::ZeroFreedMemory()const
        {
            return m_ZeroFreedMemory;
        }

        inline RFTYPE::Bool StackAllocator::ZeroPopedMemory()const
        {
            return m_ZeroPopedMemory;
        }

        inline void StackAllocator::ZeroPopedMemory(RFTYPE::Bool choice)
        {
            m_ZeroPopedMemory=choice;
        }

        inline void StackAllocator::ZeroFreedMemory(RFTYPE::Bool choice)
        {
            m_ZeroFreedMemory=choice;
        }
    }
}

#endif
