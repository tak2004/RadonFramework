#ifndef RF_IO_LOGDEBUGGEROUTPUT_HPP
#define RF_IO_LOGDEBUGGEROUTPUT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Appender.hpp>

namespace RadonFramework::IO {

/** @brief This class relay the log messages to the IDE debug output window.
*
* Usage:
* RF_Mem::AutoPointer<RF_Diag::Appender> console(new RF_IO::LogDebuggerOutput);
* RF_IO::Log::AddAppender(console);
* RF_IO::LogInfo("Hello world!");
**/
class LogDebuggerOutput:public Diagnostics::Appender
{
public:
    void WriteInfo(const RF_Type::String& Text);
    void WriteError(const RF_Type::String& Text);
    void WriteFatalError(const RF_Type::String& Text);
    void WriteDebug(const RF_Type::String& Text);
};

}

#endif // RF_IO_LOGDEBUGGEROUTPUT_HPP