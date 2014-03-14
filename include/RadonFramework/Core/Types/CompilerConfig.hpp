#ifndef RF_CORE_TYPES_COMPILERCONFIG_HPP
#define RF_CORE_TYPES_COMPILERCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

// detect 64bit integer support
#if defined(_MSC_VER) || defined(__SIZEOF_LONG_LONG__) // VS, gcc
    #define RF_HAVE_LONG_LONG    
#endif                           

#endif // RF_CORE_TYPES_COMPILERCONFIG_HPP