#ifndef RF_COLLECTIONS_SCENEGRAPH_NODE_HPP
#define RF_COLLECTIONS_SCENEGRAPH_NODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/SceneGraph/DataTraits.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework { namespace Collections { namespace SceneGraph {

class Component;
class NodeItem;

class Node
{
public:
    Node();
    Node(RF_Mem::AutoPointer<NodeItem> nodeData);
    ~Node();

    typedef DataTraits<Node>::IDType IDType;

    template<class T>
    T* AddComponent();

    Component* AddComponent(RF_Mem::AutoPointer<Component> Component);

    void LoadComponents(RF_Mem::AutoPointerArray<Component> Components);

    IDType ID()const;

    RF_Type::Bool SetParent(Node& newParent);
private:
    RF_Idiom::PImpl<Node> m_PImpl;
};

template<class T>
T* Node::AddComponent()
{
    return reinterpret_cast<T*>(AddComponent(RF_Mem::AutoPointer<Component>(reinterpret_cast<Component*>(new T()))));
}

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_NODE_HPP