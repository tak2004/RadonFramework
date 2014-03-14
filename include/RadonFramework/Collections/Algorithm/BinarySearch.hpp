#ifndef RF_COLLECTIONS_ALGORITHM_BINARYSEARCH_HPP
#define RF_ALGORITHM_BINARYSEARCH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Collections/ArrayEnumerator.hpp>

namespace RadonFramework { namespace Collections { namespace Algorithm {
    /**
     * \brief Searches an entire one-dimensional sorted Array 
     *        for a value using the specified Comparer function.
     *
     * \param Index The starting index of the range to search.
     * \param Length The length of the range to search.
     * \param Value The value which will searched.
     * \param Comparer The callback which will be called for each
     *                 element of the array.
     */
    template<class T>
    RFTYPE::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value,
                                const Delegate2<T&,T&,RFTYPE::Int32> Comparer);

    /**
     * \brief Searches an entire one-dimensional sorted Array 
     *        for a value using the specified Comparer function.
     *
     * \param Index The starting index of the range to search.
     * \param Length The length of the range to search.
     * \param Value The value which will searched.
     */
    template<class T>
    RFTYPE::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value);

    template<class T>
    RFTYPE::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value )
    {
        Memory::AutoPointer<ArrayEnumerator<T> > upperBorderIterator=Range.Begin();
        Memory::AutoPointer<ArrayEnumerator<T> > lowerBorderIterator=Range.End();
        Memory::AutoPointer<ArrayEnumerator<T> > current=upperBorderIterator;
            
        while(current->MoveTo((static_cast<RFTYPE::MemoryRange>(upperBorderIterator->Current()-lowerBorderIterator->Current())>>1)+
                               static_cast<RFTYPE::MemoryRange>(lowerBorderIterator->Current()-Range.Current()) &&
                               *current->Current()!=Value))
        {
            if (*current->Current()<Value)
                lowerBorderIterator=current;
            else
                upperBorderIterator=current;
        }

        return static_cast<RFTYPE::MemoryRange>(current->Current()-Range.Current());
    }

    template<class T>
    RFTYPE::Size BinarySearch(ArrayEnumerator<T>& Range, const T& Value,
                                const Delegate2<T&, T&, RFTYPE::Int32> Comparer)
    {
        Memory::AutoPointer<ArrayEnumerator<T> > upperBorderIterator=Range.Begin();
        Memory::AutoPointer<ArrayEnumerator<T> > lowerBorderIterator=Range.End();
        Memory::AutoPointer<ArrayEnumerator<T> > current=upperBorderIterator;

        while(current.MoveTo((static_cast<RFTYPE::MemoryRange>(upperBorderIterator.Current()-lowerBorderIterator.Current())>>1)+
            static_cast<RFTYPE::MemoryRange>(lowerBorderIterator.Current()-Range.Current())) &&
            Comparer(*current.Current(),Value)!=0)
        {
            if (*current.Current()<Value)
                lowerBorderIterator=current;
            else
                upperBorderIterator=current;
        }

        return static_cast<RFTYPE::MemoryRange>(current.Current()-Range.Current());
    }

} } }

#endif // RF_ALGORITHM_BINARYSEARCH_HPP