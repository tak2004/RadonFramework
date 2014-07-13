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
    Size GetSize()const;
    void SetSize(const UInt8 NewSize);
protected:
    Char m_Buffer[LENGTH];
    UInt8 m_Size;
};

template<int LENGTH>
Char& FixString<LENGTH>::operator [](const MemoryRange Index)
{
    Assert(Index < LENGTH, "Index out of bound.");
    return m_Buffer[Index];
}

template<int LENGTH>
Char FixString<LENGTH>::operator [](const MemoryRange Index)const
{
    Assert(Index < LENGTH, "Index out of bound.");
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

} } }

#endif