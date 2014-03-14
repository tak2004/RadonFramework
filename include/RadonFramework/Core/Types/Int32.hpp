#ifndef RF_CORE_TYPES_INT32_HPP
#define RF_CORE_TYPES_INT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            /// A Int32 have always the size of 4 byte and represent a signed number.
            typedef long Int32;

            /// The maximum value which can be contained by a Int32.
            extern const Int32 Int32Max;

            /// The minimum value which can be contained by a Int32.
            extern const Int32 Int32Min;
        }
    }
}

#endif // RF_CORE_TYPES_INT32_HPP
