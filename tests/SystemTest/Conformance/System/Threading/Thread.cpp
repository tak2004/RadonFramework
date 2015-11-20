#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/Algorithm/Exists.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>
#include <RadonFramework/Threading/Thread.hpp>
#include <RadonFramework/System/Process/ThreadInfo.hpp>
#include <RadonFramework/System/Process.hpp>

using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class TestThread :public RF_Thread::Thread
{
public:
    void Run()
    {
        while(CancelCondition == 0)
        {
            Sleep(RF_Time::TimeSpan::Zero);
        }
    }
    RF_Type::AtomicInt32 CancelCondition;
};

class ThreadingThreadTest:public TestSuite
{
public:
    ThreadingThreadTest()
    :TestSuite("RadonFramework::Threading::Thread-Test")
    {
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Create),
            "ThreadingThreadTest::Create", "Create");
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Destroy),
            "ThreadingThreadTest::Destroy", "Destroy");
    }

    Bool Create()
    {
        RF_Type::Bool result = true;
        TestThread testThread;
        void* handle;
        RF_Type::UInt64 tid;
        RF_SysProc::ThreadInfoList threadInfoBefore, threadInfoAfter;
        RF_Type::UInt32 pid = RFPROC::GetCurrentProcessId();
        // get all threads of process
        RFPROC::GetThreadInfo(pid, threadInfoBefore);       
        handle = RF_SysThread::Create(testThread, tid);
        // thread must be in the process tree now
        RFPROC::GetThreadInfo(pid, threadInfoAfter);
        
        ++testThread.CancelCondition;
        RF_SysThread::Join(handle);
        RF_SysThread::Destroy(handle);

        result &= (handle != 0);
        result &= !RF_Algo::Exists(threadInfoBefore, [tid](decltype(threadInfoBefore)::ConstEnumeratorType& info) {return info->ID == tid; });
        result &= RF_Algo::Exists(threadInfoAfter, [tid](decltype(threadInfoAfter)::ConstEnumeratorType& info) {return info->ID == tid; });
        return result;
    }

    Bool Destroy()
    {
        RF_Type::Bool result = true;
        TestThread testThread;
        void* handle;
        RF_Type::UInt64 tid;
        RF_Type::UInt32 pid = RFPROC::GetCurrentProcessId();
        handle = RF_SysThread::Create(testThread, tid);

        ++testThread.CancelCondition;
        RF_SysThread::Join(handle);
        RF_SysThread::Destroy(handle);

        result &= (handle != 0);
        return result;
    }
};

ThreadingThreadTest ThreadTest;
