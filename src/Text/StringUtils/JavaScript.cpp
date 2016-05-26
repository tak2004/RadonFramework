#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringUtils/JavaScript.hpp"
#include "RadonFramework/backend/stringcoders/modp_bjavascript.h"

namespace RadonFramework { namespace Text { namespace StringUtils {

RF_Type::String JavaScriptConverter::Encode(const RF_Type::String &Source)
{
    std::string str = modp::javascript_encode(Source.c_str(), Source.Length());
    RF_Type::String result(str.c_str(), str.size());
    return result;
}

} } }