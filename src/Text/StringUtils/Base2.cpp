#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/Base2.hpp"
#include "RadonFramework/backend/stringcoders/modp_b2.h"

namespace RadonFramework { namespace Text { namespace StringUtils {

RF_Type::String Base2Converter::Encode(const RF_Type::String &Source)
{
    std::string str(Source.c_str());
    modp::b2_encode(str);
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String Base2Converter::Decode(const RF_Type::String &Source)
{
    std::string str = Source.c_str();
    modp::b2_decode(str);
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

} } }