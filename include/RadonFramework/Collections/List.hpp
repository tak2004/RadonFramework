#ifndef RF_COLLECTIONS_LIST_HPP
#define RF_COLLECTIONS_LIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework { namespace Collections {

template <typename T>class List;

template <typename T,class Node,typename Pointer=T*,typename Reference=T&>
class ListIterator
{
public:
    ListIterator();
    ListIterator(const ListIterator &It);
    ListIterator& operator=(const ListIterator &It);
    RF_Type::Bool operator==(const ListIterator &It)const;
    RF_Type::Bool operator!=(const ListIterator &It)const;
    ListIterator& operator++();
    ListIterator operator++(int);
    ListIterator& operator--();
    ListIterator operator--(int);
    ListIterator& operator+=(const RF_Type::UInt32 Step);
    ListIterator& operator-=(const RF_Type::UInt32 Step);
    const ListIterator operator+(const RF_Type::UInt32 Step)const;
    const ListIterator operator-(const RF_Type::UInt32 Step)const;
    operator bool()const;
    Pointer operator->()const;
    Reference operator*()const;
    static RF_Type::UInt32 Distance(ListIterator Start, ListIterator Stop);
protected:
    friend class List<T>;
    ListIterator(Node* node, List<T> *Owner);
    Node* GetNode()const;
    Node *m_Node;
    List<T> *m_Owner;
};

/** @brief This class is a double link list template.
    *
    * The template allow different specialization of types.
    * The class has no virtual methods because it will slow down the calls,
    * if you overload them. The Iterator of List use a Owner variable to
    * determinate, that the iterator belong to a List object. This mean
    * that you can't use a iterator of one List on an other List of the same
    * type. This is more defensive and allow less mistakes.
    * The class use a Node class which consists of prev, next node and value
    * of the element.
    * To get the best performance use the Iterator and run it sequential.
    * If you need random access to the elements then use a Vector class,
    * because this is much faster but need more time for adding new elements.
    */
template <typename T>
class List
{
private:
    class Node
    {
    public:
        Node();
        Node(T &V);
        ~Node();

        void SetNext(Node *N);
        Node* GetNext()const;
        void SetPrev(Node *P);
        Node* GetPrev()const;
        T& Value();
    protected:
        Node *m_Next;
        Node *m_Prev;
        T m_Value;
    };
public:
    typedef ListIterator<T,Node> Iterator;
    typedef ListIterator<T,Node,const T*, const T&> ConstIterator;
    typedef T Type;

    List();
    List(const List& Copy);
    ~List();
    void operator=(const List<T>&rhs);

    RF_Type::Bool AddAfter(const Iterator& It,T &Item);
    RF_Type::Bool AddAfter(const Iterator& It,const T &Item);
    RF_Type::Bool AddBefore(const Iterator& it,T &Item);
    RF_Type::Bool AddBefore(const Iterator& it,const T &Item);
    void AddLast(T &Item);
    void AddLast(const T &Item);
    void AddFirst(T &Item);
    void AddFirst(const T &Item);
    void AddList(const List<T> &L);
    void Insert(const RF_Type::UInt32 Index, T &Item);
    void Insert(const RF_Type::UInt32 Index, const T &Item);
    T& CreateElementAtEnd();
    T& CreateElementAtBegin();
    T& CreateElementAt(const RF_Type::UInt32 Position);

    void Clear();
    RF_Type::Bool Remove(Iterator& It);
    void RemoveLast();
    void RemoveFirst();
    void RemoveAt(RF_Type::UInt32 Index);
    void Swap(List<T>&rhs);

    T& Item(const RF_Type::UInt32 Index);
    const T& Item(const RF_Type::UInt32 Index)const;
    T& operator[](const RF_Type::UInt32 Index);
    const T& operator[](const RF_Type::UInt32 Index)const;
    RF_Type::Bool Find(const Iterator& It)const;
    RF_Type::Bool Find(const T& Item)const;
    T* First()const;
    T* Last()const;
    Iterator Begin()const;
    Iterator End()const;
    ConstIterator ConstBegin()const;
    ConstIterator ConstEnd()const;

    RF_Type::UInt32 Count()const;
private:
    Node *m_First;
    Node *m_Last;
    RF_Type::UInt32 m_Count;
};

template<typename T>
List<T>::Node::Node()
:m_Next(0),
    m_Prev(0)
{
}

template<typename T>
List<T>::Node::Node(T &V)
:m_Next(0)
,m_Prev(0)
,m_Value(V)
{                
}

template<typename T>
List<T>::Node::~Node()
{
}

template<typename T>
void List<T>::Node::SetNext(Node *N)
{
    m_Next=N;
}

template<typename T>
typename List<T>::Node* List<T>::Node::GetNext()const
{
    return m_Next;
}

template<typename T>
void List<T>::Node::SetPrev(Node *N)
{
    m_Prev=N;
}

template<typename T>
typename List<T>::Node* List<T>::Node::GetPrev()const
{
    return m_Prev;
}

template<typename T>
T& List<T>::Node::Value()
{
    return m_Value;
}

//
//
//

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>::ListIterator()
:m_Node(0),
    m_Owner(0)
{
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>::ListIterator(Node *node, List<T> *Owner)
:m_Node(node),
    m_Owner(Owner)
{
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>::ListIterator(const ListIterator &It)
:m_Node(It.m_Node),
    m_Owner(It.m_Owner)
{
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>& ListIterator<T,Node,Pointer,Reference>::operator=(const ListIterator &It)
{
    if (&It!=this)
    {
        m_Node=It.m_Node;
        m_Owner=It.m_Owner;
    }
    return *this;
}

template<typename T,class Node,class Pointer,class Reference>
RF_Type::Bool ListIterator<T,Node,Pointer,Reference>::operator==(const ListIterator &It)const
{
    return m_Node==It.m_Node && m_Owner==It.m_Owner;
}

template<typename T,class Node,class Pointer,class Reference>
RF_Type::Bool ListIterator<T,Node,Pointer,Reference>::operator!=(const ListIterator &It)const
{
    return m_Node!=It.m_Node || m_Owner!=It.m_Owner;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>& ListIterator<T,Node,Pointer,Reference>::operator++()
{
    m_Node=m_Node->GetNext();
    return *this;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference> ListIterator<T,Node,Pointer,Reference>::operator++(int)
{
    ListIterator tmp(m_Node,m_Owner);
    m_Node=m_Node->GetNext();
    return tmp;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>& ListIterator<T,Node,Pointer,Reference>::operator--()
{
    m_Node=m_Node->GetPrev();
    return *this;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference> ListIterator<T,Node,Pointer,Reference>::operator--(int)
{
    ListIterator tmp(m_Node,m_Owner);
    m_Node=m_Node->GetPrev();
    return tmp;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>& ListIterator<T,Node,Pointer,Reference>::operator+=(const RF_Type::UInt32 Step)
{
    for (RF_Type::UInt32 i=0;i<Step;++i)
        if (m_Node->GetNext())
            m_Node=m_Node->GetNext();
        else
            break;
    return *this;
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>& ListIterator<T,Node,Pointer,Reference>::operator-=(const RF_Type::UInt32 Step)
{
    for (RF_Type::UInt32 i=0;i<Step;++i)
        if (m_Node->GetPrev())
            m_Node=m_Node->GetPrev();
        else
            break;
    return *this;
}

template<typename T,class Node,class Pointer,class Reference>
const ListIterator<T,Node,Pointer,Reference> ListIterator<T,Node,Pointer,Reference>::operator+(const RF_Type::UInt32 Step)const
{
    Node *n=m_Node;
    for (RF_Type::UInt32 i=0;i<Step;++i)
        if (n->GetNext())
            n=n->GetNext();
        else
            break;
    return ListIterator(n,m_Owner);
}

template<typename T,class Node,class Pointer,class Reference>
const ListIterator<T,Node,Pointer,Reference> ListIterator<T,Node,Pointer,Reference>::operator-(const RF_Type::UInt32 Step)const
{
    Node *n=m_Node;
    for (RF_Type::UInt32 i=0;i<Step;++i)
        if (n->GetPrev())
            n=n->GetPrev();
        else
            break;
    return ListIterator(n,m_Owner);
}

template<typename T,class Node,class Pointer,class Reference>
ListIterator<T,Node,Pointer,Reference>::operator bool()const
{
    return 0!=m_Node;
}

template<typename T,class Node,class Pointer,class Reference>
Pointer ListIterator<T,Node,Pointer,Reference>::operator->()const
{
    Assert(m_Node,"Invalid use of null pointer.");
    return &m_Node->Value();
}

template<typename T,class Node,class Pointer,class Reference>
Reference ListIterator<T,Node,Pointer,Reference>::operator*()const
{
    Assert(m_Node,"Invalid use of null pointer.");
    return m_Node->Value();
}

template<typename T,class Node,class Pointer,class Reference>
RF_Type::UInt32 ListIterator<T,Node,Pointer,Reference>::Distance(
    ListIterator Start, ListIterator Stop)
{
    return (ptrdiff_t)(Stop.m_Element-Start.m_Element);
}

template<typename T,class Node,class Pointer,class Reference>
Node* ListIterator<T,Node,Pointer,Reference>::GetNode()const
{
    return m_Node;
}

//
//
//

template<typename T>
List<T>::List()
:m_First(0),
    m_Last(0),
    m_Count(0)
{
}

template<typename T>
List<T>::List(const List<T>& Copy)
:m_First(0),
    m_Last(0),
    m_Count(0)
{
    AddList(Copy);
}

template<typename T>
List<T>::~List()
{
    Clear();
}

template<typename T>
void List<T>::operator=(const List<T> &rhs)
{
    Clear();
    AddList(rhs);
}

template<typename T>
void List<T>::Clear()
{
    while(m_Last)
        RemoveLast();
}

template<typename T>
void List<T>::Swap(List<T>&rhs)
{
    Node* first=m_First;
    Node* last=m_Last;
    RF_Type::UInt32 size=m_Count;
    m_First=rhs.m_First;
    m_Last=rhs.m_Last;
    m_Count=rhs.m_Count;
    rhs.m_First=first;
    rhs.m_Last=last;
    rhs.m_Count=size;
}

template<typename T>
RF_Type::Bool List<T>::AddBefore(const Iterator& It, T &Item)
{
    if (It==End())
    {
        Node* n=new Node(Item);
        m_First=n;
        m_Last=n;
        m_Count+=1;
        return true;
    }
    else
        if (It.m_Owner!=this)
            return false;

    Node* n=new Node(Item);
    if (It.GetNode()==m_First)
        m_First=n;
    if (It.GetNode()->GetPrev()!=0)
        It.GetNode()->GetPrev()->SetNext(n);

    n->SetPrev(It.GetNode()->GetPrev());
    It.GetNode()->SetPrev(n);
    n->SetNext(It.GetNode());
    m_Count+=1;
    return true;
}

template<typename T>
RF_Type::Bool List<T>::AddBefore(const Iterator& It, const T &Item)
{
    T& item=const_cast<T&>(Item);
    return AddBefore(It,item);
}

template<typename T>
RF_Type::Bool List<T>::AddAfter(const Iterator& It,T &Item)
{
    if (It==End())
    {
        Node* n=new Node(Item);
        m_First=n;
        m_Last=n;
        m_Count+=1;
        return true;
    }
    else
        if (It.m_Owner!=this)
            return false;

    Node* n=new Node(Item);
    if (It.GetNode()==m_Last)
        m_Last=n;
    if (It.GetNode()->GetNext()!=0)
        It.GetNode()->GetNext()->SetPrev(n);

    n->SetNext(It.GetNode()->GetNext());
    It.GetNode()->SetNext(n);
    n->SetPrev(It.GetNode());
    m_Count+=1;
    return true;
}

template<typename T>
RF_Type::Bool List<T>::AddAfter(const Iterator& It,const T &Item)
{
    T& item=const_cast<T&>(Item);
    return AddAfter(It,item);
}

template<typename T>
void List<T>::AddFirst(T &Item)
{
    AddBefore(Begin(), Item);
}

template<typename T>
void List<T>::AddFirst(const T &Item)
{
    AddBefore(Begin(), Item);
}

template<typename T>
void List<T>::AddLast(T &Item)
{
    AddAfter(Iterator(m_Last,this),Item);
}

template<typename T>
void List<T>::AddLast(const T &Item)
{
    AddAfter(Iterator(m_Last,this),Item);
}

template<typename T>
void List<T>::AddList(const List<T> &L)
{
    Iterator it;
    for (it=L.Begin(); it!=L.End(); ++it)
        AddLast(*it);
}

template<typename T>
void List<T>::Insert(RF_Type::UInt32 Index, T &Item)
{
    Assert(m_Count>=Index,"Out of bound.");
    if (m_Count==Index)
        AddLast(Item);
    else
    {
        RF_Type::UInt32 i=0;
        for (Iterator it=Begin(); it!=End(); ++it)
        {
            if (Index==i)
            {
                AddBefore(it,Item);
                break;
            }
            ++i;
        }
    }
}

template<typename T>
void List<T>::Insert(RF_Type::UInt32 Index, const T &Item)
{
    T& item=const_cast<T&>(Item);
    Insert(Index,item);
}

template<typename T>
T& List<T>::CreateElementAtEnd()
{
    Node* n=new Node;
    n->SetPrev(m_Last);
    if (m_Last)
        m_Last->SetNext(n);
    m_Last=n;
    m_Count+=1;
    if (m_First==0)
        m_First=m_Last;
    return m_Last->Value();
}

template<typename T>
T& List<T>::CreateElementAtBegin()
{
    Node* n=new Node;
    n->SetNext(m_First);
    if (m_First)
        m_First->SetPrev(n);
    m_First=n;
    m_Count+=1;
    if (m_Last==0)
        m_Last=m_First;
    return m_First->Value();
}

template<typename T>
T& List<T>::CreateElementAt(const RF_Type::UInt32 Position)
{
    Assert(m_Count>Position,"Out of bound.");
    if (m_Count==Position)
        return CreateElementAtEnd();
    if (Position==0)
        return CreateElementAtBegin();

    RF_Type::UInt32 i=0;
    Node *it=m_First;
    while (i<Position)
    {
        ++i;
        it=it->GetNext();
    }
    Node* n=new Node;
    n->SetNext(it);
    n->SetPrev(it->GetPrev());
    it->GetPrev()->SetNext(n);
    it->GetNext()->SetPrev(n);
    return n->Value();
}

template<typename T>
RF_Type::Bool List<T>::Remove(Iterator& It)
{
    if (It==End())
        return false;
    if (!Find(It))
        return false;

    Node *n=It.GetNode();
    ++It;
    if(n->GetPrev())
        n->GetPrev()->SetNext(n->GetNext());
    if(n->GetNext())
        n->GetNext()->SetPrev(n->GetPrev());
    if(n==m_First)
        m_First=n->GetNext();
    if (n==m_Last)
        m_Last=n->GetPrev();
    n->SetNext(0);
    n->SetPrev(0);
    delete n;
    m_Count-=1;
    return true;
}

template<typename T>
void List<T>::RemoveFirst()
{
    if (m_First)
    {
        Iterator it=Begin();
        Remove(it);
    }
}

template<typename T>
void List<T>::RemoveLast()
{                
    if (m_Last)
    {
        Iterator it(m_Last,this);
        Remove(it);
    }
}

template<typename T>
void List<T>::RemoveAt(RF_Type::UInt32 Index)
{
    Assert(Index<m_Count,"Out of bound.");

    RF_Type::UInt32 i=0;
    for (Iterator it=Begin(); it!=End(); ++it)
    {
        if (Index==i)
        {
            Remove(it);
            break;
        }
        ++i;
    }
}

template<typename T>
T& List<T>::Item(const RF_Type::UInt32 Index)
{
    Assert(Index<m_Count,"Out of bound.");

    RF_Type::UInt32 i=0;
    Iterator it=Begin();
    for (;it!=End();++it)
    {
        if (i==Index)
            break;
        i++;
    }
    return *it;
}

template<typename T>
const T& List<T>::Item(const RF_Type::UInt32 Index)const
{
    Assert(Index<m_Count, "Out of bound");

    RF_Type::UInt32 i=0;
    Iterator it=Begin();
    for (;it!=End();++it)
    {
        if (i==Index)
            break;
        i++;
    }
    return *it;
}

template <typename T>
T& List<T>::operator[]( const RF_Type::UInt32 Index )
{
    return Item(Index);
}

template <typename T>
const T& List<T>::operator[]( const RF_Type::UInt32 Index ) const
{
    return Item(Index);
}

template<typename T>
RF_Type::Bool List<T>::Find(const Iterator& It)const
{
    for (Iterator i=Begin(); i!=End(); ++i)
        if (i==It)
            return true;
    return false;
}

template<typename T>
RF_Type::Bool List<T>::Find(const T& Item)const
{
    for (Iterator i=Begin(); i!=End(); ++i)
        if (*i==Item)
            return true;
    return false;
}

template<typename T>
T* List<T>::First()const
{
    if (m_Count)
        return &m_First->Value();
    return 0;
}

template<typename T>
T* List<T>::Last()const
{
    if (m_Count)
        return &m_Last->Value();
    return 0;
}

template<typename T>
typename List<T>::Iterator List<T>::End()const
{
    return Iterator(0,(List<T>*)this);
}

template<typename T>
typename List<T>::Iterator List<T>::Begin()const
{
    return Iterator(m_First,(List<T>*)this);
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstEnd()const
{
    return ConstIterator(0,(List<T>*)this);
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstBegin()const
{
    return ConstIterator(m_First,(List<T>*)this);
}

template<typename T>
RF_Type::UInt32 List<T>::Count()const
{
    return m_Count;
}
    
} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_LIST_HPP
