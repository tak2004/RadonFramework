#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/OptionValue.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;

OptionValue::OptionValue()
:m_ValueSet(false)
{
}

OptionValue::OptionValue(const OptionValue& Copy)
{
    *this=Copy;
}

OptionValue::OptionValue(const String& Value)
{
    m_ValueSet=true;
    m_Value=Value;
}

Bool OptionValue::IsSet()const
{
    return m_ValueSet;
}

OptionValue& OptionValue::operator=(const OptionValue& Other)
{
    m_ValueSet=Other.m_ValueSet;
    m_Value=Other.m_Value;
    return *this;
}

OptionValue& OptionValue::operator=(const String& Value)
{
    m_ValueSet=true;
    m_Value=Value;
    return *this;
}

const String& OptionValue::Value()const
{
    return m_Value;
}

void OptionValue::Set()
{
	m_ValueSet=true;
}
