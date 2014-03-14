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
                "Constructor");

            AddTest(MakeDelegate(this,&QueueTest::ConstructorCollection),
                "A constructor which copy from an IEnumerable object.");
            
            AddTest(MakeDelegate(this,&QueueTest::CopyConstructor),
                "Copy constructor");

            AddTest(MakeDelegate(this,&QueueTest::ReserveConstructor),
                "Construct a Queue and reserve the specified number of elements.");

            AddTest(MakeDelegate(this,&QueueTest::Clear),
                "Clear Queue");

            AddTest(MakeDelegate(this,&QueueTest::Contains),
                "Check if an specified element is existing in the Queue.");

            AddTest(MakeDelegate(this,&QueueTest::CopyTo),
                "Copy all elements of a Queue to an Array.");

            AddTest(MakeDelegate(this,&QueueTest::Dequeue),
                "Remove the first element of the Queue.");

            AddTest(MakeDelegate(this,&QueueTest::Enqueue),
                "Add an element to the Queue.");

            AddTest(MakeDelegate(this,&QueueTest::GetEnumerator),
                "Test IEnumerator interface of the Queue.");

            AddTest(MakeDelegate(this,&QueueTest::Peek),
                "Get the first element of the Queue.");

            AddTest(MakeDelegate(this,&QueueTest::ToArray),
                "Make a copy of the Queue as Array.");

            AddTest(MakeDelegate(this,&QueueTest::TrimExcess),
                "Remove all reserved nodes of a Queue.");   

            AddTest(MakeDelegate(this,&QueueTest::Swap),
                "Swap the content of two Queue of the same type.");   
        }

        Bool Constructor()
        {
            Queue<UInt32> queue;
            return (0==queue.Count());
        }

        Bool ConstructorCollection()
        {
            Queue<UInt32> collection;
            collection.Enqueue(1);
            collection.Enqueue(2);
            Queue<UInt32> queue(reinterpret_cast<IEnumerable<UInt32>*>(&collection));
            return (2==queue.Count() && 2==*queue.Peek());
        }

        Bool CopyConstructor()
        {
            Queue<UInt32> queue1;
            queue1.Enqueue(1);
            Queue<UInt32> queue2(queue1);
            return (0==queue2.Capacity() && 1==*queue2.Peek());
        }

        Bool ReserveConstructor()
        {
            Queue<UInt32> queue(3);
            return (3==queue.Capacity());
        }

        Bool Clear()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Clear();
            return (0==queue.Count() && 2==queue.Capacity());
        }

        Bool Contains()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Enqueue(3);
            return (true==queue.Contains(2) && false==queue.Contains(4));
        }

        Bool CopyTo()
        {
            Queue<UInt32> queue;
            Array<UInt32> arr(2);
            Array<UInt32> arr1(4);
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Enqueue(3);
            return (true==queue.CopyTo(arr1,1) && false==queue.CopyTo(arr,0) &&
                    1==arr1(1) && 2==arr1(2) && 3==arr1(3));
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
            return (0==queue.Count() && 3==queue.Capacity() && result);
        }

        Bool Enqueue()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            return (1==queue.Count() && 0==queue.Capacity() && 1==*queue.Peek());
        }

        Bool GetEnumerator()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Enqueue(3);
            AutoPointer<IEnumerator<UInt32> > it=queue.GetEnumerator();
            Bool result=true;
            result&=it->MoveNext();
            result&=(*it->Current())==1;
            result&=it->MoveNext();
            result&=(*it->Current())==2;
            result&=it->MoveNext();
            result&=(*it->Current())==3;
            result&=!it->MoveNext();
            return result;
        }

        Bool Peek()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            Bool result=(*queue.Peek())==1;
            queue.Enqueue(2);
            result&=(*queue.Peek())==2;
            UInt32 e;
            queue.Dequeue(e);
            result&=(*queue.Peek())==1;
            queue.Dequeue(e);
            result&=queue.Peek()==0;
            return result;
        }

        Bool ToArray()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            AutoPointer<Array<UInt32> > arr=queue.ToArray();
            return (arr && arr->Count()==1 && arr->GetValue(0)==1);
        }

        Bool TrimExcess()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Enqueue(3);
            UInt32 e;
            queue.Dequeue(e);
            Bool result=queue.Capacity()==1;
            queue.TrimExcess();
            result&=queue.Capacity()==0;
            return result;
        }

        Bool Swap()
        {
            Queue<UInt32> queue;
            queue.Enqueue(1);
            queue.Enqueue(2);
            queue.Enqueue(3);
            Queue<UInt32> queue1;
            queue1.Swap(queue);
            return (queue.Count()==0 && queue1.Count()==3);
        }
};

QueueTest collectionsGenericQueueTestInstance;