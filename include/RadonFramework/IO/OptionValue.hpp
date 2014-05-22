#ifndef RF_IO_OPTIONVALUE_HPP
#define RF_IO_OPTIONVALUE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

class OptionValue
{
public:
    OptionValue();

    OptionValue(const OptionValue& Copy);

    OptionValue(const RFTYPE::String& Value);
                                
    OptionValue& operator=(const OptionValue& Other);

    OptionValue& operator=(const RFTYPE::String& Value);

    void Set();

    RFTYPE::Bool IsSet()const;

    const RFTYPE::String& Value()const;
protected:
    RFTYPE::String m_Value;
    RFTYPE::Bool m_ValueSet;
};

} }

#endif