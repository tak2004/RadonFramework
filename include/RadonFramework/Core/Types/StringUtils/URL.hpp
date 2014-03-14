#ifndef RF_CORE_TYPES_STRINGUTILS_URL_HPP
#define RF_CORE_TYPES_STRINGUTILS_URL_HPP
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
                class URLConverter
                {
                    public:
                        static String Encode(const String &Source);
                        static String Decode(const String &Source);
                        static String EncodeMinimal(const String &Source);
                        static String DecodeMinimal(const String &Source);
                };
            }
        }
    }
}

#endif
