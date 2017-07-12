#ifndef RF_MEMORY_HEAPALLOCATOR_HPP
#define RF_MEMORY_HEAPALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework::Memory {

class HeapAllocator
{
public:
    HeapAllocator();
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(const MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
private:
    static RF_Type::Size m_PageSize;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_HEAPALLOCATOR_HPP