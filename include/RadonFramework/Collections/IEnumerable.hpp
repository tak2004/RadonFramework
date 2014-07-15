#ifndef RF_COLLECTIONS_GENERIC_IENUMERABLE_HPP
#define RF_COLLECTIONS_GENERIC_IENUMERABLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/IEnumerator.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework { namespace Collections {

template<typename T>
class IEnumerable
{
public:
    /// Returns an enumerator that iterates through the collection.
    virtual RF_Mem::AutoPointer<IEnumerator<T> > GetEnumerator()=0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_GENERIC_IENUMERABLE_HPP