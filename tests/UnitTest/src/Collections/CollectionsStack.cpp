#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/Stack.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

class CollectionsStackTest:public RadonFramework::Diagnostics::Debugging::UnitTest::TestSuite
{
    public:
        CollectionsStackTest()
            :TestSuite("RadonFramework::Collections::Stack-Test")
        {
            AddTest(MakeDelegate(this,&CollectionsStackTest::Constructor),
                "CollectionsStackTest::Constructor", "Constructor");
            AddTest(MakeDelegate(this,&CollectionsStackTest::Push),
                "CollectionsStackTest::Push", "Push");
            AddTest(MakeDelegate(this,&CollectionsStackTest::Pop),
                "CollectionsStackTest::Pop", "Pop");
            AddTest(MakeDelegate(this,&CollectionsStackTest::Clear),
                "CollectionsStackTest::Clear", "Clear");
            AddTest(MakeDelegate(this,&CollectionsStackTest::Size),
                "CollectionsStackTest::Size", "Size");
            AddTest(MakeDelegate(this,&CollectionsStackTest::Peek),
                "CollectionsStackTest::Peek", "Peek");
        }

        Bool Constructor()
        {
            Stack<UInt32> m_Stack;
            return m_Stack.Size()==0;
        }

        Bool Push()
        {
            Stack<UInt32> m_Stack;
            UInt32 i=5;
            m_Stack.Push(i);
            return m_Stack.Size()==1;
        }

        Bool Pop()
        {
            Stack<UInt32> m_Stack;
            UInt32 i=5;
            m_Stack.Push(i);
            m_Stack.Pop();
            return m_Stack.Size()==0;
        }

        Bool Clear()
        {
            Stack<UInt32> m_Stack;
            UInt32 i=5;
            m_Stack.Push(i);
            m_Stack.Clear();
            return m_Stack.Size()==0;
        }

        Bool Size()
        {
            Stack<UInt32> m_Stack;
            UInt32 i=5;
            m_Stack.Push(i);
            return m_Stack.Size()==1;
        }

        Bool Peek()
        {
            Stack<UInt32> m_Stack;
            UInt32 i=5;
            m_Stack.Push(i);
            return (m_Stack.Peek()==5)&&m_Stack.Size()==1;
        }
};

CollectionsStackTest StackTest;
