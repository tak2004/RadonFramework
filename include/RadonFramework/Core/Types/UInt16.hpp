#ifndef RF_CORE_TYPES_UINT16_HPP
#define RF_CORE_TYPES_UINT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            /// A UInt16 have always the size of 2 byte and represent a unsigned number.
            typedef unsigned short int UInt16;

            /// The minimum value which can be contained by a UInt16.
            extern const UInt16 UInt16Min;

            /// The maximum value which can be contained by a UInt16.
            extern const UInt16 UInt16Max;
        }
    }
}

#endif // RF_CORE_TYPES_UINT16_HPP
