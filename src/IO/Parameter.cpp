#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Parameter.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Compiler.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

AutoPointerArray<OptionValue> m_Values;

Bool Parameter::Parse(const AutoPointerArray<String>& Parameters,
                      const AutoPointerArray<OptionRule>& Rules,
                      String& ErrorMessage)
{
    // reserve memory for values
    AutoPointerArray<OptionValue> results(new OptionValue[Rules.Count()],Rules.Count());
    
    Bool matchingValue,matchingParameter;
    UInt32 parameterIndex=0,parameterOffset=0;
    String para;
    String value;
    // process all rules
    for (UInt32 i=0;i<Rules.Count();++i)
    {
        // if long and short name are null then only the value check is neccessary
        matchingValue=true;

        // if there is only a value then the offset is 0 else 1
        if ((Rules[i].LongName!=0 || Rules[i].ShortName!=0) && Rules[i].ValueCheck!=0)
            parameterOffset=1;
        else
            parameterOffset=0;

        if (Parameters.Count()>parameterIndex)
        {
            // If both parameter are null or one of them is unequal null and match the
            // specified name then matchingParameter is true else false.
            if (Rules[i].LongName!=0)
            {
                matchingParameter=Parameters[parameterIndex]==Rules[i].LongName;
                if (Rules[i].ShortName!=0)
                    matchingParameter|=Parameters[parameterIndex]==Rules[i].ShortName;
            }
            else
            {
                if (Rules[i].ShortName!=0)
                    matchingParameter=Parameters[parameterIndex]==Rules[i].ShortName;
                else
                    matchingParameter=true;
            }

            // validate value if possible
            if (Rules[i].ValueCheck!=0)
                matchingValue=Rules[i].ValueCheck(Parameters[parameterIndex+parameterOffset]);
        }
        else
        {
            matchingParameter=false;
            matchingValue=false;
        }

        // something was going wrong
        if (!(matchingParameter && matchingValue))
        {
            switch (Rules[i].Availability)
            {
                case OptionRule::Required:// going crazy
                    ErrorMessage=String::Format("Can't parse '%s', exspected '%s' or '%s'.",
                        Parameters[parameterIndex].c_str(),
                        Rules[i].LongName,
                        Rules[i].ShortName);
                    return false;
                case OptionRule::Optional:// don't care check the next one
                    continue;
            }
        }

        if (Rules[i].ValueCheck!=0)
            results[i]=Parameters[parameterIndex+parameterOffset];// parameter with value
        else
            results[i].Set();// flag

        parameterIndex+=(1+parameterOffset);
    }

    if (parameterIndex!=Parameters.Count())
    {
        ErrorMessage="Unexspected parameter count.";
        return false;
    }    

    m_Values.Swap(results);
    return true;
}

Bool Parameter::Parse(const AutoPointerArray<String>& Parameters,
                      const AutoPointerArray<OptionRule>& Rules)
{
    String errMsg;
    if (!Parse(Parameters,Rules,errMsg))
    {
        LogFatalError("%s", errMsg.c_str());
        return false;
    }
    return true;
}

const AutoPointerArray<OptionValue>& Parameter::Values()
{
    return m_Values;
}
