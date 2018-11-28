#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"
#include <stdlib.h>
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Diagnostics::Debugging;
using namespace RadonFramework::IO;

#ifndef NDEBUG
AssertHandler::Callback AssertHandler::Override = 0;

void AssertHandler::Process(const char* Test,
                            const char* Message,
                            const char* Filename,
                            int Line)
{
  LogFatalError("%s(%d): %s\n\t%s\n", Filename, Line, Test, Message);
  abort();
}
#endif