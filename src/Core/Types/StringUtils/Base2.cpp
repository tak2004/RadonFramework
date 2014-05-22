#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/Base2.hpp>
#include <RadonFramework/backend/stringcoders/modp_b2.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String Base2Converter::Encode(const String &Source)
{
    std::string str(Source.c_str());
    modp::b2_encode(str);
    String result(str.c_str(), str.size());
    return result;
}

String Base2Converter::Decode(const String &Source)
{
    std::string str=Source.c_str();
    modp::b2_decode(str);
    String result(str.c_str(), str.size());
    return result;
}

