#include "RadonFramework/Core/Types/StringView.hpp"

namespace RadonFramework::Core::Types
{
StringView::StringView() noexcept : m_Source(nullptr), m_Length(0) {}

StringView::StringView(const StringView& Copy) noexcept
: m_Source(Copy.m_Source), m_Length(Copy.m_Length)
{
}

StringView::StringView(const char* Data, size_t Length)
: m_Source(reinterpret_cast<const UInt8*>(Data)), m_Length(Length)
{
}

StringView StringView::SubString(const Size Offset, const Size Length) const
{
  return StringView(reinterpret_cast<const char*>(m_Source + Offset), Length);
}

const UInt8& StringView::operator[](const Size Index)const
{
  return m_Source[Index];
}

Size StringView::Length() const
{
  return m_Length;
}

const UInt8* StringView::Data() const
{
  return m_Source;
}

Bool StringView::StartsWith(const UInt8 Value)
{
  return m_Source[0] == Value;
}

}  // namespace RadonFramework::Core::Types