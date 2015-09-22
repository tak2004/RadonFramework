#ifndef RF_SYSTEM_COMPILERCONFIG_HPP
#define RF_SYSTEM_COMPILERCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/MemoryArchitecture.hpp>
#include <RadonFramework/System/Endian.hpp>

namespace RadonFramework { namespace System {

struct CompilerConfig
{
    static const Endian Endianness;
    static const MemoryArchitecture::Type CompiledForArchitecture;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_SYS
#define RF_SHORTHAND_NAMESPACE_SYS
namespace RF_Sys = RadonFramework::System;
#endif

#if defined(RF_VISUALCPP)
// vsc++

// error msg
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "		
#define RF_COMPILER_WARNING(x) __pragma(message(__LOC__ x))

// memory alignment
#define RF_ALIGN(X) __declspec(align(X))
#else
#if defined(RF_MINGW32)
// mingw

// error msg
#define RF_COMPILER_WARNING(x) #warning x
#else
#if defined(RF_GCC)
// gcc

// error msg
// really bad solution but this is allready the best on gcc
#define RF_DO_PRAGMA(x) _Pragma (#x)
#define RF_COMPILER_WARNING(x) RF_DO_PRAGMA(message ("warning: " x))
#else
static_assert(false, "There's no support, of compiler warnings, for your compiler at the moment.\
                                                          Please insert the warning command for your compiler here or remove this info.");
#endif
#endif
#endif

#ifndef RF_ALIGN
#define RF_ALIGN(X) alignas(X)
#endif

// clang: check if __has_feature is available
#ifndef __has_feature
#define __has_feature(x) 0
#endif

// detect if compiler can use constexpr
// gcc: available since 4.0.6
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406
#define RF_HAVE_CONSTEXPR
#endif
#if __has_feature(cxx_constexpr)
#define RF_HAVE_CONSTEXPR
#endif

#ifdef RF_HAVE_CONSTEXPR
#define RF_CONSTEXPR constexpr
#else
#define RF_CONSTEXPR
#endif

// detect if compiler can use is_trivially_copyable
// available since VS2012
#if (defined(RF_VISUALCPP) && !defined(RF_VISUALCPP_OLDER_2012))
#define RF_HAVE_IS_TRIVIALLY_COPYABLE
#endif

#if !defined(RF_VISUALCPP)
#define RF_HAVE_IS_TRIVIALLY_COPYABLE
#endif

// detect if compiler can use noexcept
// gcc and clang
#if __has_feature(cxx_noexcept) ||\
    (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46) ||\
    defined(RF_VISUALCPP)
#define RF_HAVE_NOEXCEPT
#endif

#ifdef RF_HAVE_NOEXCEPT
#ifdef RF_VISUALCPP
#define RF_NOEXCEPT _NOEXCEPT
#else
#define RF_NOEXCEPT noexcept
#endif
#else
#define RF_NOEXCEPT
#endif

#endif // RF_SYSTEM_COMPILERCONFIG_HPP