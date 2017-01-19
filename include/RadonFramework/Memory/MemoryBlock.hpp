#ifndef RF_MEMORY_MEMORYBLOCK_HPP
#define RF_MEMORY_MEMORYBLOCK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Memory {

struct MemoryBlock
{
    RF_Type::UInt8* Data;
    RF_Type::Size Bytes;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_MEMORYBLOCK_HPP
