#ifndef RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
#define RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>

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
    auto data = reinterpret_cast<EnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    for(RFTYPE::UInt32 i = 0, end = data->Steps; i < end; ++i, ++data->Enumeable)
    {
        data->Function(data->Enumeable);
        data->OverallWork->Decrement();
    }
}

template <class C, typename FUNCTION>
Memory::AutoPointerArray<RFTYPE::Size> FindAll(const C& Enumerable, FUNCTION Function)
{
    Memory::AutoPointerArray<RFTYPE::Size> result;
    auto enumerator = Enumerable.GetEnumerator();

    RFTYPE::Size elements = enumerator.Size();
    RFTYPE::UInt32 worker, cport;
    Singleton<Threading::ThreadPool>::GetInstance().GetThreadCount(worker, cport);
    RFTYPE::UInt32 jobsPerWorker = 0;
    RFTYPE::AtomicInt32 overallWork(elements);
    // this thread will work too
    ++worker;
    while(elements > worker && worker > 1)
    {
        ++jobsPerWorker;
        elements -= worker;
    }
    // decrease to recover worker pool count
    --worker;

    for(RFTYPE::UInt32 i = 0; i < worker; ++i)
    {
        auto task = new EnumeratorTaskData<C, FUNCTION>;
        task->Enumeable = enumerator;
        task->Function = Function;
        task->From = i * jobsPerWorker;
        task->Steps = jobsPerWorker;
        task->OverallWork = &overallWork;
        Singleton<Threading::ThreadPool>::GetInstance().QueueUserWorkItem(EnumeratorTaskFunction<C, FUNCTION>, task);
    }

    // do a part of the job
    enumerator.MoveBy(worker * jobsPerWorker);
    for(RFTYPE::UInt32 i = 0, end = jobsPerWorker + elements; i < end; ++i, ++enumerator)
    {
        Function(enumerator);
        overallWork.Decrement();
    }

    // wait for other threads;
    Time::TimeSpan sleep = Time::TimeSpan::CreateByTicks(Time::TimeSpan::TicksPerMillisecond);
    while(overallWork != 0)
    {
        System::Threading::Thread::Sleep(sleep);
    }
    return result;
}

} } }

#endif // RF_COLLECTIONS_ALGORITHM_FINDALL_HPP