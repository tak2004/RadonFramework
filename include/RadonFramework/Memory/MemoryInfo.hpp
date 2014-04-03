#ifndef RF_MEMORYINFO_HPP
#define RF_MEMORYINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Memory
    {
        class MemoryInfo
        {
            public:
                // Return the size of installed memory in megabytes.
                static RFTYPE::UInt32 InstalledMemory();
            protected:
                static void* m_Backend;
        };
    }
}

#endif // RF_MEMORYINFO_HPP
