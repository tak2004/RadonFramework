#ifndef RF_COMPILER_HPP
#define RF_COMPILER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#if defined(RF_VISUALCPP)
    // vsc++

    // error msg
    #define __STR2__(x) #x
    #define __STR1__(x) __STR2__(x)
    #define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "		
    #define RF_COMPILER_WARNING(x) __pragma(message(__LOC__ x))

    // memory alignment
    #define ALIGN(X) __declspec(align(X))
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
            #define DO_PRAGMA(x) _Pragma (#x)
            #define RF_COMPILER_WARNING(x) DO_PRAGMA(message ("warning: " x))
        #else
            static_assert(false,"There's no support, of compiler warnings, for your compiler at the moment.\
                Please insert the warning command for your compiler here or remove this info.");                
        #endif
    #endif

    // memory alignment
    #define ALIGN(X) __attribute__ ((aligned (X)))
#endif

// detect if compiler can use constexpr
// gcc: available since 4.0.6
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406
    #define RF_HAVE_CONSTEXPR
#endif
// clang: check if __has_feature is available
#ifndef __has_feature
    #define __has_feature(x) 0
#endif
#if __has_feature(cxx_constexpr)
    #define RF_HAVE_CONSTEXPR
#endif

#ifdef RF_HAVE_CONSTEXPR
    #define RF_CONSTEXPR constexpr
#else
    #define RF_CONSTEXPR
#endif

#endif // RF_COMPILER_HPP
