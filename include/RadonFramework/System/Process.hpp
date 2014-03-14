#ifndef RF_SYSTEM_PROCESS_HPP
#define RF_SYSTEM_PROCESS_HPP

namespace RadonFramework
{
    namespace System
    {
        namespace Process
        {
            typedef Memory::AutoPointer<ProcessTree> (*GetProcessTreeCallback)();
            typedef Memory::AutoPointer<ProcessInformation> (*GetCurrentProcess)();
            typedef RFTYPE::UInt32 (*GetCurrentProcessID)();
            typedef Memory::AutoPointer<ProcessInformation> (*GetProcessByID)(RFTYPE::UInt32 ProcessID);

            extern GetProcessTreeCallback GetProcessTree;
            extern GetCurrentProcessIDCallback 
        }
    }
}

#endif // RF_SYSTEM_PROCESS_HPP