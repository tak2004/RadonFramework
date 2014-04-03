#ifndef RF_CORE_COMMON_STRING_CACHE_HPP
#define RF_CORE_COMMON_STRING_CACHE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Common
        {
            namespace StringCache
            {
                void Exchange(const char*** newValues);
                const char* Find(const RFTYPE::String& Value);
            }
        }
    }
}

#endif // RF_CORE_COMMON_STRING_CACHE_HPP