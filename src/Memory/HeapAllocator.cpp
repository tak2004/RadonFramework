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

void HeapAllocator::Deallocate(MemoryBlock& Block)
{
    RF_SysMem::PageFree(Block.Data);
    Block.Data = nullptr;
    Block.Bytes = 0;
}

RF_Type::Bool HeapAllocator::Owns(const MemoryBlock& Block) const
{
    return RF_SysMem::PageAllocationSize(Block.Data)==Block.Bytes;
}

void HeapAllocator::DeallocateAll()
{

}

MemoryMap HeapAllocator::Map(const RF_Type::Size Bytes)
{
    return {RF_SysMem::MapMemory(nullptr, Bytes)};
}

void HeapAllocator::Unmap(MemoryMap& Mapping)
{
    RF_SysMem::UnmapMemory(Mapping.Handle);
    Mapping.Handle = nullptr;
}

RF_Type::UInt8* HeapAllocator::MapView(const MemoryMap& Map, const RF_Type::Size Bytes, void* View)
{
    return reinterpret_cast<RF_Type::UInt8*>(RF_SysMem::MapView(Map.Handle, Bytes, View));
}

RF_Type::Size HeapAllocator::m_BlockSize = 0;

}