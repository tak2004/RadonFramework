#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Memory/MemoryInfo.hpp>

void* RadonFramework::Memory::MemoryInfo::m_Backend=0;

RadonFramework::Core::Types::UInt32 RadonFramework::Memory::MemoryInfo::InstalledMemory()
{
//    if (!m_Backend)
//        m_Backend=(void*)new geekinfo::Memory();
//    return ((geekinfo::Memory*)m_Backend)->get_memory_size();
    return 0;
}
