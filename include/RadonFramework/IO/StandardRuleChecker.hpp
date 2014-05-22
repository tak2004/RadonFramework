#ifndef RF_IO_STANDARDRULECHECKER_HPP
#define RF_IO_STANDARDRULECHECKER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

struct StandardRuleChecker
{
    static RFTYPE::Bool Text(const RFTYPE::String& Value)
    {
        return Value != "";
    }

    static RFTYPE::Bool Numeric(const RFTYPE::String& Value)
    {
        return Value.IsNumber();
    }

    static RFTYPE::Bool Boolean(const RFTYPE::String& Value)
    {
        return Value.IsBoolean();
    }
};

} }

#endif // RF_IO_STANDARDRULECHECKER_HPP