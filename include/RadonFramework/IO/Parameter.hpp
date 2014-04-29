#ifndef RF_IO_PARAMETER_HPP
#define RF_IO_PARAMETER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/IO/OptionRule.hpp>
#include <RadonFramework/IO/OptionValue.hpp>

namespace RadonFramework { namespace IO { 

class Parameter
{
public:
    /// Parse standard C application parameter.
    RFTYPE::Bool ParsingWithErrorOutput(const char* argv[], int argc, 
        const Memory::AutoPointerArray<OptionRule>& Rules,
        RFTYPE::String& ErrorMessage);

    /// Parse standard C application parameter.
    RFTYPE::Bool ParsingWithLogging(const char* argv[], int argc,
        const Memory::AutoPointerArray<OptionRule>& Rules);

    /// Parse a string array and write to ErrorMessage if an error occur.
    RFTYPE::Bool SafeParsingWithErrorOutput(
        const Memory::AutoPointerArray<RFTYPE::String>& Parameters,
        const Memory::AutoPointerArray<OptionRule>& Rules,
        RFTYPE::String& ErrorMessage);

    /// Parse a string array.
    RFTYPE::Bool SafeParsingWithLogging(
        const Memory::AutoPointerArray<RFTYPE::String>& Parameters,
        const Memory::AutoPointerArray<OptionRule>& Rules);


    const Memory::AutoPointerArray<OptionValue>& Values();
private:
    Memory::AutoPointerArray<OptionValue> m_Values;
};

} }

#endif // RF_IO_PARAMETER_HPP