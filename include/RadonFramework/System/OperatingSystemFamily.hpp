#ifndef RF_OPERATINGSYSTEMFAMILY_HPP
#define RF_OPERATINGSYSTEMFAMILY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace System
    {
        namespace OperatingSystemFamily
        {
            enum Type
            {
                Unkown,
                Windows,
                Linux,
                MacOS
            };
        }
    }
}

#endif // RF_OPERATINGSYSTEMFAMILY_HPP