#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringBuilder.hpp"

namespace RadonFramework::Text {

StringBuilder::StringBuilder()
:m_Data(0)
{
}

StringBuilder::~StringBuilder()
{
}

StringBuilder& StringBuilder::AppendFormat(const RF_Type::String& Format, ...)
{
    return *this;
}

StringBuilder& StringBuilder::AppendLine()
{
    return *this;
}

StringBuilder& StringBuilder::Append(const RF_Type::String& Value)
{
    return *this;
}

void StringBuilder::Clear()
{
}

void StringBuilder::EnsureCapacity(const RF_Type::Size NewCapacity)
{
}

StringBuilder& StringBuilder::Insert(const RF_Type::String& Value, const RF_Type::Size Index)
{
    return *this;
}

StringBuilder& StringBuilder::Remove(const RF_Type::Size Index, const RF_Type::Size GlyphCount)
{
    return *this;
}

StringBuilder& StringBuilder::Replace(const RF_Type::String& ThisString,
    const RF_Type::String& ByString)
{
    return *this;
}

RF_Type::Size StringBuilder::Length()const
{
    return m_Length;
}

RF_Type::Size StringBuilder::Size()const
{
    return m_Size;
}

RF_Type::Size StringBuilder::Capacity()const
{
    RF_Type::Size result = 0;
    return result;
}

RF_Mem::AutoPointer<RF_Type::String> StringBuilder::ToString()const
{
    RF_Mem::AutoPointer<RF_Type::String> result(new RF_Type::String(
        m_Data, m_Size, RF_Core::DataManagment::UnmanagedInstance));
    return result;
}

RF_Type::Char* StringBuilder::AsCString() const
{
    return m_Data;
}

}