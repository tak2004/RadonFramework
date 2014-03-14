#ifndef RF_SYSTEM_ENDIAN_HPP
#define RF_SYSTEM_ENDIAN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace System
    {
        namespace Endian 
        { 
            enum Type
            { 
                Little=1, 
                Big, 
                Both 
            }; 
        }
    }
}
#endif // RF_SYSTEM_ENDIAN_HPP