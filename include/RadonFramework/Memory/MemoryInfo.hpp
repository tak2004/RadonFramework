#ifndef RF_MEMORYINFO_HPP
#define RF_MEMORYINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework { namespace Memory {

class MemoryInfo
{
public:
    // Return the size of installed memory in megabytes.
    static RF_Type::UInt32 InstalledMemory();
protected:
    static void* m_Backend;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORYINFO_HPP
