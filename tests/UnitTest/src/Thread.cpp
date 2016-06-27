#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/System/Threading/Thread.hpp>

using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class DerivedThread:public Thread
{
public:
    void Run()
    {

    }
};

class ThreadingThreadTest:public TestSuite
{
public:
    ThreadingThreadTest()
    :TestSuite("RadonFramework::Threading::Thread-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Constructor),
            "ThreadingThreadTest::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this,&ThreadingThreadTest::Start),
            "ThreadingThreadTest::Start"_rfs, "Start"_rfs);
    }

    Bool Constructor()
    {
        DerivedThread m_Thread1;
        return true;
    }

    Bool Start()
    {
        DerivedThread m_Thread1;
        m_Thread1.Start();
        m_Thread1.Exit();
        m_Thread1.Join();
        return m_Thread1.Working();
    }
};

ThreadingThreadTest ThreadTest;
