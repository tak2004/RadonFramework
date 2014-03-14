#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/StringUtils/JavaScript.hpp>
#include <RadonFramework/backend/stringcoders/modp_bjavascript.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Types::StringUtils;

String JavaScriptConverter::Encode(const String &Source)
{
    std::string str=modp::javascript_encode(Source.c_str(),Source.Length());
    String result(str.c_str());
    return result;
}
