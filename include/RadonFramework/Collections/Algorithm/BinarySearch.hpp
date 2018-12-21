//#ifndef RF_COLLECTIONS_ALGORITHM_BINARYSEARCH_HPP
//#define RF_COLLECTIONS_ALGORITHM_BINARYSEARCH_HPP
//#if _MSC_VER > 1000
//#pragma once
//#endif
//
//#include <RadonFramework/Core/Pattern/Delegate.hpp>
//#include <RadonFramework/Core/Types/Int32.hpp>
//#include <RadonFramework/Core/Types/MemoryRange.hpp>
//#include <RadonFramework/Core/Types/Size.hpp>
//#include <RadonFramework/Memory/AutoPointer.hpp>
//
//namespace RadonFramework::Collections::Algorithm
//{
///**
// * \brief Searches an entire one-dimensional sorted Array
// *        for a value using the specified Comparer function.
// *
// * \param Index The starting index of the range to search.
// * \param Length The length of the range to search.
// * \param Value The value which will searched.
// * \param Comparer The callback which will be called for each
// *                 element of the array.
// */
//template <class T>
//RF_Type::Size BinarySearch(ArrayEnumerator<T>& Range,
//                           const T& Value,
//                           const Delegate2<RF_Type::Int32(T&, T&)> Comparer);
//
///**
// * \brief Searches an entire one-dimensional sorted Array
// *        for a value using the specified Comparer function.
// *
// * \param Index The starting index of the range to search.
// * \param Length The length of the range to search.
// * \param Value The value which will searched.
// */
//template <class T>
//RF_Type::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value);
//
//template <class T>
//RF_Type::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value)
//{
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> upperBorderIterator = Range.Begin();
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> lowerBorderIterator = Range.End();
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> current = upperBorderIterator;
//
//  while(current->MoveTo(
//      (static_cast<RF_Type::MemoryRange>(upperBorderIterator->Current() -
//                                         lowerBorderIterator->Current()) >>
//       1) +
//          static_cast<RF_Type::MemoryRange>(lowerBorderIterator->Current() -
//                                            Range.Current()) &&
//      *current->Current() != Value))
//  {
//    if(*current->Current() < Value)
//      lowerBorderIterator = current;
//    else
//      upperBorderIterator = current;
//  }
//
//  return static_cast<RF_Type::MemoryRange>(current->Current() -
//                                           Range.Current());
//}
//
//template <class T>
//RF_Type::Size BinarySearch(ArrayEnumerator<T>& Range,
//                           const T& Value,
//                           const Delegate2<RF_Type::Int32(T&, T&)> Comparer)
//{
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> upperBorderIterator = Range.Begin();
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> lowerBorderIterator = Range.End();
//  RF_Mem::AutoPointer<ArrayEnumerator<T>> current = upperBorderIterator;
//
//  while(current.MoveTo(
//            (static_cast<RF_Type::MemoryRange>(upperBorderIterator.Current() -
//                                               lowerBorderIterator.Current()) >>
//             1) +
//            static_cast<RF_Type::MemoryRange>(lowerBorderIterator.Current() -
//                                              Range.Current())) &&
//        Comparer(*current.Current(), Value) != 0)
//  {
//    if(*current.Current() < Value)
//      lowerBorderIterator = current;
//    else
//      upperBorderIterator = current;
//  }
//
//  return static_cast<RF_Type::MemoryRange>(current.Current() - Range.Current());
//}
//
//}  // namespace RadonFramework::Collections::Algorithm
//
//#ifndef RF_SHORTHAND_NAMESPACE_ALGO
//#define RF_SHORTHAND_NAMESPACE_ALGO
//namespace RF_Algo = RadonFramework::Collections::Algorithm;
//#endif
//
//#endif  // RF_COLLECTIONS_ALGORITHM_BINARYSEARCH_HPP