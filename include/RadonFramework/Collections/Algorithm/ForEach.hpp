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
struct ForEachEnumeratorTaskData
{
    FUNCTION Function;
    typename C::EnumeratorType Enumeable;
    RF_Type::UInt32 From;
    RF_Type::UInt32 Steps;
    RF_Type::AtomicInt32* OverallWork;
};

template <class C, typename FUNCTION>
void ForEachEnumeratorTaskFunction(void* Data)
{
    auto* data = reinterpret_cast<ForEachEnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    for(RF_Type::UInt32 i = 0, end = data->Steps; i < end; ++i, ++data->Enumeable)
    {
        data->Function(data->Enumeable);
        data->OverallWork->Decrement();
    }
}

template <class C, typename FUNCTION>
void ForEach(const C& Enumerable, FUNCTION Function)
{
    auto enumerator = Enumerable.GetEnumerator();
    
    RF_Type::Size elements = enumerator.Size();
    RF_Type::UInt32 worker, cport;
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().GetThreadCount(worker, cport);
    RF_Type::UInt32 jobsPerWorker = 0;    
    RF_Type::AtomicInt32 overallWork(elements);
    RF_Type::UInt32 extra = 1;
    
    if(elements > worker)
    {
        jobsPerWorker = elements / worker;
        elements -= jobsPerWorker * worker;
    }
    else
    {
        jobsPerWorker = 1;
        worker = elements;
        extra = 0;
    }
    
    for(RF_Type::UInt32 i = 0, offset = 0; i < worker; ++i)
    {
        if(elements <= i)
            extra = 0;
        auto* task = new ForEachEnumeratorTaskData<C, FUNCTION>;
        task->Enumeable = enumerator;
        task->Function = Function;
        task->From = offset;
        task->Steps = jobsPerWorker + extra;
        task->OverallWork = &overallWork; 
        RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().QueueUserWorkItem(ForEachEnumeratorTaskFunction<C, FUNCTION>, task);
        offset += jobsPerWorker + extra;
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

#ifndef RF_SHORTHAND_NAMESPACE_ALGO
#define RF_SHORTHAND_NAMESPACE_ALGO
namespace RF_Algo = RadonFramework::Collections::Algorithm;
#endif

#endif // RF_COLLECTIONS_ALGORITHM_FOREACH_HPP