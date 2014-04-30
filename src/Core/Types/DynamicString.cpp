#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/DynamicString.hpp"

using namespace RadonFramework::Core::Types;

Char FixString::operator [](const MemoryRange Index)
{
    ASSERT(Index >= m_Buffer.Size(), "Index out of bound.");
    return m_Buffer[Index];
}

const Char FixString::operator [](const MemoryRange Index)const
{
    ASSERT(Index >= m_Buffer.Size(), "Index out of bound.");
    return m_Buffer[Index];
}