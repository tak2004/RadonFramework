#ifndef RF_IO_OPTIONVALUE_HPP
#define RF_IO_OPTIONVALUE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class OptionValue
        {
            public:
                OptionValue();

                OptionValue(const OptionValue& Copy);

                OptionValue(const char* Value);

                OptionValue(const Core::Types::String& Value);
                                
                OptionValue& operator=(const OptionValue& Other);

                OptionValue& operator=(const Core::Types::String& Value);

                void Set();

                Core::Types::Bool IsSet()const;

                const Core::Types::String& Value()const;				
            protected:
                Core::Types::String m_Value;
                Core::Types::Bool m_ValueSet;
        };
    }
}

#endif