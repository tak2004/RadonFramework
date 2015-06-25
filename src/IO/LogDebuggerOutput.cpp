#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/LogDebuggerOutput.hpp"
#include "RadonFramework/System/IO/Debugger.hpp"

using namespace RadonFramework::System::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics;

namespace RadonFramework { namespace IO {

void LogDebuggerOutput::WriteInfo(const String& Text)
{
    Debugger::GetInstance().WriteLine(Text);
}

void LogDebuggerOutput::WriteError(const String& Text)
{
    Debugger::GetInstance().WriteLine(Text);
}

void LogDebuggerOutput::WriteFatalError(const String& Text)
{
    Debugger::GetInstance().WriteLine(Text);
}

void LogDebuggerOutput::WriteDebug(const String& Text)
{
    Debugger::GetInstance().WriteLine(Text);
}

} }