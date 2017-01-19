#ifndef RF_META_IF_HPP
#define RF_META_IF_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Meta { 

template<bool V, typename A, typename B>
struct If;

template<typename A, typename B>
struct If<true, A,B>{ typedef A Value; };

template<class A, class B>
struct If<false, A,B>{ typedef B Value; };

} } }

#ifndef RF_SHORTHAND_NAMESPACE_META
#define RF_SHORTHAND_NAMESPACE_META
namespace RF_Meta = RadonFramework::Core::Meta;
#endif

#endif // RF_META_IF_HPP