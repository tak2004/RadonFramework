#ifndef RF_COLLECTIONS_ARRAY_HPP
#define RF_COLLECTIONS_ARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <type_traits>

#include <RadonFramework/Threading/ISynchronize.hpp>

#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Threading/Policies/NoSynchronization.hpp>
#include <RadonFramework/Collections/ArrayEnumerator.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
#include <RadonFramework/Collections/ArrayEnumeratorType.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        /** 
            * This class allow to store many elements of the same type.
            * The length of the array will be set on the constructor and
            * could only be changed by assign a complete new array object.
            * This allow to reduce the processing time at runtime but increase the
            * memory usage. Use this class if you have information which
            * wouldn't change in the count of elements anymore.
            *
            * \tparam T Set the type of the container elements.
            * \tparam SP Set the type of synchronization which will be used to
            *            make the class thread safe.
            * \tparam MA Set the memory allocation policy which will be used
            *            to allocate and free memory.
            * \tparam MO Set the memory operation policy which will be used to
            *            do copy, move, compare and other operations on the
            *            allocated memory.
            */
        template<typename T, 
                    typename SP=Threading::Policies::NoSynchronization, 
                    typename MA=Core::Policies::CPPAllocator,
                    typename MO=Core::Policies::CMemoryOperation>
        class Array
        {
            template <typename,typename,typename,typename>
            friend class Array;
            public:
                typedef T Type;
                typedef Enumerator<T, ArrayEnumeratorType> EnumeratorType;
                
                // Constructor and destructor
                    
                /** 
                    * Create an instance of the Array class.
                    */
                Array();

                /** 
                    * \brief Create a copy of a given Array.
                    *
                    * The copy constructor make a deep copy.
                    *
                    * \param Copy The object from which the copy will be done.
                    */
                Array(const Array<T,SP,MA,MO>& Copy);

                /**
                    * Create a 1D Array.
                    *
                    * \param Length1 The size of the Array to create.
                    */
                Array(const RFTYPE::Size Length1);

                /**
                    * Create a 2D Array.
                    *
                    * \param Length1 The size of the first dimension of the
                    *                Array to create.
                    * \param Length2 The size of the second dimension of the 
                    *                Array to create.
                    */
                Array(const RFTYPE::Size Length1,
                    const RFTYPE::Size Length2);

                /**
                    * Create a 3D Array.
                    *
                    * \param Length1 The size of the first dimension of the
                    *                Array to create.
                    * \param Length2 The size of the second dimension of the 
                    *                Array to create.
                    * \param Length3 The size of the third dimension of the 
                    *                Array to create.
                    */
                Array(const RFTYPE::Size Length1,
                    const RFTYPE::Size Length2,
                    const RFTYPE::Size Length3);

                /**
                    * \brief Creates a multidimensional Array of the specified 
                    *        dimension lengths. The dimension lengths are 
                    *        specified in an array of system depended type.
                    *
                    * \param Lengths An array of system depended type that represent 
                    *                the size of each dimension of the Array 
                    *                to create.
                    */
                static Memory::AutoPointer<Array<T,SP,MA,MO> > 
                    CreateInstance(const Array<RFTYPE::Size>& Lengths);

                /**
                    * \brief Creates a 1D Array of the specified length. 
                    *        The data of the Array are copied from the c array.
                    *
                    * \param CArray An array which was created by C.
                    * \param Length Specify the length of the Array.
                    */
                static Memory::AutoPointer<Array<T,SP,MA,MO> > 
                    CreateInstance(const T CArray[], 
                        const RFTYPE::Size Length);

                virtual ~Array();

            // Properties
                /**
                    * Gets the number of elements contained in the Array.
                    */
                RFTYPE::Size Count()const;

                /** \brief Gets the rank (number of dimensions) of the Array<T>.
                    *
                    * Retrieving the value of this property is an O(1) operation.
                    * 
                    * \return The rank (number of dimensions) of the Array.
                    */
                RFTYPE::Size Rank()const;

                /** 
                    * \brief Gets an object that can be used to synchronize access 
                    *         to the Array<T>.
                    *
                    * Classes that use arrays can also implement their own 
                    * synchronization using the SyncRoot property. The synchronizing
                    * code must perform operations on the SyncRoot of the collection,
                    * not directly on the collection. This ensures proper operation 
                    * of collections that are derived from other objects. 
                    * Specifically, it maintains proper synchronization with other 
                    * threads that might be simultaneously modifying the collection. 
                    * Note that some implementations of SyncRoot might return the 
                    * Array itself.
                    * 
                    * Enumerating through a collection is intrinsically not a thread 
                    * safe procedure. Even when a collection is synchronized, other 
                    * threads can still modify the collection. To guarantee 
                    * thread safety during enumeration, you can either lock the
                    * collection during the entire enumeration.
                    *
                    * Retrieving the value of this property is an O(1) operation.
                    *
                    * \return An object that can be used to synchronize access to 
                    *         the Array.
                    */
                Threading::ISynchronize& SyncRoot();                

                /**
                    * \brief Gets a value indicating whether access to the 
                    *        Array is synchronized (thread safe).
                    */           
                RFTYPE::Bool IsSynchronized()const;

                /**
                    * \brief Gets a value indicating whether the Array has a 
                    *        fixed size.
                    * An array with a fixed size does not allow the addition 
                    * or removal of elements after the array is created, but 
                    * it allows the modification of existing elements.
                    */
                RFTYPE::Bool IsFixedSize()const;

                /**
                    * Gets a value indicating whether the Array is read-only.
                    */
                RFTYPE::Bool IsReadOnly()const;

                /**
                    * Sets the element at the specified index.   
                    * 
                    * \param Index Specify the index of the element.
                    * \param Value The value which will be assigned to the element.
                    */
                void Item(RFTYPE::Size Index, const T& Value);

                /**
                    * Gets the element at the specified index.                     
                    * \param Index Specify the index of the element.
                    */
                T& Item(RFTYPE::Size Index)const;

            // Methods
                /**
                    * \brief Searches an entire one-dimensional sorted Array 
                    *        for a value using the specified Comparer function.
                    *
                    * \param Value The value which will searched.
                    * \param Comparer The callback which will be called for 
                    *                 each element of the array.
                    */
                RFTYPE::Size BinarySearch(const T& Value, 
                    const Delegate2<T&,T&,RFTYPE::Size>* Comparer=0);

                /**
                    * \brief Searches an entire one-dimensional sorted Array 
                    *        for a value using the specified Comparer function.
                    *
                    * \param Index The starting index of the range to search.
                    * \param Length The length of the range to search.
                    * \param Value The value which will searched.
                    * \param Comparer The callback which will be called for 
                    *                 each element of the array.
                    */
                RFTYPE::Size BinarySearch(RFTYPE::Size Index, 
                    RFTYPE::Size Length, const T& Value, 
                    const Delegate2<T&,T&,RFTYPE::Size>* Comparer=0);
                
                /**
                    * \brief Creates a shallow copy of the Array.
                    *
                    * A shallow copy of an Array copies only the elements of 
                    * the Array, whether they are reference types or value 
                    * types, but it does not copy the objects that the 
                    * references refer to. The references in the new Array 
                    * point to the same objects that the references in the 
                    * original Array point to.
                    *
                    * In contrast, a deep copy of an Array copies the elements
                    * and everything directly or indirectly referenced by the 
                    * elements.
                    *
                    * This method is an O(n) operation, where n is Count.
                    */
                Memory::AutoPointer<Array<T,SP,MA,MO> > Clone()const;

                /**
                    * \brief Copies a range of elements from an Array starting
                    *        at the specified source index and pastes them to 
                    *        another Array starting at the specified destination 
                    *        index. Guarantees that all changes are undone if 
                    *        the copy does not succeed completely.
                    *
                    * \param SourceIndex A system depended type that represents                      
                    *                    the index in the sourceArray at which 
                    *                    copying begins.
                    * \param DestinationArray The Array that receives the data.
                    * \param DestinationIndex A system depended type that 
                    *                         represents the index in the 
                    *                         destinationArray at which storing 
                    *                         begins.
                    * \param Length A system depended type that represents 
                    *               the number of elements to copy.
                    */
                RFTYPE::Bool ConstrainedCopy(
                    RFTYPE::Size SourceIndex,
                    Array<T,SP,MA,MO>& DestinationArray,
                    RFTYPE::Size DestinationIndex,
                    RFTYPE::Size Length);

                /**
                    * \brief Copies a range of elements from an Array starting
                    *        at the specified source index and pastes them to 
                    *        another Array starting at the specified destination 
                    *        index. Guarantees that all changes are undone if 
                    *        the copy does not succeed completely.
                    *
                    * \param DestinationArray The Array that receives the data.
                    * \param Length A system depended type that represents 
                    *               the number of elements to copy.
                    */
                RFTYPE::Bool ConstrainedCopy(
                    Array<T,SP,MA,MO>& DestinationArray, 
                    RFTYPE::Size Length);

                /**
                    * Converts an array of one type to an array of another type.
                    *
                    * \param Converter A function that converts each element 
                    *                  from one type to another type.
                    */
                template<typename Out>
                Memory::AutoPointer<Array<Out,SP> > ConvertAll(
                    const Delegate1<T,Out>& Converter);

                /**
                    * \brief Copies a range of elements from an Array starting 
                    *        at the first element and pastes them into another 
                    *        Array starting at the first element. The length 
                    *        is specified as a system depended type.
                    *
                    * \param DestinationArray The Array that receives the data.
                    * \param Length A 32-bit unsigned integer that represents 
                    *               the number of elements to copy.
                    */
                void Copy(Array<T,SP,MA,MO>& DestinationArray, 
                    RFTYPE::Size Length);

                /**
                    * \brief Copies a range of elements from an Array starting 
                    *        at the first element and pastes them into another 
                    *        Array starting at the first element. The length 
                    *        is specified as a system depended type.
                    *
                    * \param Index A system depended type that represents 
                    *              the index in the sourceArray at which 
                    *              copying begins.
                    * \param DestinationArray The Array that receives the data.
                    * \param DestinationIndex A system depended type that 
                    *                         represents the index in the DestinationArray 
                    *                         at which storing begins.
                    * \param Length A 32-bit unsigned integer that represents 
                    *               the number of elements to copy.
                    */
                void Copy(RFTYPE::Size Index, 
                    Array<T,SP,MA,MO>& DestinationArray,
                    RFTYPE::Size DestinationIndex, 
                    RFTYPE::Size Length);

                /**
                    * \brief Determines whether the specified array contains 
                    *        elements that match the conditions defined by the
                    *        specified Match.
                    *
                    * \param Match The function that defines the conditions of
                    *              the elements to search for.
                    */
                RFTYPE::Bool Exists(const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified Match, and returns the 
                    *        first occurrence within the entire Array.
                    *
                    * \param Match The function that defines the conditions of 
                    *              the element to search for.
                    */
                T* Find(const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Retrieves all the elements that match the conditions 
                    *        defined by the specified predicate.
                    *
                    * \param Match The function that defines the conditions of
                    *              the elements to search for.
                    */
                Memory::AutoPointer<Array<T,SP,MA,MO> > FindAll(
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified Match, and returns the 
                    *        zero-based index of the first occurrence within 
                    *        the entire Array.
                    *
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindIndex(
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified Match, and returns the 
                    *        zero-based index of the first occurrence within 
                    *        the entire Array.
                    *
                    * \param StartIndex The zero-based starting index of the search.
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindIndex(RFTYPE::Size StartIndex,
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified Match, and returns the 
                    *        zero-based index of the first occurrence within 
                    *        the entire Array.
                    *
                    * \param StartIndex The zero-based starting index of the search.
                    * \param Count The number of elements in the section to search.
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindIndex(RFTYPE::Size StartIndex,
                    RFTYPE::Size Count, 
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified predicate, and returns 
                    *        the last occurrence within the entire Array.
                    *
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                T* FindLast(const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified predicate, and returns the 
                    *        zero-based index of the last occurrence within the
                    *        entire Array.
                    *
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindLastIndex(
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified predicate, and returns the 
                    *        zero-based index of the last occurrence within the
                    *        entire Array.
                    *
                    * \param StartIndex The zero-based starting index of the 
                    *                   backward search.
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindLastIndex(
                    RFTYPE::Size StartIndex,
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Searches for an element that matches the conditions 
                    *        defined by the specified predicate, and returns the 
                    *        zero-based index of the last occurrence within the
                    *        entire Array.
                    *
                    * \param StartIndex The zero-based starting index of the 
                    *                   backward search.
                    * \param Count The number of elements in the section to search.
                    * \param Match The function that defines the conditions of
                    *              the element to search for.
                    */
                RFTYPE::Size FindLastIndex(
                    RFTYPE::Size StartIndex, RFTYPE::Size Count, 
                    const Delegate1<T,RFTYPE::Bool>& Match);

                /**
                    * \brief Performs the specified action for each element of 
                    *        the specified array and pass the element as parameter.
                    *
                    * \param Action The function to perform on each element of array.
                    */
                void ForEach(const Delegate1<T&>& Action);
            

                /**
                    * \brief Performs the specified action for each element of 
                    *        the specified array and pass the element and
                    *        Param as parameters.
                    *
                    * \param Action The function to perform on each element of array.
                    * \param Param A value which will be passed additionally to the Action.
                    */
                template<typename X>
                void ForEach(const Delegate2<T&,X>& Action,X Param);

                /**
                    * Returns an IEnumerator for the Array.
                    */
                ArrayEnumerator<T> GetArrayEnumerator()const;

                /**
                * Returns an Enumerator for the Array.
                */
                EnumeratorType GetEnumerator()const;

                /**
                    * \brief Gets a system depended type that represents the
                    *        number of elements in the specified dimension of 
                    *        the Array.
                    *
                    * \param Dimension A system depend size that represents 
                    *                  the number of elements in the specified 
                    *                  dimension.
                    */
                RFTYPE::Size GetLength(RFTYPE::Size Dimension);

                /**
                    * \brief Gets the value at the specified position in the 
                    *        one-dimensional Array.
                    *
                    * \param Index An Array of 32-bit unsigned integer indices.
                    */
                const T& GetValue(Array<RFTYPE::Size>& Index);

                /**
                    * \brief Gets the value at the specified position in the 
                    *        one-dimensional Array.
                    *
                    * \param Index A 32-bit unsigned integer that represents 
                    *              the position of the Array element to get.
                    */
                const T& GetValue(RFTYPE::Size Index);

                /**
                    * \brief Gets the value at the specified position in the 
                    *        one-dimensional Array.
                    *
                    * \param Index1 A 32-bit unsigned integer that represents 
                    *               the first-dimension index of the Array 
                    *               element to get.
                    * \param Index2 A system depended type that represents 
                    *               the second-dimension index of the Array 
                    *               element to get.
                    */
                const T& GetValue(RFTYPE::Size Index1,
                                  RFTYPE::Size Index2);

                /**
                    * \brief Gets the value at the specified position in the 
                    *        one-dimensional Array.
                    *
                    * \param Index1 A system depended type that represents 
                    *               the first-dimension index of the Array 
                    *               element to get.
                    * \param Index2 A system depended type that represents 
                    *               the second-dimension index of the Array 
                    *               element to get.
                    * \param Index3 A system depended type that represents 
                    *               the third-dimension index of the Array 
                    *               element to get.
                    */
                const T& GetValue(RFTYPE::Size Index1,
                                  RFTYPE::Size Index2,
                                  RFTYPE::Size Index3);

                /**
                    * \brief Searches for the specified object and returns the
                    *        index of the first occurrence within the entire Array.
                    *
                    * \param Value The object to locate in array.
                    * \return The zero-based index of the first occurrence of 
                    *         value within the entire array, if found; 
                    *         otherwise, �1.
                    */
                RFTYPE::Size IndexOf(const T& Value);

                /**
                    * \brief Searches for the specified object and returns the 
                    *        index of the first occurrence within the range of
                    *        elements in the Array that extends from the 
                    *        specified index to the last element. 
                    *
                    * \param Value The object to locate in array.
                    * \param StartIndex The zero-based starting index of the 
                    *                   search. 0 (zero) is valid in an empty array.
                    * \return The zero-based index of the first occurrence of 
                    *         value within the entire array, if found; 
                    *         otherwise, �1.
                    */
                RFTYPE::Size IndexOf(const T& Value, 
                    const RFTYPE::Size StartIndex);

                /**
                    * \brief Searches for the specified object and returns the 
                    *        index of the first occurrence within the range of 
                    *        elements in the Array that starts at the specified 
                    *        index and contains the specified number of elements.
                    *
                    * \param Value The object to locate in array.
                    * \param StartIndex The zero-based starting index of the 
                    *                   search. 0 (zero) is valid in an empty array.
                    * \param Count The number of elements in the section to search.
                    * \return The zero-based index of the first occurrence of 
                    *         value within the entire array, if found; 
                    *         otherwise, �1.
                    */
                RFTYPE::Size IndexOf(const T& Value, 
                    const RFTYPE::Size StartIndex,
                    const RFTYPE::Size Count);
                    
                /**
                    * \brief Searches for the specified object and returns the 
                    *        index of the last occurrence within the entire Array.
                    *
                    * \param Value The object to locate in array.
                    * \return The zero-based index of the last occurrence of 
                    *         value within the range of elements in array that 
                    *         contains the number of elements specified in count 
                    *         and ends at startIndex, if found; otherwise, �1.
                    */
                RFTYPE::Size LastIndexOf(const T& Value);

                /**
                    * \brief Searches for the specified object and returns the 
                    *        index of the last occurrence within the range of 
                    *        elements in the Array that extends from the first 
                    *        element to the specified index.
                    *
                    * \param Value The object to locate in array.
                    * \param StartIndex The zero-based starting index of the 
                    *                   backward search.
                    * \return The zero-based index of the last occurrence of 
                    *         value within the range of elements in array that 
                    *         contains the number of elements specified in count 
                    *         and ends at startIndex, if found; otherwise, �1.
                    */
                RFTYPE::Size LastIndexOf(const T& Value, 
                    const RFTYPE::Size StartIndex);

                /**
                    * \brief Searches for the specified object and returns the 
                    *        index of the last occurrence within the range of 
                    *        elements in the Array that contains the specified 
                    *        number of elements and ends at the specified index.
                    *
                    * \param Value The object to locate in array.
                    * \param StartIndex The zero-based starting index of the 
                    *                   backward search.
                    * \param Count The number of elements in the section to search.
                    * \return The zero-based index of the last occurrence of 
                    *         value within the range of elements in array that 
                    *         contains the number of elements specified in count 
                    *         and ends at startIndex, if found; otherwise, �1.
                    */
                RFTYPE::Size LastIndexOf(const T& Value, 
                    const RFTYPE::Size StartIndex,
                    const RFTYPE::Size Count);

                /**
                    * \brief Changes the number of elements of an array to the 
                    *        specified new size.
                    *
                    * \param NewSize The size of the new array.
                    */
                void Resize(RFTYPE::Size NewSize);

                /**
                    * \brief Reverses the sequence of the elements in the entire 
                    *        one-dimensional Array.
                    */
                void Reverse();

                /**
                    * \brief Reverses the sequence of the elements in a range 
                    *        of elements in the one-dimensional Array.
                    *
                    * \param Index The starting index of the section to reverse.
                    * \param Length The number of elements in the section to reverse.
                    */
                void Reverse(RFTYPE::Size Index, 
                    RFTYPE::Size Length);

                /**
                    * \brief Sets a value to the element at the specified 
                    *        position in the one-dimensional Array. The index 
                    *        is specified as a system depended type.
                    *
                    * \param Value The new value for the specified element.
                    * \param Index A system depended type that represents 
                    *              the position of the Array element to set.
                    */
                void SetValue(const T& Value, RFTYPE::Size Index);

                /**
                    * \brief Sets a value to the element at the specified 
                    *        position in the multidimensional Array. The indexes 
                    *        are specified as an array of system depended type.
                    *
                    * \param Value The new value for the specified element.
                    * \param Index A one-dimensional array of 32-bit unsigned 
                    *              integers that represent the indexes specifying 
                    *              the position of the element to set.
                    */
                void SetValue(const T& Value, 
                    Array<RFTYPE::Size,SP>& Indices);

                /**
                    * \brief Sets a value to the element at the specified 
                    *        position in the two-dimensional Array. The indexes 
                    *        are specified as system depended type.
                    *
                    * \param Value The new value for the specified element.
                    * \param Index1 A system depended type that represents 
                    *               the first-dimension index of the Array 
                    *               element to set.
                    * \param Index2 A system depended type that represents 
                    *               the second-dimension index of the Array 
                    *               element to set.
                    */
                void SetValue(const T& Value, RFTYPE::Size Index1,
                    RFTYPE::Size Index);

                    
                /**
                    * \brief Sets a value to the element at the specified 
                    *        position in the three-dimensional Array. The 
                    *        indexes are specified as system depended type.
                    *
                    * \param Value The new value for the specified element.
                    * \param Index1 A system depended type that represents 
                    *               the first-dimension index of the Array 
                    *               element to set.
                    * \param Index2 A system depended type that represents 
                    *               the second-dimension index of the Array 
                    *               element to set.
                    * \param Index3 A system depended type that represents 
                    *               the third-dimension index of the Array 
                    *               element to set.
                    */
                void SetValue(const T& Value, RFTYPE::Size Index1,
                    RFTYPE::Size Index2, RFTYPE::Size Index3);

                /**
                    * \brief Sorts the elements in an Array using the specified 
                    *        Comparer method.
                    *
                    * \param Comparer The method which will be called for each
                    *                 element of the Array.
                    */
                void Sort(const Delegate2<T&,T&,RFTYPE::Size>& Comparer);

                /**
                    * \brief Sorts the elements in a range of elements in an 
                    *        Array using the specified Comparer method.
                    *
                    * \param Index The starting index of the range to sort.
                    * \param Length The number of elements in the range to sort.
                    * \param Comparer The method which will be called for each
                    *                 element of the Array.
                    */
                void Sort(RFTYPE::Size Index, RFTYPE::Size Length,
                            const Delegate2<T&,T&,RFTYPE::Size>& Comparer);

                /**
                    * \brief Sorts a pair of Array objects (one contains the 
                    *        keys and the other contains the corresponding 
                    *        items) based on the keys in the first Array using 
                    *        the specified Comparer method.
                    *
                    * \tparam TKey The type of the elements of the key array.
                    * \tparam TValue The type of the elements of the items array.
                    * \param Keys The one-dimensional, zero-based Array that 
                    *             contains the keys to sort. 
                    * \param Items The one-dimensional, zero-based Array that 
                    *              contains the items that correspond to the 
                    *              keys in keys, or Nothing to sort only keys.
                    * \param Comparer The method which will be called for each
                    *                 element of the Array.
                    */
                template <typename TKey, typename TValue>
                static void Sort(Array<TKey,SP,MA,MO>& Keys, 
                                    Array<TValue,SP,MA,MO>& Items,
                                    const Delegate2<T&,T&,RFTYPE::Size>& Comparer);

                /**
                    * \brief Sorts a range of elements in a pair of Array 
                    *        objects (one contains the keys and the other 
                    *        contains the corresponding items) based on the 
                    *        keys in the first Array using the specified 
                    *        Comparer method.
                    *
                    * \tparam TKey The type of the elements of the key array.
                    * \tparam TValue The type of the elements of the items array.
                    * \param Keys The one-dimensional, zero-based Array that 
                    *             contains the keys to sort. 
                    * \param Items The one-dimensional, zero-based Array that 
                    *              contains the items that correspond to the 
                    *              keys in keys, or Nothing to sort only keys.
                    * \param Index The starting index of the range to sort.
                    * \param Length The number of elements in the range to sort.
                    * \param Comparer The method which will be called for each
                    *                 element of the Array.
                    */
                template <typename TKey, typename TValue>
                static void Sort(Array<TKey,SP,MA,MO>& Keys, 
                                    Array<TValue,SP,MA,MO>& Items,
                                    RFTYPE::Size Index, 
                                    RFTYPE::Size Length,
                                    const Delegate2<T&,T&,RFTYPE::Size>& Comparer);

                /**
                    * \brief Determines whether every element in the array matches 
                    *        the conditions defined by the specified Match method.
                    *
                    * \param Match This method defines the conditions to check 
                    *        against the elements.
                    * \return true if every element in array matches the conditions
                    *         defined by the specified Match; otherwise, false.
                    *         If there are no elements in the array, the return
                    *         value is true.
                    */
                RFTYPE::Bool TrueForAll(
                    const Delegate1<T,RFTYPE::Bool>& Match);

                void Swap(Array<T,SP,MA,MO>& Other);
            // Operators
                /**
                    * \brief Create a deep copy of the Array.
                    *
                    * A shallow copy of an Array copies only the elements of 
                    * the Array, whether they are reference types or value 
                    * types, but it does not copy the objects that the 
                    * references refer to. The references in the new Array 
                    * point to the same objects that the references in the 
                    * original Array point to.
                    *
                    * In contrast, a deep copy of an Array copies the elements
                    * and everything directly or indirectly referenced by the 
                    * elements.
                    */
                Array<T,SP,MA,MO>& operator=(
                    const Array<T,SP,MA,MO>& Other);

                T& operator()(const RFTYPE::Size Index);
                    
                const T& operator()(const RFTYPE::Size Index)const;

                T& operator()(const RFTYPE::Size Index1,
                              const RFTYPE::Size Index2);
                    
                const T& operator()(const RFTYPE::Size Index1,
                                    const RFTYPE::Size Index2)const;

                T& operator()(const RFTYPE::Size Index1,
                              const RFTYPE::Size Index2,
                              const RFTYPE::Size Index3);

                const T& operator()(const RFTYPE::Size Index1,
                                    const RFTYPE::Size Index2,
                                    const RFTYPE::Size Index3)const;

            protected:
                RFTYPE::Size* m_Length;
                RFTYPE::Size m_Rank;
                Threading::ISynchronize* m_SyncRoot;
                RFTYPE::Bool m_Synchronized;
                T* m_Data;
                RFTYPE::Size m_ElementCount;

            // helper functions
                /// setup the data part of the class
                RFTYPE::Bool InitArray(RFTYPE::Size Rank, 
                    const RFTYPE::Size* LengthArray);
        };

        // Constructor & Destructor

        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>::Array()
        {
            InitArray(0,0);
        }

        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>::Array(const Array<T,SP,MA,MO>& Copy)
        {
            *this=Copy;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>::Array(const RFTYPE::Size Length1)
        {
            InitArray(1,&Length1);
        }

        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>::Array(const RFTYPE::Size Length1,
            const RFTYPE::Size Length2)
        {
            RFTYPE::Size arr[2];
            arr[0]=Length1;arr[1]=Length2;
            InitArray(2,arr);
        }

        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>::Array(const RFTYPE::Size Length1,
            const RFTYPE::Size Length2,
            const RFTYPE::Size Length3)
        {
            RFTYPE::Size arr[3];
            arr[0]=Length1; arr[1]=Length2; arr[2]=Length3;
            InitArray(3,arr);
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<Array<T,SP,MA,MO> > Array<T,SP,MA,MO>::CreateInstance(
            const T CArray[], 
            const RFTYPE::Size Length)
        {
            typename Memory::AutoPointer<Array<T,SP,MA,MO> > arr(MA::template New<Array<T,SP,MA,MO> >());
            if (arr.Get()!=0) // out of memory check
            {
                if (arr->InitArray(1,&Length))
                    MO::Copy(arr->m_Data,CArray,Length);
                else // something was going wrong, clean up
                    arr.Reset();
            }
            return arr;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<Array<T,SP,MA,MO> > Array<T,SP,MA,MO>::CreateInstance(
            const Array<RFTYPE::Size>& Lengths)
        {
            typename Memory::AutoPointer<Array<T,SP,MA,MO> > arr(MA::template New<Array>());
            if (arr.Get()!=0) // out of memory check
                if (false==arr->InitArray(Lengths.m_ElementCount, Lengths.m_Data))
                {// something was going wrong, clean up
                    arr.Reset();
                }                                            
            return arr;
        }
            
        template<typename T, typename SP, typename MA,typename MO>
        Array<T,SP,MA,MO>::~Array()
        {
            if (m_SyncRoot!=0)
            {
                MA::Free(static_cast<SP*>(m_SyncRoot));
                m_SyncRoot=0;
            }

            if (m_Data!=0)
            {
                MA::FreeArray(m_Data);
                m_Data=0;
            }
        }

        // Properties

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::Count()const
        {
            return m_ElementCount;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::Rank()const
        {
            return m_Rank;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Threading::ISynchronize& Array<T,SP,MA,MO>::SyncRoot()
        {
            return *m_SyncRoot;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::IsSynchronized()const
        {
            return m_Synchronized;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::IsFixedSize()const
        {
            return true;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::IsReadOnly()const
        {
            return false;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Item(RFTYPE::Size Index, const T& Value)
        {
            Assert(m_Rank>0,"Try to access an item on an empty array.");
            Assert(m_ElementCount>Index,"Index out of bound.");
            m_Data[Index]=Value;
        }

        template<typename T, typename SP, typename MA, typename MO>
        T& Array<T,SP,MA,MO>::Item(RFTYPE::Size Index)const
        {   
            Assert(m_Rank>0,"Try to access an item on an empty array.");
            Assert(m_ElementCount>Index,"Index out of bound.");
            return m_Data[Index];
        }

        // Methods

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::BinarySearch(const T& Value, 
            const Delegate2<T&,T&,RFTYPE::Size>* Comparer)
        {
            return BinarySearch(0,m_ElementCount,Value,Comparer);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::BinarySearch(
            RFTYPE::Size Index, RFTYPE::Size Length, const T& Value, 
            const Delegate2<T&,T&,RFTYPE::Size>* Comparer)
        {
            RFTYPE::Size left=Index,right=Index+Length-1,middle;
            while(left<=right && right < m_ElementCount)
            {
                middle=(left+right)>>1;
                if (m_Data[middle]==Value)
                    return middle;
                else
                    if (m_Data[middle]>Value)
                        right=middle-1;
                    else
                        left=middle+1;
            }
            return ~left;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<Array<T,SP,MA,MO> > Array<T,SP,MA,MO>::Clone()const
        {
            Array<RFTYPE::Size,SP,MA,MO> lengths(m_Rank);
            for (RFTYPE::Size i=0;i<m_Rank;++i)
                lengths.m_Data[i]=m_Length[i];
            Memory::AutoPointer<Array> result=Array::CreateInstance(lengths);
            MO::Copy(result->m_Data,m_Data,m_ElementCount);
            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::ConstrainedCopy(RFTYPE::Size SourceIndex,
            Array<T,SP,MA,MO>& DestinationArray,
            RFTYPE::Size DestinationIndex,
            RFTYPE::Size Length)
        {
            if (m_Rank!=DestinationArray.m_Rank)
                return false;
            if (m_ElementCount<SourceIndex+Length)
                return false;
            if (DestinationArray.m_ElementCount<DestinationIndex+Length)
                return false;
            for (RFTYPE::Size i=0;i<m_Rank;++i)
                if (m_Length[i]!=DestinationArray.m_Length[i])
                    return false;
            MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[SourceIndex],Length);
            return true;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::ConstrainedCopy(
            Array<T,SP,MA,MO>& DestinationArray, 
            RFTYPE::Size Length)
        {
            return ConstrainedCopy(0,DestinationArray,0,Length);
        }

        template<typename T, typename SP, typename MA, typename MO>
        template<typename Out>
        Memory::AutoPointer<Array<Out,SP> > Array<T,SP,MA,MO>::ConvertAll(
            const Delegate1<T,Out>& Converter)
        {
            Array<RFTYPE::Size,SP,MA,MO> lengths(m_Rank);
            for (RFTYPE::Size i=0;i<m_Rank;++i)
                lengths.m_Data[i]=m_Length[i];

            Memory::AutoPointer<Array<Out,SP,MA,MO> > result=Array<Out,SP,MA,MO>::CreateInstance(lengths);
            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                result->m_Data[i]=Converter(m_Data[i]);

            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Copy(Array<T,SP,MA,MO>& DestinationArray, 
            RFTYPE::Size Length)
        {
            Copy(0,DestinationArray,0,Length);
        }
            
        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Copy(RFTYPE::Size Index, 
            Array<T,SP,MA,MO>& DestinationArray,
            RFTYPE::Size DestinationIndex, 
            RFTYPE::Size Length)
        {
            Assert(m_Rank==DestinationArray.m_Rank,"Try to copy one array to an other with different dimensions.");
            Assert(m_ElementCount>=Index+Length,"Operation leave the memory bound of source array.");
            Assert(DestinationArray.m_ElementCount>=DestinationIndex+Length,"Operation leave the memory bound of the destination array.");
            MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[Index],Length);
        }
            
        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::Exists(
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            RFTYPE::Size end=m_ElementCount-1;
            for (RFTYPE::Size i=0;i<end;++i)
                if (Match(m_Data[i]))
                    return true;
            return false;
        }

        template<typename T, typename SP, typename MA, typename MO>
        T* Array<T,SP,MA,MO>::Find(const Delegate1<T,RFTYPE::Bool>& Match)
        {
            RFTYPE::Size end=m_ElementCount-1;
            for (RFTYPE::Size i=0;i<end;++i)
                if (Match(m_Data[i]))
                    return &m_Data[i];
            return 0;
        }

        template<typename T, typename SP, typename MA, typename MO>
        T* Array<T,SP,MA,MO>::FindLast(const Delegate1<T,RFTYPE::Bool>& Match)
        {
            RFTYPE::Size end=m_ElementCount-1;
            for (RFTYPE::Size i=end;i>=0 && i <= end;--i)
                if (Match(m_Data[i]))
                    return &m_Data[i];
            return 0;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<Array<T,SP,MA,MO> > Array<T,SP,MA,MO>::FindAll(
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Memory::AutoPointer<Array<T,SP,MA,MO> > result;
            // reserve memory with the size of pow
            RFTYPE::Size reserved=2;
            RFTYPE::Size size=0;
            T* arr=MA::template NewArray<T>(reserved);

            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                if (Match(m_Data[i]))
                {
                    if (size+1>reserved)// no more free buckets available
                    {
                        // double reserved memory
                        reserved<<=1;
                        T* tmp=MA::template NewArray<T>(reserved);
                        MO::Copy(tmp,arr,size);
                        MA::FreeArray(arr);
                        arr=tmp;
                    }
                    arr[size]=m_Data[i];
                    ++size;
                }
            // store the final result and free the temporary memory
            result=Memory::AutoPointer<Array<T,SP,MA,MO> >(new Array<T,SP,MA,MO>(size));
            MO::Copy(result->m_Data,arr,size);
            MA::FreeArray(arr);
            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindIndex(
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return FindIndex(0,m_Length[0],Match);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindIndex(
            RFTYPE::Size StartIndex,
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return FindIndex(StartIndex,m_Length[0]-StartIndex,Match);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindIndex(
            RFTYPE::Size StartIndex,
            RFTYPE::Size Count, 
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            RFTYPE::Size end=StartIndex+Count;
            for (RFTYPE::Size i=StartIndex;i<end;++i)
                if (Match(m_Data[i]))
                    return i;
            return -1;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindLastIndex(
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return FindLastIndex(m_Length[0]-1,m_Length[0],Match);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindLastIndex(
            RFTYPE::Size StartIndex,
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return FindLastIndex(StartIndex,m_Length[0]-StartIndex,Match);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::FindLastIndex(
            RFTYPE::Size StartIndex, RFTYPE::Size Count, 
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");                
            RFTYPE::Size end=StartIndex-(Count-1);
            for (RFTYPE::Size i=StartIndex;i>=end;--i)
                if (Match(m_Data[i]))
                    return i;
            return -1;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::ForEach(const Delegate1<T&>& Action)
        {
            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                Action(m_Data[i]);
        }

        template<typename T, typename SP, typename MA, typename MO>
        template<typename X>
        void Array<T,SP,MA,MO>::ForEach(const Delegate2<T&,X>& Action, X Param)
        {
            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                Action(m_Data[i],Param);
        }
             
        template<typename T, typename SP, typename MA, typename MO>
        ArrayEnumerator<T> Array<T,SP,MA,MO>::GetArrayEnumerator()const
        {
            ArrayEnumerator<T> result(m_Data, &m_Data[m_ElementCount - 1]);
            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        typename Array<T, SP, MA, MO>::EnumeratorType Array<T, SP, MA, MO>::GetEnumerator()const
        {
            EnumeratorType result;
            result.m_Start = m_Data;
            result.m_Current = m_Data;
            result.m_Elements = m_ElementCount;
            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::GetLength(
            RFTYPE::Size Dimension)
        {
            Assert(Dimension<m_Rank,"Dimension is out bound.");
            return m_Length[Dimension];
        }
                   
        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::GetValue(RFTYPE::Size Index)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            Assert(Index<m_Length[0],"Index out of bound.");
            return m_Data[Index];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::GetValue(RFTYPE::Size Index1,
                                                RFTYPE::Size Index2)
        {
            Assert(m_Rank==2,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            return m_Data[(Index1*m_Length[1])+Index2];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::GetValue(RFTYPE::Size Index1,
                                                RFTYPE::Size Index2,
                                                RFTYPE::Size Index3)
        {
            Assert(m_Rank==3,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            Assert(Index3<m_Length[2],"Index out of bound.");
            return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::GetValue(Array<RFTYPE::Size>& Index)
        {
            RFTYPE::Size index=0;
            RFTYPE::Size i=0;
            for (;i<Index.Count()-1;++i)
            {
                index+=m_Length[i]*Index.m_Data[i];
                Assert(index<m_ElementCount,"Index out of bound.");
            }
            index+=Index.m_Data[i];
            Assert(index<m_ElementCount,"Index out of bound.");
            return m_Data[index];
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::IndexOf(const T& Value)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return IndexOf(Value,0,m_Length[0]);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::IndexOf(const T& Value,
            const RFTYPE::Size StartIndex)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return IndexOf(Value,StartIndex,m_Length[0]-StartIndex);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::IndexOf(const T& Value,
            const RFTYPE::Size StartIndex, 
            const RFTYPE::Size Count)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            RFTYPE::Size end=StartIndex+Count;
            Assert(end>=0,"Operation out of bound.");
            for (RFTYPE::Size i=StartIndex;i<end;++i)
                if (m_Data[i]==Value)
                    return i;
            return -1;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::LastIndexOf(const T& Value)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return LastIndexOf(Value,m_Length[0]-1,m_Length[0]);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::LastIndexOf(const T& Value, 
            const RFTYPE::Size StartIndex)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            return LastIndexOf(Value,StartIndex,m_Length[0]-StartIndex);
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Size Array<T,SP,MA,MO>::LastIndexOf(
            const T& Value, const RFTYPE::Size StartIndex,
            const RFTYPE::Size Count)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");                
            RFTYPE::Size end=StartIndex-(Count-1);
            Assert(end>=0,"Operation out of bound.");
            for (RFTYPE::Size i=StartIndex;i>=end;--i)
                if (m_Data[i]==Value)
                    return i;
            return -1;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Resize(RFTYPE::Size NewSize)
        {
            if(m_Rank == 0)
            {
	            InitArray(1, &NewSize);
            }

            Assert(m_Rank == 1, "Unexpected dimension of array.");

            if(NewSize != m_Length[0])
            {
                T* data = MA::template NewArray<T>(NewSize);
                if(std::is_trivially_copyable<T>::value == false)
                {
                    for(RFTYPE::Size i = 0, end = RadonFramework::Math::Math<RFTYPE::Size>::Min(m_Length[0], NewSize); i < end; ++i)
                    {
                        data[i] = m_Data[i];
                    }
                }
                else
                {
                    MO::Copy(data, m_Data, RadonFramework::Math::Math<RFTYPE::Size>::Min(m_Length[0], NewSize));
                }
                MA::FreeArray(m_Data);
                m_Data = data;
                m_Length[0] = NewSize;
                m_ElementCount = NewSize;
            }
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Reverse()
        {
            Reverse(0,m_ElementCount);
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Reverse(RFTYPE::Size Index, 
            RFTYPE::Size Length)
        {
            Assert(Index+Length<=m_ElementCount,"Operation out of bound.");
            RFTYPE::Size end=Index+Length-1;
            RFTYPE::Size halfEnd=Index + (Length >> 1);
            T* tmp=MA::template New<T>();
            for (RFTYPE::Size i=Index; i<halfEnd; ++i)
            {
                MO::Copy(tmp,&m_Data[i],1);
                MO::Move(&m_Data[i],&m_Data[end-i],1);
                MO::Copy(&m_Data[end-i],tmp,1);
            }
            MA::Free(tmp);
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::SetValue(const T& Value, RFTYPE::Size Index)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            Assert(Index<m_ElementCount,"Index out of bound.");
            m_Data[Index]=Value;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::SetValue(const T& Value, RFTYPE::Size Index1,
            RFTYPE::Size Index2)
        {
            Assert(m_Rank==2,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            m_Data[(Index1*m_Length[1])+Index2]=Value;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::SetValue(const T& Value, RFTYPE::Size Index1,
            RFTYPE::Size Index2,
            RFTYPE::Size Index3)
        {
            Assert(m_Rank==3,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            Assert(Index3<m_Length[2],"Index out of bound.");
            m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3]=Value;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::SetValue(const T& Value, 
            Array<RFTYPE::Size,SP>& Indices)
        {
            Assert(m_Rank==Indices.Count(),"Unexpected dimension of array.");
            RFTYPE::Size index=0;
            RFTYPE::Size i=0;
            for (;i<Indices.Count()-1;++i)
            {
                index+=m_Length[i]*Indices.m_Data[i];
                Assert(index<m_ElementCount,"Index out of bound.");
            }
            index+=Indices.m_Data[i];
            Assert(index<m_ElementCount,"Index out of bound.");
            m_Data[index]=Value;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Sort(const Delegate2<T&,T&,RFTYPE::Size>& Comparer)
        {
            Sort(0,m_ElementCount,Comparer);
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Sort(RFTYPE::Size Index, 
            RFTYPE::Size Length,
            const Delegate2<T&,T&,RFTYPE::Size>& Comparer)
        {
            Assert(Index+Length<=m_ElementCount,"Index out of bound.");

            // look at http://alienryderflex.com/quicksort/ for more details
            #define  MAX_LEVELS  300
            T piv;
            RFTYPE::Int64  i = 0, beg[MAX_LEVELS], end[MAX_LEVELS], L, R, swap ;
            beg[0]=Index; end[0]=Index+Length;

            while (i>=0) 
            {
                L=beg[i]; 
                R=end[i]-1;

                if (L<R) 
                {
                    piv=this->m_Data[L];

                    while (L<R) 
                    {
                        while (Comparer(this->m_Data[R],piv)>=0 && L<R) 
                            R--; 

                        if (L<R) 
                            this->m_Data[L++]=this->m_Data[R];

                        while (Comparer(this->m_Data[L],piv)<=0 && L<R) 
                            L++; 

                        if (L<R) 
                            this->m_Data[R--]=this->m_Data[L]; 
                    }

                    this->m_Data[L]=piv; 
                    beg[i+1]=L+1; 
                    end[i+1]=end[i]; 
                    end[i++]=L;

                    if (end[i]-beg[i]>end[i-1]-beg[i-1]) 
                    {
                        swap=beg[i]; 
                        beg[i]=beg[i-1]; 
                        beg[i-1]=swap;
                        swap=end[i]; 
                        end[i]=end[i-1]; 
                        end[i-1]=swap; 
                    }
                }
                else 
                    i--;
            }
        }

        template<typename T, typename SP, typename MA, typename MO>
        template<typename TKey, typename TValue>
        void Array<T,SP,MA,MO>::Sort(Array<TKey,SP,MA,MO>& Keys, 
            Array<TValue,SP,MA,MO>& Items,
            const Delegate2<T&,T&,RFTYPE::Size>& Comparer)
        {
            Sort(Keys,Items,0,Keys.m_ElementCount,Comparer);
        }

        template<typename T, typename SP, typename MA, typename MO>
        template <typename TKey, typename TValue>
        void Array<T,SP,MA,MO>::Sort(Array<TKey,SP,MA,MO>& Keys, 
                                            Array<TValue,SP,MA,MO>& Items,
                                            RFTYPE::Size Index, 
                                            RFTYPE::Size Length,
                        const Delegate2<T&,T&,RFTYPE::Size>& Comparer)
        {
            Assert(Keys.m_ElementCount==Items.m_ElementCount,"Invalid parameter.");
            Assert((Index+Length)<=Keys.m_ElementCount,"Index out of bound.");

            // look at http://alienryderflex.com/quicksort/ for more details
            #define  MAX_LEVELS  300
            TKey key;
            TValue value;
            RFTYPE::Int64  beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R, swap ;
            beg[0]=Index; end[0]=Index+Length;

            while (i>=0) 
            {
                L=beg[i]; 
                R=end[i]-1;

                if (L<R) 
                {
                    key=Keys.Item(L);
                    value=Items.Item(L);

                    while (L<R) 
                    {
                        while (Comparer(Items.Item(R),value)>=0 && L<R) 
                            R--; 

                        if (L<R) 
                        {
                            Items.Item(L,Items.Item(R));
                            Keys.Item(L,Keys.Item(R));
                            ++L;
                        }

                        while (Comparer(Items.Item(L),value)<=0 && L<R) 
                            L++; 

                        if (L<R) 
                        {
                            Items.Item(R,Items.Item(L));
                            Keys.Item(R,Keys.Item(L));
                            --R;
                        }
                    }

                    Keys.Item(L,key); 
                    Items.Item(L,value); 
                    beg[i+1]=L+1; 
                    end[i+1]=end[i]; 
                    end[i++]=L;

                    if (end[i]-beg[i]>end[i-1]-beg[i-1]) 
                    {
                        swap=beg[i]; 
                        beg[i]=beg[i-1]; 
                        beg[i-1]=swap;
                        swap=end[i]; 
                        end[i]=end[i-1]; 
                        end[i-1]=swap; 
                    }
                }
                else 
                    i--;
            }
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::TrueForAll(
            const Delegate1<T,RFTYPE::Bool>& Match)
        {
            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                if (false==Match(m_Data[i]))
                    return false;
            return true;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Array<T,SP,MA,MO>::Swap(Array<T,SP,MA,MO>& Other)
        {
            T* tmpData=m_Data;
            m_Data=Other.m_Data;
            Other.m_Data=tmpData;

            RFTYPE::Size tmpCount=m_ElementCount;
            m_ElementCount=Other.m_ElementCount;
            Other.m_ElementCount=tmpCount;

            RFTYPE::Size* tmpLen=m_Length;
            m_Length=Other.m_Length;
            Other.m_Length=tmpLen;

            RFTYPE::Size tmpRank=m_Rank;
            m_Rank=Other.m_Rank;
            Other.m_Rank=tmpRank;

            RFTYPE::Bool tmpSync=m_Synchronized;
            m_Synchronized=Other.m_Synchronized;
            Other.m_Synchronized=tmpSync;

            Threading::ISynchronize* tmpSynchronize=m_SyncRoot;
            m_SyncRoot=Other.m_SyncRoot;
            Other.m_SyncRoot=tmpSynchronize;
        }

        // Operators
        template<typename T, typename SP, typename MA, typename MO>
        Array<T,SP,MA,MO>& Array<T,SP,MA,MO>::operator=(const Array<T,SP,MA,MO>& Other)
        {
            InitArray(Other.m_Rank,Other.m_Length);
            for (RFTYPE::Size i=0;i<m_ElementCount;++i)
                m_Data[i]=Other.m_Data[i];
            return *this;
        }

        template<typename T, typename SP, typename MA, typename MO>
        T& Array<T,SP,MA,MO>::operator()(const RFTYPE::Size Index)
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            Assert(Index<m_Length[0],"Index out of bound.");                
            return m_Data[Index];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::operator()(const RFTYPE::Size Index)const
        {
            Assert(m_Rank==1,"Unexpected dimension of array.");
            Assert(Index<m_Length[0],"Index out of bound.");
            return m_Data[Index];
        }

        template<typename T, typename SP, typename MA, typename MO>
        T& Array<T,SP,MA,MO>::operator()(const RFTYPE::Size Index1,
                                    const RFTYPE::Size Index2)
        {
            Assert(m_Rank==2,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            return m_Data[(Index1*m_Length[1])+Index2];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::operator()(const RFTYPE::Size Index1,
                                            const RFTYPE::Size Index2)const
        {
            Assert(m_Rank==2,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            return m_Data[(Index1*m_Length[1])+Index2];
        }

        template<typename T, typename SP, typename MA, typename MO>
        T& Array<T,SP,MA,MO>::operator()(const RFTYPE::Size Index1,
                                    const RFTYPE::Size Index2,
                                    const RFTYPE::Size Index3)
        {
            Assert(m_Rank==3,"Unexpected dimension of array");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            Assert(Index3<m_Length[2],"Index out of bound.");
            return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
        }

        template<typename T, typename SP, typename MA, typename MO>
        const T& Array<T,SP,MA,MO>::operator()(
            const RFTYPE::Size Index1,
            const RFTYPE::Size Index2,
            const RFTYPE::Size Index3)const
        {
            Assert(m_Rank==3,"Unexpected dimension of array.");
            Assert(Index1<m_Length[0],"Index out of bound.");
            Assert(Index2<m_Length[1],"Index out of bound.");
            Assert(Index3<m_Length[2],"Index out of bound.");
            return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
        }

        // internal helper functions

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Array<T,SP,MA,MO>::InitArray(
            RFTYPE::Size Rank, 
            const RFTYPE::Size* LengthArray)
        {
            m_Rank=Rank;
            m_Synchronized=false;
            m_Data=0;
            m_Length=0;
            m_SyncRoot=MA::template New<SP>();
            m_ElementCount=0;

            if (m_SyncRoot==0)
                return false;

            if (Rank>0)
            {
                m_Length=MA::template NewArray<RFTYPE::Size>(Rank);

                if (m_Length==0)
                    return false;

                RFTYPE::Size len;
                for (RFTYPE::Size i=0;i<Rank;++i)
                {
                    m_Length[i]=LengthArray[i];
                        
                    if (i==0)
                        len=LengthArray[0];
                    else
                        len*=LengthArray[i];
                }

                m_Data=MA::template NewArray<T>(len);
                m_ElementCount=len;
                if (m_Data==0)
                    return false;
            }
            return true;
        }
    }
}

#endif // RF_COLLECTIONS_ARRAY_HPP