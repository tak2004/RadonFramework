#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/SceneGraph/Node.hpp"
#include "RadonFramework/Collections/SceneGraph/NodeItem.hpp"
#include "RadonFramework/Collections/SceneGraph/Component.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Collections;
using namespace RadonFramework::Collections::SceneGraph;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Idioms;
using namespace RadonFramework::Core::Types;

template<class T>
struct PImpl<T>::Data
{
    Data()
    : m_Data(new NodeItem)
    {
        m_Data->ID = 0;
        m_Data->Name = "Root";
        m_Data->Parent = 0;
    }

    ~Data()
    {
    }

    // internal data
    AutoPointer<NodeItem> m_Data;

    // runtime data
    List<AutoPointer<Component> > m_Components;
    List<Node*> m_Childs;
    Node* m_Parent;
};

Node::Node()
{
}

Node::Node(AutoPointer<NodeItem> nodeData)
{
    m_PImpl->m_Data = nodeData;
}

Node::~Node()
{
}

void Node::LoadComponents(AutoPointerArray<Component> Components)
{
//    (*this)->m_Components.Swap(Components);
}

Node::IDType Node::ID()const
{
    return m_PImpl->m_Data->ID;
}

Component* Node::AddComponent(AutoPointer<Component> Component)
{
    ::Component* result = Component.Get();
    m_PImpl->m_Components.AddLast(Component);
    return result;
}

Bool Node::SetParent(Node& newParent)
{
    Bool result = false;
    if (this != &newParent && m_PImpl->m_Parent)
    {        
        for (List<Node*>::Iterator it = m_PImpl->m_Childs.Begin(); it != m_PImpl->m_Childs.End(); ++it)
        {
            if (*it == this)
            {
                m_PImpl->m_Childs.Remove(it);
                break;
            }
        }

        m_PImpl->m_Parent = &newParent;
        newParent.m_PImpl->m_Childs.AddLast(this);
        m_PImpl->m_Data->Parent = m_PImpl->m_Parent->ID();
        result = true;
    }
    return result;
}