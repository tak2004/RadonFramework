#include "RadonFramework/IO/LogConsole.hpp"
#include "RadonFramework/Radon.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/String.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Time.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;

int main()
{
  Radon framework;

  RF_Mem::AutoPointer<RF_IO::Appender> console(new LogConsole);
  Log::AddAppender(console);

  RF_Collect::List<String> missingFunctions;
  if(!RF_SysEnv::IsSuccessfullyDispatched())
    RF_SysEnv::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysMem::IsSuccessfullyDispatched())
    RF_SysMem::GetNotDispatchedFunctions(missingFunctions);
  if(!RFFILE::IsSuccessfullyDispatched())
    RFFILE::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysTime::IsSuccessfullyDispatched())
    RF_SysTime::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysStr::IsSuccessfullyDispatched())
    RF_SysStr::GetNotDispatchedFunctions(missingFunctions);
  if(!RFPROC::IsSuccessfullyDispatched())
    RFPROC::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysMem::IsSuccessfullyDispatched())
    RF_SysMem::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysHardware::IsSuccessfullyDispatched())
    RF_SysHardware::GetNotDispatchedFunctions(missingFunctions);
  if(!RF_SysThread::IsSuccessfullyDispatched())
    RF_SysThread::GetNotDispatchedFunctions(missingFunctions);
  for(Size i = 0; i < missingFunctions.Count(); ++i)
  {
    LogError("Missing system function: %s", missingFunctions[i].c_str());
  }
  RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance()
      .DisableAndWaitTillDone();
  return 0;
}
