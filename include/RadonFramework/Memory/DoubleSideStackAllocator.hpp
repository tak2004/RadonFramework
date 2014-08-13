#ifndef RF_DOUBLESIDESTACKALLOCATOR_HPP
#define RF_DOUBLESIDESTACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework { namespace Memory {

class DoubleSideStackAllocator
{
public:
    DoubleSideStackAllocator(RF_Type::Size ReservedMemorySize);
    void ClearBoth();

    void* PushPersistent(RF_Type::Size MemorySize);
    void PopPersistent();
    void* PeekPersistent()const;
    RF_Type::Size PeekSizePersistent()const;
    void ClearPersistent();

    void* PushTemporary(RF_Type::Size MemorySize);
    void PopTemporary();
    void* PeekTemporary()const;
    RF_Type::Size PeekSizeTemporary()const;
    void ClearTemporary();

    void FillZeroIfPoped(RF_Type::Bool choice);
    void FillZeroIfFreed(RF_Type::Bool choice);
    RF_Type::Bool FillZeroIfFreed()const;
    RF_Type::Bool FillZeroIfPoped()const;

    RF_Type::Size PersistantStackSize()const;
    RF_Type::Size TemporaryStackSize()const;
    RF_Type::Size CombinedStackSize()const;
    RF_Type::Size ReservedSize()const;
protected:
    Memory::AutoPointerArray<RF_Type::UInt8> m_ReservedMemory;
    RF_Type::Size m_AllocatedMemorySize;
    RF_Type::UInt8* m_PersistentStack;
    RF_Type::UInt8* m_TemporaryStack;
    RF_Type::UInt8* m_CurrentPersistentLocation;
    RF_Type::UInt8* m_CurrentTemporaryLocation;
    RF_Type::Bool m_FillZeroIfFreed;
    RF_Type::Bool m_FillZeroIfPoped;
};

inline RF_Type::Bool DoubleSideStackAllocator::FillZeroIfFreed()const
{
    return m_FillZeroIfFreed;
}

inline RF_Type::Bool DoubleSideStackAllocator::FillZeroIfPoped()const
{
    return m_FillZeroIfPoped;
}

inline void DoubleSideStackAllocator::FillZeroIfPoped(RF_Type::Bool choice)
{
    m_FillZeroIfPoped = choice;
}

inline void DoubleSideStackAllocator::FillZeroIfFreed(RF_Type::Bool choice)
{
    m_FillZeroIfFreed = choice;
}

inline RF_Type::Size DoubleSideStackAllocator::PersistantStackSize()const
{
    return m_CurrentPersistentLocation - m_PersistentStack;
}

inline RF_Type::Size DoubleSideStackAllocator::TemporaryStackSize()const
{
    return m_TemporaryStack - m_CurrentTemporaryLocation;
}

inline RF_Type::Size DoubleSideStackAllocator::CombinedStackSize()const
{
    return m_AllocatedMemorySize;
}

inline RF_Type::Size DoubleSideStackAllocator::ReservedSize() const
{
    return m_ReservedMemory.Size();
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_DOUBLESIDESTACKALLOCATOR_HPP
