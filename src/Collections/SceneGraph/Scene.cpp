#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/SceneGraph/Scene.hpp"
#include "RadonFramework/Collections/SceneGraph/Node.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/SceneGraph/NodeItem.hpp"

using namespace RadonFramework::Collections::SceneGraph;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Idioms;

template<>
struct PImpl<Scene>::Data
{
    Data()
    : m_Root(0)
    {
    }
    
    ~Data()
    {
    }

    List<AutoPointer<Node> > m_Nodes;
    AutoPointer<Node> m_Root;
};

Scene::Scene()
{
}

Scene::~Scene()
{
}

Float64 Scene::Delta()const
{
    return 0;
}

void Scene::SetDelta(Float64 newDelta)
{
}

void Scene::RemoveNode(DataTraits<Node>::IDType ID)
{
}

Node& Scene::CreateNode()
{
    if (!m_PImpl->m_Root)
        m_PImpl->m_Root = AutoPointer<Node>(new Node());

    AutoPointer<NodeItem> node(new NodeItem);
    node->ID = m_PImpl->m_Nodes.Size()+1;
    node->Name = String("Node") + node->ID;
    AutoPointer<Node> n(new Node(node));
    n->SetParent(*m_PImpl->m_Root);

    Node* result = n.Get();
    m_PImpl->m_Nodes.AddLast(n);
    return *result;
    
}

Node* Scene::LoadNode(AutoPointer<NodeItem> nodeData)
{
    if (!m_PImpl->m_Root)
        m_PImpl->m_Root = AutoPointer<Node>(new Node());

    Node* result = 0;
    Node* parent = FindNode(nodeData->Parent);
    if (parent && nodeData->ID != 0)
    {
        AutoPointer<Node> n(new Node(nodeData));
        result = n.Get();
        n->SetParent(*parent);
        m_PImpl->m_Nodes.AddLast(n);
    }
    return result;
}

Node* Scene::FindNode(DataTraits<Node>::IDType ID)
{
    Node* result = 0;
    for (List<AutoPointer<Node> >::Iterator it = m_PImpl->m_Nodes.Begin(); it != m_PImpl->m_Nodes.End(); ++it)
        if ((*it)->ID() == ID)
        {
            result = (*it).Get();
            break;
        }
    return result;
}