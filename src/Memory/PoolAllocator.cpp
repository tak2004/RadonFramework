#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/PoolAllocator.hpp"

namespace RadonFramework { namespace Memory {

class PoolAllocator::ObjList
{
public:
    ObjList(){}
    RF_Type::UInt8* m_Start;
    void* m_NextFreeBlock;
    RF_Type::AtomicPointer<ObjList> m_NextList;
    RF_Type::AtomicInt32 m_FreeElements;
    RF_Type::UInt8* m_Last;
};

PoolAllocator::PoolAllocator(const RF_Type::Size Blocksize , const RF_Type::Size Alignment,
    AllocatorBase* Arena /*= nullptr*/)
:m_Arena(Arena)
,m_Chunks(0)
,m_Used(0)
,m_Reserved(0)
,m_Alignment(Alignment)
,m_ChunkCount(0)
{
    // A block should be at least 4/8byte large to hold the counter.
    m_BlockSize = RF_Math::Integer<RF_Type::Size>::Max(Blocksize, sizeof(void*));
    m_BlockOffset = (((m_BlockSize - 1) / m_Alignment) + 1) * m_Alignment;
}

void* PoolAllocator::Allocate(const RF_Type::Size Bytes, const RF_Type::UInt32 Flag /*= 0*/)
{
    void* result = nullptr;

    // get an ObjList
    ObjList* currentList = m_Chunks;
    RF_Type::Int32 freeElements;
    while((currentList != nullptr) && (freeElements = currentList->m_FreeElements.FetchAndExchange(-1)) <= 0)
    {
        currentList = currentList->m_NextList;
    }

    if(currentList != nullptr)
    {// got an entry
        --freeElements;
        m_Used.Add(m_BlockSize);
        result = reinterpret_cast<void*>(currentList->m_NextFreeBlock);
        if(currentList->m_FreeElements != 0)
        {
            currentList->m_NextFreeBlock = *reinterpret_cast<void**>(currentList->m_NextFreeBlock);
        }
        else
        {
            currentList->m_NextFreeBlock = nullptr;
        }
        currentList->m_FreeElements = freeElements;
        // end of lock
    }
    else
    {// Create a new entry.
        // Adjust to the underlying allocator but need at least space for one instance.
        RF_Type::Size chunkSize = RF_Math::Integer<RF_Type::Size>::Max(
            m_Arena->GetAllocationGranularity(), m_BlockSize+sizeof(ObjList)+m_Alignment);
        void* chunk = m_Arena->Allocate(chunkSize);
        chunkSize = m_Arena->AllocationSize(chunk);
        m_Reserved.Add(chunkSize);

        // init ObjList
        ObjList* list = reinterpret_cast<ObjList*>(RF_Mem::AlignPointer(chunk, alignof(ObjList)));
        new (list) ObjList;
        list->m_Start = reinterpret_cast<RF_Type::UInt8*>(RF_Mem::AlignPointer(list+1, m_Alignment));
        list->m_FreeElements = ((reinterpret_cast<RF_Type::MemoryRange>(chunk) + chunkSize) - 
            reinterpret_cast<RF_Type::MemoryRange>(list->m_Start)) / m_BlockOffset;
        list->m_Last = list->m_Start + (list->m_FreeElements - 1) * m_BlockOffset;
        list->m_NextFreeBlock = reinterpret_cast<void*>(list->m_Start);
        for (RF_Type::Size i = 0; i < list->m_FreeElements; ++i)
        {
            *reinterpret_cast<void**>(list->m_Start+(i*m_BlockOffset)) = reinterpret_cast<void*>(list->m_Start + ((i+1)*m_BlockOffset));
        }

        // got an entry
        --list->m_FreeElements;
        result = reinterpret_cast<void*>(list->m_NextFreeBlock);
        list->m_NextFreeBlock = *reinterpret_cast<void**>(list->m_NextFreeBlock);
        m_Used.Add(m_BlockSize);

        do // put it in front of the list
        {
            list->m_NextList = m_Chunks;
        } while(RF_SysThread::Interlocked::InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(&m_Chunks), list, list->m_NextList));
    }
    return result;
}

void PoolAllocator::Free(void* Pointer)
{
    ObjList* targetList = m_Chunks;
    while(targetList != 0 && (Pointer < targetList->m_Start || Pointer > targetList->m_Last))
    {
        targetList = targetList->m_NextList;
    }
    
    if(targetList != nullptr)
    {
        RF_Type::Int32 lastValue;
        while(lastValue = targetList->m_FreeElements.FetchAndExchange(-1) >= 0)
        {            
        }

        void* next = reinterpret_cast<void*>(
            reinterpret_cast<RF_Type::MemoryRange>(Pointer) & (m_Alignment - 1));
        next = *reinterpret_cast<void**>(targetList->m_NextFreeBlock);
        targetList->m_NextFreeBlock = next;
        ++lastValue;
        m_Used.Add(-m_BlockSize);
        targetList->m_FreeElements = lastValue;
    }
}

RF_Type::Size PoolAllocator::AllocationSize(void* Pointer)
{
    return m_BlockSize;
}

RF_Type::Size PoolAllocator::GetAllocatedBytes() const
{
    return m_Reserved;
}

RF_Type::Size PoolAllocator::GetUsedBytes() const
{
    return m_Used;
}

RF_Type::Size PoolAllocator::GetAllocationGranularity() const
{
    return m_BlockSize;
}

RF_Type::Size PoolAllocator::Resize(void* Pointer, const RF_Type::Size NewSize)
{
    return m_BlockSize;
}

void* PoolAllocator::ResizeOrAllocate(void* Pointer, const RF_Type::Size NewSize)
{
    return nullptr;
}

} }