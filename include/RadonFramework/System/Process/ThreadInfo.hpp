#ifndef RF_SYSTEM_PROCESS_THREADINFO_HPP
#define RF_SYSTEM_PROCESS_THREADINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework::System::Process {

struct ThreadInfo
{
    //General
    RF_Type::UInt64 ID;
    RF_Thread::ThreadPriority::Type Priority;
    //Timing
    RF_Time::DateTime CreationTime;
    RF_Time::DateTime ExitTime;
    RF_Time::TimeSpan KernelTime;
    RF_Time::TimeSpan UserTime;
};

using ThreadInfoList = RF_Collect::Array<ThreadInfo>;

}  // namespace RadonFramework::System::Process

#endif // RF_SYSTEM_PROCESS_THREADINFO_HPP