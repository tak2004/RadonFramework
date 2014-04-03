#ifndef RF_CORE_TYPES_UINT64_HPP
#define RF_CORE_TYPES_UINT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Types {

/// A UInt8 have always the size of 8 byte and represent a unsigned number.
#ifdef RF_HAVE_LONG_LONG
    typedef unsigned long long int UInt64;
#else
    typedef struct {
        #ifdef IS_LITTLE_ENDIAN
            unsigned long lo,hi;
        #else
            unsigned long hi,lo;
        #endif
    }UInt64;
#endif

/// The minimum value which can be contained by a UInt64.
extern const UInt64 UInt64Min;

/// The maximum value which can be contained by a UInt64.
extern const UInt64 UInt64Max;

} } }

#endif // RF_CORE_TYPES_UINT64_HPP
