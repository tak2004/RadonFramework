#ifndef RF_COLLECTIONS_ALGORITHM_FOREACH_HPP
#define RF_COLLECTIONS_ALGORITHM_FOREACH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Time/ScopeTimer.hpp>

namespace RadonFramework { namespace Collections { namespace Algorithm {

template <class C, typename FUNCTION>
struct EnumeratorTaskData
{
    FUNCTION Function;
    typename C::EnumeratorType Enumeable;
    RFTYPE::UInt32 From;
    RFTYPE::UInt32 Steps;
    RFTYPE::AtomicInt32* OverallWork;
};

template <class C, typename FUNCTION>
void EnumeratorTaskFunction(void* Data)
{
    auto* data = reinterpret_cast<EnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    for(RFTYPE::UInt32 i = 0, end = data->Steps; i < end; ++i, ++data->Enumeable)
    {
        data->Function(data->Enumeable);
        data->OverallWork->Decrement();
    }
}

template <class C, typename FUNCTION>
void ForEach(const C& Enumerable, FUNCTION Function)
{
    auto enumerator = Enumerable.GetEnumerator();
    
    RFTYPE::Size elements = enumerator.Size();
    RFTYPE::UInt32 worker, cport;
    Singleton<Threading::ThreadPool>::GetInstance().GetThreadCount(worker, cport);
    RFTYPE::UInt32 jobsPerWorker = 0;    
    RFTYPE::AtomicInt32 overallWork(elements);
    
    if(elements > worker)
    {
        jobsPerWorker = elements / worker;
        elements -= jobsPerWorker * worker;
    }
    else
    {
        jobsPerWorker = 1;
        worker = elements;
    }
    
    for(RFTYPE::UInt32 i = 0, offset = 0, Extra = 1; i < worker; ++i)
    {
        if(elements <= i)
            Extra = 0;
        auto* task = new EnumeratorTaskData<C, FUNCTION>;
        task->Enumeable = enumerator;
        task->Function = Function;
        task->From = offset;
        task->Steps = jobsPerWorker + Extra;
        task->OverallWork = &overallWork; 
        Singleton<Threading::ThreadPool>::GetInstance().QueueUserWorkItem(EnumeratorTaskFunction<C, FUNCTION>, task); 
        offset += jobsPerWorker + Extra;
    }
    
    // Wait for other threads. Sleep(0) will ensure that the thread return if no
    // other process/thread will work for the rest of the time slice on this core.
    Time::TimeSpan sleep = Time::TimeSpan::CreateByTicks(0);
    while(overallWork != 0)
    {
        System::Threading::Thread::Sleep(sleep);
    }
}

} } }

#endif // RF_COLLECTIONS_ALGORITHM_FOREACH_HPP