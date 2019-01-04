#include "RadonFramework/Core/Common/Assert.hpp"
#include <stdlib.h>
#include "RadonFramework/IO/Log.hpp"

namespace RadonFramework::Core::Common
{
#ifndef NDEBUG
AssertHandler::Callback AssertHandler::Override = 0;

void AssertHandler::Process(const char* Test,
                            const char* Message,
                            const char* Filename,
                            int Line)
{
  RF_IO::LogFatalError("%s(%d): %s\n\t%s\n", Filename, Line, Test, Message);
  abort();
}
#endif
}  // namespace RadonFramework::Core::Common