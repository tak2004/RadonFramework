#ifndef RF_TEXT_STRINGUTILS_BASE85_HPP
#define RF_TEXT_STRINGUTILS_BASE85_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Text { namespace StringUtils {

class Base85Converter
{
public:
    static RF_Type::String Encode(const RF_Type::String &Source);
    static RF_Type::String Decode(const RF_Type::String &Source);
};

} } }

#endif // RF_TEXT_STRINGUTILS_BASE85_HPP
