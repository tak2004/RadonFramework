#ifndef RF_COLLECTIONS_PAIR_HPP
#define RF_COLLECTIONS_PAIR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Collections
{
/**
 * This class contains two member which are related as a pair.
 */
template <class FIRST, class SECOND>
class Pair
{
public:
  Pair();

  Pair(const FIRST& FirstValue, const SECOND& SecondValue);

  FIRST First;
  SECOND Second;
};

template <class FIRST, class SECOND>
Pair<FIRST, SECOND>::Pair()
{
}

template <class FIRST, class SECOND>
Pair<FIRST, SECOND>::Pair(const FIRST& FirstValue, const SECOND& SecondValue)
: First(FirstValue), Second(SecondValue)
{
}

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif  // RF_COLLECTIONS_PAIR_HPP