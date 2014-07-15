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

    OptionValue(const RF_Type::String& Value);
                                
    OptionValue& operator=(const OptionValue& Other);

    OptionValue& operator=(const RF_Type::String& Value);

    void Set();

    RF_Type::Bool IsSet()const;

    const RF_Type::String& Value()const;
protected:
    RF_Type::String m_Value;
    RF_Type::Bool m_ValueSet;
};

} }

#endif