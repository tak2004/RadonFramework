#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/Base64.hpp"
#include "RadonFramework/backend/stringcoders/modp_b64.h"

namespace RadonFramework::Text::StringUtils {

RF_Type::String Base64Converter::Encode(const RF_Type::String &Source)
{
    std::string str = modp::b64_encode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String Base64Converter::Decode(const RF_Type::String &Source)
{
    std::string str = modp::b64_decode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

}