#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/LinearAllocator.hpp"
#include "RadonFramework/System/Memory.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

LinearAllocator* LinearAllocator::CreateInstance(const Size MemorySize )
{
    Size memoryBlockSize = MemorySize + sizeof(LinearAllocator) + 15;// +15 Byte to ensure 16Byte alignment
    LinearAllocator* allocator = reinterpret_cast<LinearAllocator*>(RF_SysMem::Allocate(memoryBlockSize, 16));
    allocator->m_TotalSize = memoryBlockSize;
    Size next16ByteBoundary = reinterpret_cast<MemoryRange>(allocator) - (reinterpret_cast<MemoryRange>(allocator) & ~15);
    allocator->m_OffsetToFirstFreeByte = sizeof(LinearAllocator) + next16ByteBoundary;
    return allocator;
}

void LinearAllocator::FreeInstance(LinearAllocator*& Instance)
{
    if (Instance->m_TotalSize > 0)
    {
        RF_SysMem::Free(Instance);
        Instance = 0;
    }
}

void LinearAllocator::Clear()
{
    Size next16ByteBoundary = reinterpret_cast<MemoryRange>(this) - (reinterpret_cast<MemoryRange>(this) & ~15);
    m_OffsetToFirstFreeByte = sizeof(LinearAllocator) + next16ByteBoundary;
}

void* LinearAllocator::Allocate(const Size Bytes)
{
    void* result = 0;
    if (m_OffsetToFirstFreeByte + Bytes <= m_TotalSize)
    {
        result = reinterpret_cast<UInt8*>(this) + m_OffsetToFirstFreeByte;
        if (Bytes & 0xf)
            m_OffsetToFirstFreeByte += (Bytes & ~0xf) + 16;
        else
            m_OffsetToFirstFreeByte += Bytes;
    }
    return result;
}