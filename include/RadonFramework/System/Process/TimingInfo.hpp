#ifndef RF_SYSTEM_PROCESS_TIMINGINFO_HPP
#define RF_SYSTEM_PROCESS_TIMINGINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework { namespace System { namespace Process {

struct TimingInfo
{
    RadonFramework::Time::DateTime CreationTime;
    RadonFramework::Time::DateTime ExitTime;
    RadonFramework::Time::TimeSpan KernelTime;
    RadonFramework::Time::TimeSpan UserTime;
};

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_TIMINGINFO_HPP