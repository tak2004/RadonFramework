#ifndef RF_COLLECTIONS_ALGORITHM_EXISTS_HPP
#define RF_COLLECTIONS_ALGORITHM_EXISTS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

#include <RadonFramework/System/Threading/Thread.hpp>

namespace RadonFramework { namespace Collections { namespace Algorithm {

template <class C, typename FUNCTION>
struct ExistsEnumeratorTaskData
{
    explicit ExistsEnumeratorTaskData(FUNCTION function)
    :Function(function)
    {}
    FUNCTION Function;
    typename C::ConstEnumeratorType Enumeable;
    RF_Type::UInt32 From;
    RF_Type::UInt32 Steps;
    RF_Type::AtomicInt32* OverallWork;
    RF_Type::AtomicInt32* Hits;
};

template <class C, typename FUNCTION>
void ExistsEnumeratorTaskFunction(void* Data)
{
    auto* data = reinterpret_cast<ExistsEnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    RF_Type::Size i, end;
    for(i = 0, end = data->Steps; 
        i < end && (*data->Hits) == 0;
        ++i, ++data->Enumeable)
    {
        if (data->Function(data->Enumeable))
        {
            data->Hits->Increment();
        }
    }
    RF_Type::Int32 negativeLoopCounter = -static_cast<RF_Type::Int32>(i);
    data->OverallWork->Add(negativeLoopCounter);
}

template <class C, typename FUNCTION>
RF_Type::Bool Exists(const C& Enumerable, FUNCTION Function)
{
    auto enumerator = Enumerable.GetConstEnumerator();    
    RF_Type::Size elements = enumerator.Size();
    RF_Type::AtomicInt32 hits;

    if(RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().CanQueue() && elements > 1)
    {
        RF_Type::UInt32 worker, cport;
        RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().GetThreadCount(worker, cport);
        RF_Type::UInt32 jobsPerWorker = 0;    
        RF_Type::AtomicInt32 overallWork(elements);
    
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

        for(RF_Type::UInt32 i = 0, offset = 0, Extra = 1; i < worker; ++i)
        {
            if(elements <= i)
                Extra = 0;
            auto* task = new ExistsEnumeratorTaskData<C, FUNCTION>(Function);
            task->Enumeable = enumerator;
            task->From = offset;
            task->Steps = jobsPerWorker + Extra;
            task->OverallWork = &overallWork;
            task->Hits = &hits;
            RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().QueueUserWorkItem(ExistsEnumeratorTaskFunction<C, FUNCTION>, task);
            offset += jobsPerWorker + Extra;
        }

        // Wait for other threads. Sleep(0) will ensure that the thread return if no
        // other process/thread will work for the rest of the time slice on this core.
        RF_Time::TimeSpan sleep = RF_Time::TimeSpan::CreateByTicks(0);
        while(overallWork != 0 && hits == 0)
        {        
            RF_Thread::Thread::Sleep(sleep);
        }
    }
    else
    {
        for(RF_Type::Size i = 0; i < elements; ++i, ++enumerator)
        {
            if (Function(enumerator))
                ++hits;
        }
    }
    return hits != 0;
}

} } }

#ifndef RF_SHORTHAND_NAMESPACE_ALGO
#define RF_SHORTHAND_NAMESPACE_ALGO
namespace RF_Algo = RadonFramework::Collections::Algorithm;
#endif

#endif // RF_COLLECTIONS_ALGORITHM_EXISTS_HPP