#ifndef RF_CORE_TYPES_STRINGSET_HPP
#define RF_CORE_TYPES_STRINGSET_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/StringView.hpp>

namespace RadonFramework::Core::Types
{

class StringSet
{
public:
  StringSet()noexcept;
  StringSet(const StringView& Source, const Size Elements)noexcept;
  Bool IsEmpty() const;
  StringView Last() const;
  Size Count() const;
  StringView operator[](const Size Index)const;
  Bool Set(const Size Index, const Size Offset, const Size Count);
private:
  StringView m_Source;
  Size m_ElementCount;
  struct Element
  {
    Size Offset;
    Size Count;
  };
  Element* m_Elements;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif  // RF_CORE_TYPES_STRINGSET_HPP