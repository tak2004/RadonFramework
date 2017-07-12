#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/Base85.hpp"
#include "RadonFramework/backend/stringcoders/modp_b85.h"

namespace RadonFramework::Text::StringUtils {

RF_Type::String Base85Converter::Encode(const RF_Type::String &Source)
{
    std::string str = modp::b85_encode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String Base85Converter::Decode(const RF_Type::String &Source)
{
    std::string str = modp::b85_decode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

}