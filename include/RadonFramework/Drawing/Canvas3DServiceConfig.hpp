#ifndef RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
#define RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/DataTree.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        struct Canvas3DServiceConfig
        {
            static void Set(Collections::DataTree::NodeType& TreeNode);
            static RFTYPE::Bool Fallback(Collections::DataTree::NodeType& TreeNode,
                                       RFTYPE::Size& Priority, 
                                       RFTYPE::String& Parameter);
            static RFTYPE::String DefaultDriver;
            static Collections::Array<Collections::Pair<
                RFTYPE::Size,RFTYPE::String> > FallbackDriver;
        };
    }
}

#endif // RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
