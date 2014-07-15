#ifndef RF_CORE_TYPES_STRINGUTILS_JAVASCRIPT_HPP
#define RF_CORE_TYPES_STRINGUTILS_JAVASCRIPT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Core { namespace Types { namespace StringUtils {

class JavaScriptConverter
{
public:
    static RF_Type::String Encode(const RF_Type::String &Source);
};

} } } }

#endif // RF_CORE_TYPES_STRINGUTILS_JAVASCRIPT_HPP
