#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/DynamicString.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"

using namespace RadonFramework::Core::Types;

Char& DynamicString::operator [](const MemoryRange Index)
{
    Assert(Index < m_Size, "Index out of bound.");
    return m_Buffer[Index];
}

Char DynamicString::operator [](const MemoryRange Index)const
{
    Assert(Index < m_Size, "Index out of bound.");
    return m_Buffer[Index];
}

const Char* DynamicString::Raw()const
{
    return m_Buffer;
}

Char* DynamicString::Raw()
{
    return m_Buffer;
}

void DynamicString::Free()
{
    if (m_Buffer)
    {
        delete[] m_Buffer;
        m_Buffer = 0;
        m_Size = 0;
    }
}