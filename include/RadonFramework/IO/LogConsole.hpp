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
                void WriteInfo(const RFTYPE::String& Text);
                void WriteError(const RFTYPE::String& Text);
                void WriteFatalError(const RFTYPE::String& Text);
                void WriteDebug(const RFTYPE::String& Text);
        };
    }
}

#endif // RF_IO_LOGCONSOLE_HPP