#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/Debugger.hpp"

#if defined(RF_WINDOWS)
#include <windows.h>
#endif

using namespace RadonFramework::Core::Types;

namespace RadonFramework::System::IO {

void RadonFramework::System::IO::Debugger::WriteLine(const RF_Type::String &Str)
{
#if defined(RF_WINDOWS)
    RF_Type::String debugLine = RF_Type::String::Format("%s\n"_rfs, Str.c_str());
    OutputDebugString(debugLine.c_str());
#endif
}

Debugger::Debugger()
{
}

}