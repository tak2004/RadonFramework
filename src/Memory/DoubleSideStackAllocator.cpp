#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/DoubleSideStackAllocator.hpp"

/**
* Memory layout: [reserved memory chunk|n-bytes][size of chunk|sizeof(void*)-bytes]
* The pointer to the reserved memory pool + size of user reserved memory
* point to the up comming memory block and -sizeof(void*) point to the size
* of the last chunk.
*/

using namespace RadonFramework::Core::Types;

namespace RadonFramework { namespace Memory {

DoubleSideStackAllocator::DoubleSideStackAllocator(Size ReservedMemorySize)
:m_AllocatedMemorySize(0)
,m_PersistentStack(0)
,m_TemporaryStack(0)
,m_CurrentPersistentLocation(0)
,m_CurrentTemporaryLocation(0)
,m_FillZeroIfFreed(false)
,m_FillZeroIfPoped(false)
{
    m_ReservedMemory = AutoPointerArray<UInt8>(new UInt8[ReservedMemorySize], ReservedMemorySize);
    m_PersistentStack = m_ReservedMemory.Get();
    m_TemporaryStack = m_ReservedMemory.Get() + ReservedMemorySize;
    m_CurrentPersistentLocation = m_PersistentStack;
    m_CurrentTemporaryLocation = m_CurrentTemporaryLocation;
}

void DoubleSideStackAllocator::ClearBoth()
{
    if (m_FillZeroIfFreed)
        RF_SysMem::Set(m_ReservedMemory.Get(), 0, m_ReservedMemory.Size());
    m_AllocatedMemorySize = 0;
    m_CurrentPersistentLocation = m_PersistentStack;
    m_CurrentTemporaryLocation = m_TemporaryStack;
}

void* DoubleSideStackAllocator::PushPersistent(Size MemorySize)
{
    void* result = 0;
    Size blockSize = MemorySize + sizeof(Size);
    Size neccessarySpace = m_AllocatedMemorySize + blockSize;
    if (neccessarySpace < m_ReservedMemory.Size())
    {
        result = m_CurrentPersistentLocation;
        Size* ptr = reinterpret_cast<Size*>(m_CurrentPersistentLocation + MemorySize);
        *ptr = MemorySize;
        m_CurrentPersistentLocation += blockSize;
        m_AllocatedMemorySize += blockSize;
    }
    return result;
}

void DoubleSideStackAllocator::PopPersistent()
{
    Size blockSize = PeekSizePersistent() + sizeof(Size);
    if (m_FillZeroIfPoped)
        RF_SysMem::Set(m_CurrentPersistentLocation - blockSize, 0, blockSize);
    m_CurrentPersistentLocation -= blockSize;
    m_AllocatedMemorySize -= blockSize;
}

void* DoubleSideStackAllocator::PushTemporary(Size MemorySize)
{
    void* result = 0;
    Size blockSize = MemorySize + sizeof(Size);
    Size neccessarySpace = m_AllocatedMemorySize + blockSize;
    if (neccessarySpace < m_ReservedMemory.Size())
    {
        result = m_CurrentTemporaryLocation - PeekSizeTemporary() - sizeof(Size);
        Size* ptr = reinterpret_cast<Size*>(m_CurrentTemporaryLocation + sizeof(Size));
        *ptr = MemorySize;
        m_AllocatedMemorySize += blockSize;
        m_CurrentTemporaryLocation -= blockSize;
    }
    return result;
}

void DoubleSideStackAllocator::PopTemporary()
{
    Size blockSize = PeekSizeTemporary() + sizeof(Size);
    if (m_FillZeroIfPoped)
        RF_SysMem::Set(m_CurrentTemporaryLocation - blockSize, 0, blockSize);
    m_CurrentTemporaryLocation += blockSize;
    m_AllocatedMemorySize -= blockSize;
}

void* DoubleSideStackAllocator::PeekPersistent()const
{
    void* result = 0;
    if (m_CurrentPersistentLocation > m_PersistentStack)
    {
        Size blockSize = PeekSizePersistent() + sizeof(Size);
        result = reinterpret_cast<void*>(m_CurrentPersistentLocation - blockSize);
    }
    return result;
}

void* DoubleSideStackAllocator::PeekTemporary()const
{
    void* result = 0;
    if (m_TemporaryStack > m_CurrentTemporaryLocation)
    {
        Size blockSize = PeekSizeTemporary() + sizeof(Size);
        result = reinterpret_cast<void*>(m_CurrentTemporaryLocation - blockSize);
    }
    return result;
}

RF_Type::Size DoubleSideStackAllocator::PeekSizePersistent() const
{
    RF_Type::Size result = 0;
    if (m_PersistentStack < m_CurrentPersistentLocation)
    {
        result = *reinterpret_cast<Size*>(m_CurrentPersistentLocation - sizeof(Size));
    }
    return result;
}

RF_Type::Size DoubleSideStackAllocator::PeekSizeTemporary() const
{
    RF_Type::Size result = 0;
    if (m_TemporaryStack > m_CurrentTemporaryLocation)
    {
        result = *reinterpret_cast<Size*>(m_CurrentTemporaryLocation - sizeof(Size));
    }
    return result;
}

void DoubleSideStackAllocator::ClearPersistent()
{
    Size blockSize = PersistantStackSize() + sizeof(Size);
    if (m_FillZeroIfFreed)
        RF_SysMem::Set(m_PersistentStack, 0, blockSize);
    m_CurrentPersistentLocation = m_PersistentStack;
    m_AllocatedMemorySize -= blockSize;
}

void DoubleSideStackAllocator::ClearTemporary()
{
    Size blockSize = TemporaryStackSize() + sizeof(Size);
    if (m_FillZeroIfFreed)
        RF_SysMem::Set(m_TemporaryStack - blockSize, 0, blockSize);
    m_CurrentTemporaryLocation = m_TemporaryStack;
    m_AllocatedMemorySize -= blockSize;
}

} }