#ifndef RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP
#define RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/SceneGraph/DataTraits.hpp>
#include <RadonFramework/Net/FixedLengthString.hpp>

namespace RadonFramework { namespace Collections { namespace SceneGraph {

struct NodeItem
{
    DataTraits<Node>::IDType ID;
    RF_Net::FixedLengthString<RF_Type::UInt8, 256> Name;
    DataTraits<Node>::IDType Parent;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP