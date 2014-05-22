#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/Base16.hpp>
#include <RadonFramework/backend/stringcoders/modp_b16.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String Base16Converter::Encode(const String &Source)
{
    std::string str=modp::b16_encode(Source.c_str(),Source.Length());
    String result(str.c_str(), str.size());
    return result;
}

String Base16Converter::Decode(const String &Source)
{
    std::string str=modp::b16_decode(Source.c_str(),Source.Length());
    String result(str.c_str(), str.size());
    return result;
}
