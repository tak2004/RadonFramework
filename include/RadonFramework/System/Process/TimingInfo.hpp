#ifndef RF_SYSTEM_PROCESS_TIMINGINFO_HPP
#define RF_SYSTEM_PROCESS_TIMINGINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework::System::Process {

struct TimingInfo
{
    RF_Time::DateTime CreationTime;
    RF_Time::DateTime ExitTime;
    RF_Time::TimeSpan KernelTime;
    RF_Time::TimeSpan UserTime;
};

}  // namespace RadonFramework::System::Process

#endif // RF_SYSTEM_PROCESS_TIMINGINFO_HPP