#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

using namespace RadonFramework::Core::Types;

class CollectionsQueueTest:public RadonFramework::Diagnostics::Debugging::UnitTest::TestSuite
{
    public:
        CollectionsQueueTest()
        :TestSuite("RadonFramework::Collections::Queue-Test")
        {
            /*AddTest(MakeDelegate(this,&CollectionsQueueTest::Constructor),"Constructor");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Push),"Push");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Poll),"Poll");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Pop),"Pop");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Clear),"Clear");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Size),"Size");
            AddTest(MakeDelegate(this,&CollectionsQueueTest::Peek),"Peek");*/
        }

        /*
        Bool Constructor()
        {
            Queue<UInt32> m_Queue;
            return (m_Queue.Size()==0);
        }

        Bool Push()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            return (m_Queue.Size()==1);
        }

        Bool Poll()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            return (m_Queue.Poll()==5) && (m_Queue.Size()==0);
        }

        Bool Pop()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            m_Queue.Pop();
            return (m_Queue.Size()==0);
        }

        Bool Clear()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            m_Queue.Clear();
            return (m_Queue.Size()==0);
        }

        Bool Size()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            return (m_Queue.Size()==1);
        }

        Bool Peek()
        {
            Queue<UInt32> m_Queue;
            UInt32 i=5;
            m_Queue.Push(i);
            return (m_Queue.Peek()==5) && (m_Queue.Size()==1);
        }*/
};

CollectionsQueueTest QueueTest;
