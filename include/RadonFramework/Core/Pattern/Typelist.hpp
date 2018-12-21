#ifndef RF_CORE_PATTERN_TYPELIST_HPP
#define RF_CORE_PATTERN_TYPELIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

namespace RadonFramework::Core::Pattern
{
struct EmptyType
{
};

template <class HEAD, class TAIL>
struct TypeList
{
  using Head = HEAD;
  using Tail = TAIL;
};

template <class T1 = EmptyType,
          class T2 = EmptyType,
          class T3 = EmptyType,
          class T4 = EmptyType,
          class T5 = EmptyType,
          class T6 = EmptyType,
          class T7 = EmptyType,
          class T8 = EmptyType,
          class T9 = EmptyType>
struct MakeTypeList
{
private:
  using Tail = typename MakeTypeList<T2, T3, T4, T5, T6, T7, T8, T9>::Result;

public:
  using Result = TypeList<T1, Tail>;
};

template <>
struct MakeTypeList<>
{
  using Result = EmptyType;
};

}  // namespace RadonFramework::Core::Pattern

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif  // RF_CORE_PATTERN_TYPELIST_HPP