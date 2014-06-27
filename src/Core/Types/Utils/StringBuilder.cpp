#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/Utils/StringBuilder.hpp"

using namespace RadonFramework::Core::Types::Utils;

StringBuilder::StringBuilder()
:m_Data(0)
{
}

StringBuilder::~StringBuilder()
{
}

StringBuilder& StringBuilder::AppendFormat(const RFTYPE::String& Format, ...)
{
    return *this;
}

StringBuilder& StringBuilder::AppendLine()
{
    return *this;
}

StringBuilder& StringBuilder::Append(const RFTYPE::String& Value)
{
    return *this;
}

void StringBuilder::Clear()
{
}

void StringBuilder::EnsureCapacity(const RFTYPE::Size NewCapacity)
{
}

StringBuilder& StringBuilder::Insert(const RFTYPE::String& Value, const RFTYPE::Size Index)
{
    return *this;
}

StringBuilder& StringBuilder::Remove(const RFTYPE::Size Index, const RFTYPE::Size GlyphCount)
{
    return *this;
}

StringBuilder& StringBuilder::Replace(const RFTYPE::String& ThisString, 
        const RFTYPE::String& ByString)
{
    return *this;
}

RFTYPE::Size StringBuilder::Length()const
{
    return m_Length;
}

RFTYPE::Size StringBuilder::Size()const
{
    return m_Size;
}

RFTYPE::Size StringBuilder::Capacity()const
{
    RFTYPE::Size result=0;
    return result;
}

RadonFramework::Memory::AutoPointer<RFTYPE::String> StringBuilder::ToString()const
{
    RadonFramework::Memory::AutoPointer<RFTYPE::String> result(new RFTYPE::String(
        m_Data, m_Size, RadonFramework::Core::Common::DataManagment::UnmanagedInstance));
    return result;
}

RFTYPE::Char* StringBuilder::AsCString() const
{
    return m_Data;
}
