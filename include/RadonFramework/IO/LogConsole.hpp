#ifndef RF_IO_LOGCONSOLE_HPP
#define RF_IO_LOGCONSOLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Appender.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class LogConsole:public Diagnostics::Appender
        {
            public:
                void WriteInfo(const RF_Type::String& Text);
                void WriteError(const RF_Type::String& Text);
                void WriteFatalError(const RF_Type::String& Text);
                void WriteDebug(const RF_Type::String& Text);
        };
    }
}

#endif // RF_IO_LOGCONSOLE_HPP