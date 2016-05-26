#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/URL.hpp"
#include "RadonFramework/backend/stringcoders/modp_burl.h"

namespace RadonFramework { namespace Text { namespace StringUtils {

RF_Type::String URL::Encode(const RF_Type::String &Source)
{
    std::string str = modp::url_encode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String URL::Decode(const RF_Type::String &Source)
{
    std::string str = modp::url_decode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String URL::EncodeMinimal(const RF_Type::String &Source)
{
    std::string str = Source.c_str();
    modp::url_min_encode(str);
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

RF_Type::String URL::DecodeMinimal(const RF_Type::String &Source)
{
    std::string str = Source.c_str();
    modp::url_min_encode(str);
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

} } }