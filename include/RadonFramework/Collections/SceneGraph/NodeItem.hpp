#ifndef RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP
#define RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/SceneGraph/DataTraits.hpp>
#include <RadonFramework/Net/FixedLengthString.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        namespace SceneGraph
        {
            struct NodeItem
            {
                DataTraits<Node>::IDType ID;
                Net::FixedLengthString<RFTYPE::UInt8, 256> Name;
                DataTraits<Node>::IDType Parent;
            };
        }
    }
}

#endif // RF_COLLECTIONS_SCENEGRAPH_NODEITEM_HPP