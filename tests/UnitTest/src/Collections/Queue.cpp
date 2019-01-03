#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/Queue.hpp>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Test::UnitTest;

class QueueTest:public TestSuite
{
public:
    QueueTest()
    :TestSuite("RadonFramework::Collections::Queue-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&QueueTest::Constructor),
            "QueueTest::Constructor"_rfs,
            "Constructor"_rfs);

        AddTest(MakeDelegate(this,&QueueTest::Clear),
            "QueueTest::Clear"_rfs,
            "Clear Queue"_rfs);

        AddTest(MakeDelegate(this,&QueueTest::Dequeue),
            "QueueTest::Dequeue"_rfs,
            "Remove the first element of the Queue."_rfs);

        AddTest(MakeDelegate(this,&QueueTest::Enqueue),
            "QueueTest::Enqueue"_rfs,
            "Add an element to the Queue."_rfs);
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