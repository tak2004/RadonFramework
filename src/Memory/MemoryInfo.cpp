#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Memory/MemoryInfo.hpp>

void* RF_Mem::MemoryInfo::m_Backend=0;

RadonFramework::Core::Types::UInt32 RF_Mem::MemoryInfo::InstalledMemory()
{
//    if (!m_Backend)
//        m_Backend=(void*)new geekinfo::Memory();
//    return ((geekinfo::Memory*)m_Backend)->get_memory_size();
    return 0;
}
