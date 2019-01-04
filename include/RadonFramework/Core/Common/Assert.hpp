#pragma once

#include <RadonFramework/BuildInfo.hpp>

namespace RadonFramework::Core::Common
{
#ifndef NDEBUG
struct AssertHandler
{
  using Callback = void (*)(const char*, const char*, const char*, int);
  static Callback Override;
  static void Process(const char* Test,
                      const char* Message,
                      const char* Filename,
                      int Line);
};

#define RF_ASSERT(test, msg)                                                 \
  {                                                                          \
    if(RadonFramework::BuildInfo::CompileForDebugging ==                     \
           RadonFramework::BuildInfo::DebugMode::True &&                     \
       !(test))                                                              \
    {                                                                        \
      if(RF_Common::AssertHandler::Override)                                 \
        RF_Common::AssertHandler::Override(#test, #msg, __FILE__, __LINE__); \
      else                                                                   \
        RF_Common::AssertHandler::Process(#test, #msg, __FILE__, __LINE__);  \
    }                                                                        \
  }
#else
#define RF_ASSERT(test, msg) \
  {                          \
  }
#endif

}  // namespace RadonFramework::Core::Common

namespace RF_Common = RadonFramework::Core::Common;