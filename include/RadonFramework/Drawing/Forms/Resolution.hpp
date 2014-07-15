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
            RF_Type::UInt32 Width;
            RF_Type::UInt32 Height;
            RF_Type::UInt32 BitsPerPixel;
            RF_Type::UInt32 Frequency;
        };
    }
}

#endif // RF_RESOLUTION_HPP