#ifndef RF_WINDOWSPROCESSSERVICE_HPP
#define RF_WINDOWSPROCESSSERVICE_HPP

#include <RadonFramework/Diagnostics/Profiling/ProcessService.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <Windows.h>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    class WindowsProcessService:public ProcessService
		    {
			    public:
				    WindowsProcessService(const RadonFramework::Core::Types::String &Name);
				    Memory::AutoPointer<Process::ProcessTree> GetProcessTree();
				    Memory::AutoPointer<Process::ProcessInformation> GetCurrentProcess();
				    Core::Types::UInt32 GetCurrentProcessID();
				    Memory::AutoPointer<Process::ProcessInformation> GetProcessByID(Core::Types::UInt32 ProcessID);

				    RadonFramework::Time::TimeSpan FILETIMEToTimeSpan(const FILETIME &Time);
				    RadonFramework::Time::DateTime FILETIMEToDate(const FILETIME &Time);
		    };
	    }
    }
}

#endif // RF_WINDOWSPROCESSSERVICE_HPP