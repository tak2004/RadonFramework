#ifndef RF_CORE_TYPES_FIXSTRING_HPP
#define RF_CORE_TYPES_FIXSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types{

template<int LENGTH>
struct FixString
{
    Char& operator[](const MemoryRange Index);
    Char operator[](const MemoryRange Index)const;
    const Char* Raw()const;
    Char* Raw();
protected:
    Char m_Buffer[LENGTH];
};

template<int LENGTH>
Char& FixString<LENGTH>::operator [](const MemoryRange Index)
{
    ASSERT(Index >= LENGTH, "Index out of bound.");
    return m_Buffer[Index];
}

template<int LENGTH>
Char FixString<LENGTH>::operator [](const MemoryRange Index)const
{
    ASSERT(Index >= LENGTH, "Index out of bound.");
    return m_Buffer[Index];
}

template<int LENGTH>
const Char* FixString<LENGTH>::Raw()const
{
    return m_Buffer;
}

template<int LENGTH>
Char* FixString<LENGTH>::Raw()
{
    return m_Buffer;
}

} } }

#endif