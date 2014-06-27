#ifndef RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
#define RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Collections { namespace Algorithm {

template <class C, typename FUNCTION>
struct EnumeratorTaskData
{
    FUNCTION Function;
    typename C::EnumeratorType Enumeable;
    RFTYPE::UInt32 From;
    RFTYPE::UInt32 Steps;
    RFTYPE::AtomicInt32* OverallWork;
    Array<RFTYPE::UInt8>* Results;
    RFTYPE::AtomicInt32* Hits;
};

template <class C, typename FUNCTION>
void EnumeratorTaskFunction(void* Data)
{
    auto* data = reinterpret_cast<EnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    for(RFTYPE::UInt32 i = 0, end = data->Steps; i < end; ++i, ++data->Enumeable)
    {
        if (data->Function(data->Enumeable))
        {
            data->Results->Item(i)=1;
            data->Hits->Increment();
        }
        else
        {
            data->Results->Item(i)=0;
        }
        data->OverallWork->Decrement();
    }
}

template <class C, typename FUNCTION>
Memory::AutoPointerArray<RFTYPE::Size> FindAll(const C& Enumerable, FUNCTION Function)
{
    auto enumerator = Enumerable.GetEnumerator();
    
    RFTYPE::Size elements = enumerator.Size();
    RFTYPE::UInt32 worker, cport;
    Singleton<Threading::ThreadPool>::GetInstance().GetThreadCount(worker, cport);
    RFTYPE::UInt32 jobsPerWorker = 0;    
    RFTYPE::AtomicInt32 overallWork(elements);
    RFTYPE::AtomicInt32 hits;
    Array<RFTYPE::UInt8> results(elements);
    
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
        task->Results = &results;
        task->Hits = &hits;
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

    Memory::AutoPointerArray<RFTYPE::Size> result(new RFTYPE::Size[hits], hits);
    for (RFTYPE::Size i = 0, ci = 0; i < elements; ++i)
    {
        if (results(i) == 1)
        {
            result[ci] = i;
            ++ci;
        }
    }
    return result;
}

} } }

#endif // RF_COLLECTIONS_ALGORITHM_FINDALL_HPP