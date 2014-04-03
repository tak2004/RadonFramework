#ifndef RF_RESOLUTION_HPP
#define RF_RESOLUTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        struct Resolution
        {
            RFTYPE::UInt32 Width;
            RFTYPE::UInt32 Height;
            RFTYPE::UInt32 BitsPerPixel;
            RFTYPE::UInt32 Frequency;
        };
    }
}

#endif // RF_RESOLUTION_HPP