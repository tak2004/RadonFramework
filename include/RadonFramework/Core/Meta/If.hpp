#ifndef RF_META_IF_HPP
#define RF_META_IF_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Meta
{
template <bool V, typename A, typename B>
struct If;

template <typename A, typename B>
struct If<true, A, B>
{
  using Value = A;
};

template <class A, class B>
struct If<false, A, B>
{
  using Value = B;
};

}  // namespace RadonFramework::Core::Meta

#ifndef RF_SHORTHAND_NAMESPACE_META
#define RF_SHORTHAND_NAMESPACE_META
namespace RF_Meta = RadonFramework::Core::Meta;
#endif

#endif  // RF_META_IF_HPP