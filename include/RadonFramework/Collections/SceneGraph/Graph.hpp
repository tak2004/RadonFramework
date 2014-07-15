#ifndef RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP
#define RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework { namespace Collections { namespace SceneGraph {

class Node;
class Scene;

class Graph
{
private:
    RF_Mem::AutoPointer<Node> root;
    RF_Mem::AutoPointer<Scene> data;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP