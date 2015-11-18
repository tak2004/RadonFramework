#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Threading/IRunnable.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>
#include <RadonFramework/Threading/Thread.hpp>

using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class ThreadingThreadTest:public TestSuite
{
public:
    ThreadingThreadTest()
    :TestSuite("RadonFramework::Threading::Thread-Test")
    {
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Constructor),
            "ThreadingThreadTest::Constructor", "Constructor");
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Start),
            "ThreadingThreadTest::Start", "Start");
    }

    Bool Constructor()
    {
        RF_Type::Bool result = true;
        RF_Thread::Thread testThread;
        void* handle;
        RF_Type::Int64 pid;
        handle = RF_SysThread::Create(testThread, pid);
        result &= (handle != 0);
        return result;
    }

    Bool Start()
    {
        return false;
    }
};

ThreadingThreadTest ThreadTest;
