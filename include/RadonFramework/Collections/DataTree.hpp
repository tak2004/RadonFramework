#ifndef RF_COLLECTIONS_DATATREE_HPP
#define RF_COLLECTIONS_DATATREE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Collections/Tree.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework { namespace Collections {

typedef Tree<Pair<RF_Type::String, RF_Type::String> > DataTree;

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_DATATREE_HPP
