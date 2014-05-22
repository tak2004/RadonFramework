#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/Base85.hpp>
#include <RadonFramework/backend/stringcoders/modp_b85.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String Base85Converter::Encode(const String &Source)
{
    std::string str=modp::b85_encode(Source.c_str(),Source.Length());
    String result(str.c_str(), str.size());
    return result;
}

String Base85Converter::Decode(const String &Source)
{
    std::string str=modp::b85_decode(Source.c_str(),Source.Length());
    String result(str.c_str(), str.size());
    return result;
}
