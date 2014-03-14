#ifndef RF_CORE_TYPES_VEC128UINT_HPP
#define RF_CORE_TYPES_VEC128UINT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            /// A Vec128UInt8 have always the size of 16 byte and represent 16 unsigned numbers.
            typedef Vec<UInt8,16> Vec128UInt8;

            /// The minimum value which can be contained by a Vec128UInt8.
            extern const UInt8 Vec128UInt8Min;

            /// The maximum value which can be contained by a Vec128UInt8.
            extern const UInt8 Vec128UInt8Max;

            /// A Vec128UInt16 have always the size of 16 byte and represent 8 unsigned numbers.
            typedef Vec<UInt16,8> Vec128UInt16;

            /// The minimum value which can be contained by a Vec128UInt16.
            extern const UInt16 Vec128UInt16Min;

            /// The maximum value which can be contained by a Vec128UInt16.
            extern const UInt16 Vec128UInt16Max;

            /// A Vec128UInt32 have always the size of 16 byte and represent 4 unsigned numbers.
            typedef Vec<UInt32,4> Vec128UInt32;

            /// The minimum value which can be contained by a Vec128UInt32.
            extern const UInt32 Vec128UInt32Min;

            /// The maximum value which can be contained by a Vec128UInt32.
            extern const UInt32 Vec128UInt32Max;
        }
    }
}

#endif // RF_CORE_TYPES_VEC128UINT_HPP