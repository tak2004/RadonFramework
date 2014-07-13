#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Threading/IRunnable.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>

using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class JobForThread:public IRunnable
{
    public:
        explicit JobForThread(Thread* Instance=0)
        :m_Thread(Instance)
        {
        }
        void Run()
        {
            if (m_Thread)
                for(;;)
                    m_Thread->CheckCancel();
        }
    protected:
        Thread* m_Thread;
};

class DerivedThread:public Thread
{
public:
    void Run()
    {
        for(;;)
            CheckCancel();
    }
};

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
        DerivedThread m_Thread1;
        JobForThread m_JobForThread;
        RadonFramework::Memory::AutoPointer<Thread> m_Thread2=RadonFramework::Memory::AutoPointer<Thread>(new Thread(&m_JobForThread));
        return true;
    }

    Bool Start()
    {
        DerivedThread m_Thread1;
        JobForThread m_JobForThread(&m_Thread1);
        RadonFramework::Memory::AutoPointer<Thread> m_Thread2=RadonFramework::Memory::AutoPointer<Thread>(new Thread(&m_JobForThread));
        m_Thread1.Start();
        m_Thread2->Start();
        m_Thread1.Exit();
        m_Thread1.Join();
        m_Thread2->Exit();
        m_Thread2->Join();
        return m_Thread1.Working() && m_Thread2->Working();
    }
};

ThreadingThreadTest ThreadTest;
