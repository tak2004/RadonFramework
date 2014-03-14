#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_THREADINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_THREADINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace Process
            {
                struct ThreadData
                {
                    //General
                    RadonFramework::Core::Types::UInt32 ID;
                    RadonFramework::Threading::ThreadPriority::Type Priority;
                    RadonFramework::Core::Types::String PriorityAsString()const;
                    //Timing
                    RadonFramework::Time::DateTime CreationTime;
                    RadonFramework::Time::DateTime ExitTime;
                    RadonFramework::Time::TimeSpan KernelTime;
                    RadonFramework::Time::TimeSpan UserTime;
                };

                class ThreadInformation
                {
                    public:
                        ThreadInformation();
                        ThreadInformation(const ThreadInformation& Copy);
                        ThreadInformation(Memory::AutoPointer<ThreadData> Data);
                        const ThreadData& Data()const;
                        void Swap(ThreadInformation& Other);
                    protected:
                        Memory::AutoPointer<ThreadData> m_Data;
                };
            }
        }        
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_THREADINFORMATION_HPP