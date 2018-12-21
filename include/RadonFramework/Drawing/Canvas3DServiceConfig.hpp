#ifndef RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
#define RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/DataTree.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework::Drawing
{
struct Canvas3DServiceConfig
{
  static void Set(RF_Collect::DataTree::NodeType& TreeNode);
  static RF_Type::Bool Fallback(RF_Collect::DataTree::NodeType& TreeNode,
                                RF_Type::Size& Priority,
                                RF_Type::String& Parameter);
  static RF_Type::String DefaultDriver;
  static RF_Collect::Array<RF_Collect::Pair<RF_Type::Size, RF_Type::String>>
      FallbackDriver;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_CANVAS3DSERVICECONFIG_HPP
