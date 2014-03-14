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
            Core::Types::UInt32 Width;
            Core::Types::UInt32 Height;
            Core::Types::UInt32 BitsPerPixel;
            Core::Types::UInt32 Frequency;
        };
    }
}

#endif // RF_RESOLUTION_HPP