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

namespace RadonFramework
{
    namespace IO
    {
        struct Parameter
        {
            static RFTYPE::Bool Parse(
                const Memory::AutoPointerArray<RFTYPE::String>& Parameters,
                const Memory::AutoPointerArray<OptionRule>& Rules,
                RFTYPE::String& ErrorMessage);

            static RFTYPE::Bool Parse(
                const Memory::AutoPointerArray<RFTYPE::String>& Parameters,
                const Memory::AutoPointerArray<OptionRule>& Rules);

            static const Memory::AutoPointerArray<OptionValue>& Values();
        };
    }
}

#endif // RF_IO_PARAMETER_HPP