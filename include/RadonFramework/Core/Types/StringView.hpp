#ifndef RF_CORE_TYPES_STRINGVIEW_HPP
#define RF_CORE_TYPES_STRINGVIEW_HPP
#if _MSC_VER > 1000
#pragma once
#endif

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

private:
  const UInt8* m_Source;
  Size m_Length;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif  // RF_CORE_TYPES_STRINGVIEW_HPP