#ifndef RF_CORE_TYPES_STRINGUTILS_URLCONVERTER_HPP
#define RF_CORE_TYPES_STRINGUTILS_URLCONVERTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Core { namespace Types { namespace StringUtils {

class URLConverter
{
public:
    static RF_Type::String Encode(const RF_Type::String &Source);
    static RF_Type::String Decode(const RF_Type::String &Source);
    static RF_Type::String EncodeMinimal(const RF_Type::String &Source);
    static RF_Type::String DecodeMinimal(const RF_Type::String &Source);
};

} } } }

#endif // RF_CORE_TYPES_STRINGUTILS_URLCONVERTER_HPP
