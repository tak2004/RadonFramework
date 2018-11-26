#ifndef RF_CORE_TYPES_FIXSTRING_HPP
#define RF_CORE_TYPES_FIXSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/MemoryRange.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework::Core::Types{

template<int LENGTH>
struct FixString
{
    UInt8& operator[](const MemoryRange Index);
    UInt8 operator[](const MemoryRange Index)const;
    const UInt8* Raw()const;
    UInt8* Raw();
    Size GetSize()const;
    void SetSize(const UInt8 NewSize);
protected:
    UInt8 m_Buffer[LENGTH];
    UInt8 m_Size;
};

template<int LENGTH>
UInt8& FixString<LENGTH>::operator [](const MemoryRange Index)
{
    Assert(Index < LENGTH, "Index out of bound.");
    return m_Buffer[Index];
}

template<int LENGTH>
UInt8 FixString<LENGTH>::operator [](const MemoryRange Index)const
{
    Assert(Index < LENGTH, "Index out of bound.");
    return m_Buffer[Index];
}

template<int LENGTH>
const UInt8* FixString<LENGTH>::Raw()const
{
    return m_Buffer;
}

template<int LENGTH>
UInt8* FixString<LENGTH>::Raw()
{
    return m_Buffer;
}

template<int LENGTH>
Size FixString<LENGTH>::GetSize()const
{
    return m_Size;
}

template<int LENGTH>
void FixString<LENGTH>::SetSize(const UInt8 NewSize)
{
    Assert(NewSize <= LENGTH, "Out of bound");
    m_Size = NewSize;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif