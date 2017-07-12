#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/Base16.hpp"
#include "RadonFramework/backend/stringcoders/modp_b16.h"

namespace RadonFramework::Text::StringUtils {

RF_Type::String Base16Converter::Encode(const RF_Type::String &Source)
{
    std::string str = modp::b16_encode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String Base16Converter::Decode(const RF_Type::String &Source)
{
    std::string str = modp::b16_decode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

}