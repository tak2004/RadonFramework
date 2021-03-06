#ifndef RF_COLLECTIONS_ALGORITHM_FOREACHBULK_HPP
#define RF_COLLECTIONS_ALGORITHM_FOREACHBULK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Time/ScopeTimer.hpp>

namespace RadonFramework::Collections::Algorithm
{
template <class C, typename FUNCTION>
void ForEachBulkEnumeratorTaskFunction(void* Data)
{
  auto* data = reinterpret_cast<ForEachEnumeratorTaskData<C, FUNCTION>*>(Data);
  data->Enumeable.MoveBy(data->From);
  data->Function(data->Enumeable, data->Steps);
  RF_Type::Int32 negativeLoopCounter =
      -static_cast<RF_Type::Int32>(data->Steps);
  data->OverallWork->Add(negativeLoopCounter);
}

template <class C, typename FUNCTION>
void ForEachBulk(const C& Enumerable, FUNCTION Function)
{
  auto enumerator = Enumerable.GetEnumerator();
  RF_Type::Size elements = enumerator.Size();

  if(RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().CanQueue() &&
     elements > 1)
  {
    RF_Type::UInt32 worker;
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().GetThreadCount(
        worker);
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
      auto* task = new ForEachEnumeratorTaskData<C, FUNCTION>(Function);
      task->Enumeable = enumerator;
      task->From = offset;
      task->Steps = jobsPerWorker + extra;
      task->OverallWork = &overallWork;
      RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance()
          .QueueUserWorkItem(ForEachBulkEnumeratorTaskFunction<C, FUNCTION>,
                             task);
      offset += jobsPerWorker + extra;
    }

    // Wait for other threads. Sleep(0) will ensure that the thread return if no
    // other process/thread will work for the rest of the time slice on this
    // core.
    Time::TimeSpan sleep = Time::TimeSpan::CreateByTicks(0);
    while(overallWork != 0)
    {
      RF_Thread::Thread::Sleep(sleep);
    }
  }
  else
  {
    Function(enumerator, elements);
  }
}

template <class C, typename FUNCTION>
void ForEachBulk(const C& Enumerable,
                 const RF_Type::UInt32 Bulksize,
                 FUNCTION Function)
{
  auto enumerator = Enumerable.GetEnumerator();
  RF_Type::Size elements = enumerator.Size();

  if(RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().CanQueue() &&
     elements > 1)
  {
    RF_Type::AtomicInt32 overallWork(elements);
    RF_Type::UInt32 steps = Bulksize;
    for(RF_Type::UInt32 i = 0; i < elements;)
    {
      auto* task = new ForEachEnumeratorTaskData<C, FUNCTION>(Function);
      task->Enumeable = enumerator;
      task->From = i;
      task->Steps = steps;
      task->OverallWork = &overallWork;
      RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance()
          .QueueUserWorkItem(ForEachBulkEnumeratorTaskFunction<C, FUNCTION>,
                             task);
      i = i + steps;
      if(i > elements)
      {
        steps = elements - (i - Bulksize);
        i = elements - 1;
      }
    }

    // Wait for other threads. Sleep(0) will ensure that the thread return if no
    // other process/thread will work for the rest of the time slice on this
    // core.
    Time::TimeSpan sleep = Time::TimeSpan::CreateByTicks(0);
    while(overallWork != 0)
    {
      RF_Thread::Thread::Sleep(sleep);
    }
  }
  else
  {
    Function(enumerator, elements);
  }
}

}  // namespace RadonFramework::Collections::Algorithm

#ifndef RF_SHORTHAND_NAMESPACE_ALGO
#define RF_SHORTHAND_NAMESPACE_ALGO
namespace RF_Algo = RadonFramework::Collections::Algorithm;
#endif

#endif  // RF_COLLECTIONS_ALGORITHM_FOREACHBULK_HPP