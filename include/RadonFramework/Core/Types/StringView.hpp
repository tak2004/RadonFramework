#ifndef RF_CORE_TYPES_STRINGVIEW_HPP
#define RF_CORE_TYPES_STRINGVIEW_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework::Core::Types
{

class StringView
{
public:
  StringView()noexcept;
  StringView(const StringView& Copy) noexcept;
  StringView(const char* Data, size_t Length);
  StringView SubString(const Size Offset, const Size Length) const;
  const UInt8& operator[](const Size Index)const;
  Size Length()const;
  const UInt8* Data()const;
  Bool StartsWith(const UInt8 Value);
  template <int N>
  Bool operator==(char const (&CString)[N]);

private:
  const UInt8* m_Source;
  Size m_Length;
};

template <int N>
Bool StringView::operator==(char const (&CString)[N])
{
  if (m_Length >= N)
  {
    return RF_SysMem::Compare(m_Source, CString, N) == 0;
  }
  return false;
}

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif  // RF_CORE_TYPES_STRINGVIEW_HPP