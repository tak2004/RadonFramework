#ifndef RF_SYSTEM_PROCESS_THREADINFO_HPP
#define RF_SYSTEM_PROCESS_THREADINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>

namespace RadonFramework { namespace System { namespace Process {

struct ThreadInfo
{
    //General
    RFTYPE::UInt32 ID;
    RadonFramework::Threading::ThreadPriority::Type Priority;
    //Timing
    RadonFramework::Time::DateTime CreationTime;
    RadonFramework::Time::DateTime ExitTime;
    RadonFramework::Time::TimeSpan KernelTime;
    RadonFramework::Time::TimeSpan UserTime;
};

typedef RadonFramework::Collections::Array<ThreadInfo> ThreadInfoList;

} } }

#endif // RF_SYSTEM_PROCESS_THREADINFO_HPP