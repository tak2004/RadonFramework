#ifndef RF_IO_STANDARDRULECHECKER_HPP
#define RF_IO_STANDARDRULECHECKER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

struct StandardRuleChecker
{
    static RF_Type::Bool Text(const RF_Type::String& Value)
    {
        return Value != "";
    }

    static RF_Type::Bool Numeric(const RF_Type::String& Value)
    {
        return Value.IsNumber();
    }

    static RF_Type::Bool Boolean(const RF_Type::String& Value)
    {
        return Value.IsBoolean();
    }
};

} }

#endif // RF_IO_STANDARDRULECHECKER_HPP