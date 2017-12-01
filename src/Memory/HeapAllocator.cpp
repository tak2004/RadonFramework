#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/HeapAllocator.hpp"
#include "RadonFramework/System/Memory.hpp"

namespace RadonFramework::Memory {

HeapAllocator::HeapAllocator()
{
    m_BlockSize=RF_SysMem::GetBlockSize();
}

MemoryBlock HeapAllocator::Allocate(const RF_Type::Size Bytes)
{
    RF_Type::Size fittingSize = ((Bytes - 1) / m_BlockSize + 1)* m_BlockSize;
    return {reinterpret_cast<RF_Type::UInt8*>(RF_SysMem::PageAllocate(fittingSize)), fittingSize};
}

void HeapAllocator::Deallocate(const MemoryBlock& Block)
{
    RF_SysMem::PageFree(Block.Data);
}

RF_Type::Bool HeapAllocator::Owns(const MemoryBlock& Block) const
{
    return RF_SysMem::PageAllocationSize(Block.Data)==Block.Bytes;
}

void HeapAllocator::DeallocateAll()
{

}

RF_Type::Size HeapAllocator::m_BlockSize = 0;

}