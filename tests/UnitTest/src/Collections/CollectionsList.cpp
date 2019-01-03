#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

class CollectionsListTest:public RadonFramework::Diagnostics::Test::UnitTest::TestSuite
{
public:
    CollectionsListTest()
    :TestSuite("Collections::List-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&CollectionsListTest::Constructor),
            "CollectionsListTest::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::FindFail),
            "CollectionsListTest::FindFail"_rfs, "FindFail"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::AddAfter),
            "CollectionsListTest::AddAfter"_rfs, "AddAfter"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::AddBefore),
            "CollectionsListTest::AddBefore"_rfs, "AddBefore"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::AddLast),
            "CollectionsListTest::AddLast"_rfs, "AddLast"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::AddFirst),
            "CollectionsListTest::AddFirst"_rfs, "AddFirst"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::AddList),
            "CollectionsListTest::AddList"_rfs, "AddList"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::Item),
            "CollectionsListTest::Item"_rfs, "Item"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::Insert),
            "CollectionsListTest::Insert"_rfs, "Insert"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::FindMatch),
            "CollectionsListTest::FindMatch"_rfs, "FindMatch"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::ClearList),
            "CollectionsListTest::ClearList"_rfs, "ClearList"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::RemoveIterator),
            "CollectionsListTest::RemoveIterator"_rfs, "RemoveIterator"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::RemoveAt),
            "CollectionsListTest::RemoveAt"_rfs, "RemoveAt"_rfs);
        AddTest(MakeDelegate(this,&CollectionsListTest::CheckListCount),
            "CollectionsListTest::CheckListCount"_rfs, "CheckListCount"_rfs);
    }

    RadonFramework::Core::Types::Bool Constructor()
    {
        List<UInt32> m_List;
        return m_List.First()==0 && m_List.Last()==0 && (m_List.Begin()==m_List.End() && m_List.Count()==0);
    }

    RadonFramework::Core::Types::Bool FindFail()
    {
        List<UInt32> m_List;
        return !m_List.Find(m_List.End());
    }

    RadonFramework::Core::Types::Bool AddAfter()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        return m_List.AddAfter(m_List.Begin(),i) && m_List.Count()==1;
    }

    RadonFramework::Core::Types::Bool AddBefore()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        return (m_List.AddBefore(m_List.Begin(),i)) && (m_List.Count()==1);
    }

    RadonFramework::Core::Types::Bool AddLast()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddLast(i);
        return (m_List.Count()==1);
    }

    RadonFramework::Core::Types::Bool AddFirst()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddFirst(i);
        return (m_List.Count()==1);
    }

    RadonFramework::Core::Types::Bool AddList()
    {
        List<UInt32> m_List;
        List<UInt32> l;
        UInt32 i=5;
        l.AddLast(i);
        l.AddLast(i);
        m_List.AddList(l);
        return (m_List.Count()==2);
    }

    RadonFramework::Core::Types::Bool Item()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddLast(i);
        return (m_List.Item(0)==5);
    }

    RadonFramework::Core::Types::Bool Insert()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.Insert(0,i);
        i=3;
        m_List.Insert(1,i);
        i=6;
        m_List.Insert(1,i);
        return (m_List.Count()==3) && (m_List.Item(0)==5) && 
                (m_List.Item(1)==6) &&  (m_List.Item(2)==3);
    }

    RadonFramework::Core::Types::Bool FindMatch()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddLast(i);
        return (m_List.Find(m_List.Begin()));
    }

    RadonFramework::Core::Types::Bool ClearList()
    {
        List<UInt32> m_List;
        //empty list
        m_List.Clear();
        RadonFramework::Core::Types::Bool res=(m_List.Count()==0);

        //filled list
        UInt32 i=5;
        m_List.AddLast(i);
        res=res && (m_List.Count()==1);
        m_List.Clear();
        return res && (m_List.Count()==0);
    }

    RadonFramework::Core::Types::Bool RemoveIterator()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddLast(i);
        List<UInt32>::Iterator beg=m_List.Begin();
        return (m_List.Remove(beg)) && (!m_List.Remove(beg));
    }

    RadonFramework::Core::Types::Bool RemoveAt()
    {
        List<UInt32> m_List;
        UInt32 i=5;
        m_List.AddLast(i);
        m_List.RemoveAt(0);
        return (m_List.Count()==0);
    }

    RadonFramework::Core::Types::Bool CheckListCount()
    {
        List<UInt32> m_List;
        RadonFramework::Core::Types::Bool res=(m_List.Count()==0);
        UInt32 i=5;
        m_List.AddLast(i);
        return (m_List.Count()==1) && res;
    }
};

CollectionsListTest ListTest;
