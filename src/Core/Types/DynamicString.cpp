#include "RadonFramework/Core/Types/DynamicString.hpp"
#include "RadonFramework/Core/Common/Assert.hpp"

using namespace RadonFramework::Core::Types;

UInt8& DynamicString::operator [](const MemoryRange Index)
{
    RF_ASSERT(Index < m_Size, "Index out of bound.");
    return m_Buffer[Index];
}

UInt8 DynamicString::operator [](const MemoryRange Index)const
{
    RF_ASSERT(Index < m_Size, "Index out of bound.");
    return m_Buffer[Index];
}

const UInt8* DynamicString::Raw()const
{
    return m_Buffer;
}

UInt8* DynamicString::Raw()
{
    return m_Buffer;
}

Size DynamicString::GetSize() const
{
    return m_Size;
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