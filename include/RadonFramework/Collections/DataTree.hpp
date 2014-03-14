#ifndef RF_COLLECTIONS_DATATREE_HPP
#define RF_COLLECTIONS_DATATREE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Collections/Tree.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework
{
	namespace Collections
	{
		typedef Tree<Pair<RFTYPE::String, RFTYPE::String> > DataTree;
	}
}

#endif // RF_COLLECTIONS_DATATREE_HPP
