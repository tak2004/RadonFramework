#ifndef RF_TEXT_STRINGUTILS_BASE64_HPP
#define RF_TEXT_STRINGUTILS_BASE64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Text::StringUtils {

class Base64Converter
{
public:
    static RF_Type::String Encode(const RF_Type::String &Source);
    static RF_Type::String Decode(const RF_Type::String &Source);
};

}

#endif // RF_CORE_TYPES_STRINGUTILS_BASE64_HPP
