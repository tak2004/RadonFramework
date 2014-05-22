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
            Node(Memory::AutoPointer<NodeItem> nodeData);
            ~Node();

            typedef DataTraits<Node>::IDType IDType;

            template<class T>
            T* AddComponent();

            Component* AddComponent(Memory::AutoPointer<Component> Component);

            void LoadComponents(Memory::AutoPointerArray<Component> Components);

            IDType ID()const;

            RFTYPE::Bool SetParent(Node& newParent);
        private:
            Core::Idioms::PImpl<Node> m_PImpl;
    };

    template<class T>
    T* Node::AddComponent()
    {
        return reinterpret_cast<T*>(AddComponent(Memory::AutoPointer<Component>(reinterpret_cast<Component*>(new T()))));
    }
} } }
#endif // RF_COLLECTIONS_SCENEGRAPH_NODE_HPP