#ifndef RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP
#define RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/SceneGraph/DataTraits.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        namespace SceneGraph
        {
            class Node;
            class NodeItem;

            class Scene
            {
            public:
                Scene();
                virtual ~Scene();

                RFTYPE::Float64 Delta()const;
                void SetDelta(RFTYPE::Float64 newDelta);

                void RemoveNode(DataTraits<Node>::IDType ID);
                Node& CreateNode();
                Node* LoadNode(Memory::AutoPointer<NodeItem> nodeData);
                Node* FindNode(DataTraits<Node>::IDType ID);
            private:
                Core::Idioms::PImpl<Scene> m_PImpl;
            };
        }
    }
}

#endif // RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP