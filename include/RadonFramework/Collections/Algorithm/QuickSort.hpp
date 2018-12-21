#ifndef RF_COLLECTIONS_ALGORITHM_QUICKSORT_HPP
#define RF_COLLECTIONS_ALGORITHM_QUICKSORT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Collections::Algorithm
{
template <class C, typename FUNCTION>
void QuickSort(typename C::Iterator Begin,
               typename C::Iterator End,
               FUNCTION Function)
{
  auto distance = C::Iterator::Distance(Begin, End);
  if(distance > 1)
  {
    auto pivot = Begin;
    pivot += distance >> 1;

    auto left = Begin;
    auto right = End;
    --right;

    typename C::Type val = *pivot;
    typename C::Type tmp = *pivot;
    *pivot = *right;
    *right = tmp;

    auto pivot_position = left;
    while(left != right)
    {
      if(Function(*left, val) > 0)
      {
        tmp = *left;
        *left = *pivot_position;
        *pivot_position = tmp;
        ++pivot_position;
      }
      ++left;
    }

    tmp = *pivot_position;
    *pivot_position = *right;
    *right = tmp;

    right = pivot_position;
    ++right;

    QuickSort<C, FUNCTION>(Begin, pivot_position, Function);
    QuickSort<C, FUNCTION>(right, End, Function);
  }
}

template <class C, typename FUNCTION>
void QuickSort(C& Enumerable, FUNCTION Function)
{
  QuickSort<C, FUNCTION>(Enumerable.Begin(), Enumerable.End(), Function);
}

}  // namespace RadonFramework::Collections::Algorithm

#ifndef RF_SHORTHAND_NAMESPACE_ALGO
#define RF_SHORTHAND_NAMESPACE_ALGO
namespace RF_Algo = RadonFramework::Collections::Algorithm;
#endif

#endif  // RF_COLLECTIONS_ALGORITHM_QUICKSORT_HPP