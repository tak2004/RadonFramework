#ifndef RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
#define RF_COLLECTIONS_ALGORITHM_FINDALL_HPP
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
struct FindAllEnumeratorTaskData
{
    explicit FindAllEnumeratorTaskData(FUNCTION function)
    :Function(function)
    {}
    FUNCTION Function;
    typename C::ConstEnumeratorType Enumeable;
    RF_Type::UInt32 From;
    RF_Type::UInt32 Steps;
    RF_Type::AtomicInt32* OverallWork;
    RF_Collect::Array<RF_Type::UInt8>* Results;
    RF_Type::AtomicInt32* Hits;
};

template <class C, typename FUNCTION>
void FindAllEnumeratorTaskFunction(void* Data)
{
    auto* data = reinterpret_cast<FindAllEnumeratorTaskData<C, FUNCTION>*>(Data);
    data->Enumeable.MoveBy(data->From);
    RF_Type::Int32 hits = 0;
    RF_Type::UInt32 i, end;
    for(i = 0, end = data->Steps; i < end; ++i, ++data->Enumeable)
    {
        if (data->Function(data->Enumeable))
        {
            data->Results->Item(i)=1;
            ++hits;
        }
        else
        {
            data->Results->Item(i)=0;
        }
    }
    RF_Type::Int32 negativeLoopCounter = -static_cast<RF_Type::Int32>(i);
    data->OverallWork->Add(negativeLoopCounter);
    data->Hits->Add(hits);
}

template <class C, typename FUNCTION>
Memory::AutoPointerArray<RF_Type::Size> FindAll(const C& Enumerable, FUNCTION Function)
{
    auto enumerator = Enumerable.GetConstEnumerator();    
    RF_Type::Size elements = enumerator.Size();
    RF_Type::AtomicInt32 hits;
    RF_Collect::Array<RF_Type::UInt8> results(elements);

    if(RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().CanQueue())
    {
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
            auto* task = new FindAllEnumeratorTaskData<C, FUNCTION>(Function);
            task->Enumeable = enumerator;
            task->From = offset;
            task->Steps = jobsPerWorker + extra;
            task->OverallWork = &overallWork;
            task->Results = &results;
            task->Hits = &hits;
            RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().QueueUserWorkItem(FindAllEnumeratorTaskFunction<C, FUNCTION>, task);
            offset += jobsPerWorker + extra;
        }

        // Wait for other threads. Sleep(0) will ensure that the thread return if no
        // other process/thread will work for the rest of the time slice on this core.
        RF_Time::TimeSpan sleep = RF_Time::TimeSpan::CreateByTicks(0);
        while(overallWork != 0)
        {
        
            RadonFramework::System::Threading::Thread::Sleep(sleep);
        }
    }
    else
    {
        for(RF_Type::Size i = 0; i < elements; ++i, ++enumerator)
        {
            if(Function(enumerator))
            {
                hits.Increment();
                results(i) = 1;
            }
            else
            {
                results(i) = 0;
            }
        }
    }

    RF_Mem::AutoPointerArray<RF_Type::Size> result(hits);
    for (RF_Type::Size i = 0, ci = 0; i < elements; ++i)
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

#ifndef RF_SHORTHAND_NAMESPACE_ALGO
#define RF_SHORTHAND_NAMESPACE_ALGO
namespace RF_Algo = RadonFramework::Collections::Algorithm;
#endif

#endif // RF_COLLECTIONS_ALGORITHM_FINDALL_HPP