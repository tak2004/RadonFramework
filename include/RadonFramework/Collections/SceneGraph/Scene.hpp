#ifndef RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP
#define RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/SceneGraph/DataTraits.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework { namespace Collections { namespace SceneGraph {
            
class Node;
class NodeItem;

class Scene
{
public:
    Scene();
    ~Scene();

    RF_Type::Float64 Delta()const;
    void SetDelta(RF_Type::Float64 newDelta);

    void RemoveNode(DataTraits<Node>::IDType ID);
    Node& CreateNode();
    Node* LoadNode(RF_Mem::AutoPointer<NodeItem> nodeData);
    Node* FindNode(DataTraits<Node>::IDType ID);
private:
    RF_Idiom::PImpl<Scene> m_PImpl;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_SCENE_HPP