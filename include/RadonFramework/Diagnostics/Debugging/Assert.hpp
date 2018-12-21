#ifndef RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/BuildInfo.hpp>

namespace RadonFramework::Diagnostics::Debugging
{
#ifndef NDEBUG
struct AssertHandler
{
  using Callback = void (*)(const char *, const char *, const char *, int);
  static Callback Override;
  static void Process(const char* Test,
                      const char* Message,
                      const char* Filename,
                      int Line);
};

#define RF_ASSERT(test, msg)                                                   \
  {                                                                         \
    if(RadonFramework::BuildInfo::CompileForDebugging ==                    \
           RadonFramework::BuildInfo::DebugMode::True &&      \
       !(test))                                                             \
    {                                                                       \
      if(RF_Debug::AssertHandler::Override)                                 \
        RF_Debug::AssertHandler::Override(#test, #msg, __FILE__, __LINE__); \
      else                                                                  \
        RF_Debug::AssertHandler::Process(#test, #msg, __FILE__, __LINE__);  \
    }                                                                       \
  }
#else
#define RF_ASSERT(test, msg) \
  {                       \
  }
#endif

}  // namespace RadonFramework::Diagnostics::Debugging

#ifndef RF_SHORTHAND_NAMESPACE_DEBUG
#define RF_SHORTHAND_NAMESPACE_DEBUG
namespace RF_Debug = ::RadonFramework::Diagnostics::Debugging;
#endif

#endif  // RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP