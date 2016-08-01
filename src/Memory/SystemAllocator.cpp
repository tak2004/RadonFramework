#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/SystemAllocator.hpp"

namespace RadonFramework { namespace Memory {

RF_Type::Size SystemAllocator::m_BlockSize = RF_SysMem::GetBlockSize();

SystemAllocator::SystemAllocator()
{
    m_Size = 0;
}

void* SystemAllocator::Allocate(const RF_Type::Size Bytes, const RF_Type::UInt32 Flag /*= 0*/)
{    
    static RF_Type::Size PageSizeMask = ~(m_BlockSize - 1);
    if(Bytes > 0)
    {        
        auto blockSize = ((Bytes - 1) & PageSizeMask) + m_BlockSize;
        m_Size.Add(blockSize);
        return RF_SysMem::PageAllocate(blockSize);
    }
    else
    {
        return 0;
    }
}

void SystemAllocator::Free(void* Pointer)
{
    auto blockSize = RF_SysMem::PageAllocationSize(Pointer);
    if(blockSize > 0)
    {
        m_Size.Add(-blockSize);
        RF_SysMem::PageFree(Pointer);
    }
}

RF_Type::Size SystemAllocator::Resize(void* Pointer, const RF_Type::Size NewSize)
{
    return RF_SysMem::PageAllocationSize(Pointer);// just return the current size
}

void* SystemAllocator::ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize)
{
    static RF_Type::Size PageSizeMask = ~(m_BlockSize - 1);
    void* result = nullptr;
    auto currentSize = RF_SysMem::PageAllocationSize(Pointer);
    if(currentSize < NewSize)
    {
        auto newSize = ((NewSize - 1) & PageSizeMask) + m_BlockSize;
        m_Size.Add(NewSize-currentSize);
        result = RF_SysMem::PageAllocate(newSize);
        RF_SysMem::Copy(result, Pointer, currentSize);
        RF_SysMem::PageFree(Pointer);
    }
    else
    {
        result = Pointer;
    }
    return result;
}

RF_Type::Size SystemAllocator::AllocationSize(void* Pointer)
{
    return RF_SysMem::PageAllocationSize(Pointer);
}

RF_Type::Size SystemAllocator::GetAllocatedBytes() const
{
    return m_Size;
}

RF_Type::Size SystemAllocator::GetUsedBytes() const
{
    return m_Size;
}

RF_Type::Size SystemAllocator::GetAllocationGranularity() const
{
    return m_BlockSize;
}

} }