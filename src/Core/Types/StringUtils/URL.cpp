#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/URL.hpp>
#include <RadonFramework/backend/stringcoders/modp_burl.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String URLConverter::Encode(const String &Source)
{
    std::string str=modp::url_encode(Source.c_str(),Source.Length());
    String result(str.c_str());
    return result;
}

String URLConverter::Decode(const String &Source)
{
    std::string str=modp::url_decode(Source.c_str(),Source.Length());
    String result(str.c_str());
    return result;
}

String URLConverter::EncodeMinimal(const String &Source)
{
    std::string str=Source.c_str();
    modp::url_min_encode(str);
    String result(str.c_str());
    return result;
}

String URLConverter::DecodeMinimal(const String &Source)
{
    std::string str=Source.c_str();
    modp::url_min_encode(str);
    String result(str.c_str());
    return result;
}
