#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/Queue.hpp>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class QueueTest:public TestSuite
{
public:
    QueueTest()
    :TestSuite("RadonFramework::Collections::Queue-Test")
    {
        AddTest(MakeDelegate(this,&QueueTest::Constructor),
            "QueueTest::Constructor",
            "Constructor");

        AddTest(MakeDelegate(this,&QueueTest::Clear),
            "QueueTest::Clear",
            "Clear Queue");

        AddTest(MakeDelegate(this,&QueueTest::Dequeue),
            "QueueTest::Dequeue",
            "Remove the first element of the Queue.");

        AddTest(MakeDelegate(this,&QueueTest::Enqueue),
            "QueueTest::Enqueue",
            "Add an element to the Queue.");
    }

    Bool Constructor()
    {
        Queue<UInt32> queue;
        return queue.IsEmpty();
    }

    Bool Clear()
    {
        Queue<UInt32> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Clear();
        return (queue.IsEmpty());
    }

    Bool Dequeue()
    {
        Queue<UInt32> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);
        UInt32 e;
        Bool result=queue.Dequeue(e);
        result&=e==3;
        result&=queue.Dequeue(e);
        result&=e==2;
        result&=queue.Dequeue(e);
        result&=e==1;
        result&=queue.Dequeue(e)==false;
        return (queue.IsEmpty() && result);
    }

    Bool Enqueue()
    {
        Queue<UInt32> queue;
        queue.Enqueue(1);
        UInt32 result=0;
        return (!queue.IsEmpty() && queue.Dequeue(result) && result == 1);
    }
};

QueueTest collectionsGenericQueueTestInstance;