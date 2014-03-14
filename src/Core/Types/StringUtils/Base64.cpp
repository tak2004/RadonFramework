#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/Base64.hpp>
#include <RadonFramework/backend/stringcoders/modp_b64.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String Base64Converter::Encode(const String &Source)
{
    std::string str=modp::b64_encode(Source.c_str(),Source.Length());
    String result(str.c_str());
    return result;
}

String Base64Converter::Decode(const String &Source)
{
    std::string str=modp::b64_decode(Source.c_str(),Source.Length());
    String result(str.c_str());
    return result;
}