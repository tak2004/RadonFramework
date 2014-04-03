#ifndef RF_CORE_TYPES_STRINGUTILS_BASE85_HPP
#define RF_CORE_TYPES_STRINGUTILS_BASE85_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            namespace StringUtils
            {
                class Base85Converter
                {
                    public:
                        static String Encode(const String &Source);
                        static String Decode(const String &Source);
                };
            }
        }
    }
}

#endif // RF_CORE_TYPES_STRINGUTILS_BASE85_HPP