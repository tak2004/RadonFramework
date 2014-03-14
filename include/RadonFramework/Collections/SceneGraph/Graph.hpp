#ifndef RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP
#define RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Collections
    {
        namespace SceneGraph
        {
            class Graph
            {
                private:
                    AutoPointer<Node> root;
                    AutoPointer<Scene> data;
            };
        }
    }
}

#endif // RF_COLLECTIONS_SCENEGRAPH_GRAPH_HPP