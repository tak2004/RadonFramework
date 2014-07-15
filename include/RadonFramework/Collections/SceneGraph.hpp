#ifndef RF_COLLECTIONS_SCENEGRAPH_HPP
#define RF_COLLECTIONS_SCENEGRAPH_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/HashMap.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Collections { namespace SceneGraph {

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

} } }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_HPP