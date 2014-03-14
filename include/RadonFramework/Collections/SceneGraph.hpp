#ifndef RF_COLLECTIONS_SCENEGRAPH_HPP
#define RF_COLLECTIONS_SCENEGRAPH_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/HashMap.hpp>
#include <RadonFramework/Collections/Generic/Array.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        template<class NodePolicies>
        class SceneGraph
        {
            public:
                class Node:public NodePolicies
                {
                    public:

                    protected:
                        Array<Node*> m_Neighbors;
                };
            protected:
                HashMap<const char*,Node> m_Nodes;
                Node* m_Root;
        };
    }
}

#endif // RF_COLLECTIONS_SCENEGRAPH_HPP