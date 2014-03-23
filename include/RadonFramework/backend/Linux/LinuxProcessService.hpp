#ifndef RF_LINUXPROCESSSERVICE_HPP
#define RF_LINUXPROCESSSERVICE_HPP

#include <RadonFramework/Diagnostics/Profiling/ProcessService.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            class LinuxProcessService:public ProcessService
            {
                public:
                    LinuxProcessService(const RadonFramework::Core::Types::String &Name);
                    Memory::AutoPointer<Process::ProcessTree> GetProcessTree();
                    Memory::AutoPointer<Process::ProcessInformation> GetCurrentProcess();
                    Memory::AutoPointer<Process::ProcessInformation> GetProcessByID(Core::Types::UInt32 ProcessID);
                protected:
                    Collections::AutoVector<Core::Types::String> GetProcessIDsByFolder(const Core::Types::String& Path);
                    Collections::AutoVector<Core::Types::String> ReadProcFile(const Core::Types::String& Path);
            };
        }
    }    
}

#endif // RF_LINUXPROCESSSERVICE_HPP
