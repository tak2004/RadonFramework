#ifndef RF_COLLECTIONS_ARRAY_HPP
#define RF_COLLECTIONS_ARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Collections/ArrayEnumerator.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
#include <RadonFramework/Collections/ArrayEnumeratorType.hpp>

#include <stdlib.h>

namespace RadonFramework { namespace Collections {

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
         typename MA=Core::Policies::CPPAllocator,
         typename MO=Core::Policies::CMemoryOperation>
class Array
{
template <typename,typename,typename>
friend class Array;
public:
    typedef T Type;
    typedef Enumerator<T, ArrayEnumeratorType> EnumeratorType;
    typedef Enumerator<const T, ArrayEnumeratorType> ConstEnumeratorType;
                
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
    Array(const Array<T,MA,MO>& Copy);

    /**
    * \brief Moves the data during construction.
    *
    * The move constructor make a data exchange.
    *
    * \param Move The object with which the data will be exchanged.
    */
    Array(Array<T, MA, MO>&& Move);

    /**
    * Create a 1D Array.
    *
    * \param Length1 The size of the Array to create.
    */
    Array(const RF_Type::Size Length1);

    /**
    * Create a 2D Array.
    *
    * \param Length1 The size of the first dimension of the
    *                Array to create.
    * \param Length2 The size of the second dimension of the 
    *                Array to create.
    */
    Array(const RF_Type::Size Length1,
        const RF_Type::Size Length2);

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
    Array(const RF_Type::Size Length1,
        const RF_Type::Size Length2,
        const RF_Type::Size Length3);

    /**
    * \brief Creates a multidimensional Array of the specified 
    *        dimension lengths. The dimension lengths are 
    *        specified in an array of system depended type.
    *
    * \param Lengths An array of system depended type that represent 
    *                the size of each dimension of the Array 
    *                to create.
    */
    static Memory::AutoPointer<Array<T,MA,MO> > 
        CreateInstance(const Array<RF_Type::Size>& Lengths);

    /**
    * \brief Creates a 1D Array of the specified length. 
    *        The data of the Array are copied from the c array.
    *
    * \param CArray An array which was created by C.
    * \param Length Specify the length of the Array.
    */
    static Memory::AutoPointer<Array<T,MA,MO> > 
        CreateInstance(const T* CArray, 
            const RF_Type::Size Length);

    virtual ~Array();

// Properties
    /**
    * Gets the number of elements contained in the Array.
    */
    RF_Type::Size Count()const;

    /** \brief Gets the rank (number of dimensions) of the Array<T>.
    *
    * Retrieving the value of this property is an O(1) operation.
    * 
    * \return The rank (number of dimensions) of the Array.
    */
    RF_Type::Size Rank()const;

    /**
    * \brief Gets a value indicating whether the Array has a 
    *        fixed size.
    * An array with a fixed size does not allow the addition 
    * or removal of elements after the array is created, but 
    * it allows the modification of existing elements.
    */
    RF_Type::Bool IsFixedSize()const;

    /**
        * Gets a value indicating whether the Array is read-only.
        */
    RF_Type::Bool IsReadOnly()const;

    /**
    * Sets the element at the specified index.   
    * 
    * \param Index Specify the index of the element.
    * \param Value The value which will be assigned to the element.
    */
    void Item(RF_Type::Size Index, const T& Value);

    /**
    * Gets the element at the specified index.                     
    * \param Index Specify the index of the element.
    */
    T& Item(RF_Type::Size Index)const;

// Methods
    /**
    * \brief Searches an entire one-dimensional sorted Array 
    *        for a value using the specified Comparer function.
    *
    * \param Value The value which will searched.
    * \param Comparer The callback which will be called for 
    *                 each element of the array.
    */
    RF_Type::Size BinarySearch(const T& Value, 
        const Delegate2<RF_Type::Size(const T&, const T&)>* Comparer = 0);

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
    RF_Type::Size BinarySearch(RF_Type::Size Index, 
        RF_Type::Size Length, const T& Value, 
        const Delegate2<RF_Type::Size(const T&, const T&)>* Comparer = 0);
                
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
    Memory::AutoPointer<Array<T,MA,MO> > Clone()const;

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
    RF_Type::Bool ConstrainedCopy(
        RF_Type::Size SourceIndex,
        Array<T,MA,MO>& DestinationArray,
        RF_Type::Size DestinationIndex,
        RF_Type::Size Length);

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
    RF_Type::Bool ConstrainedCopy(
        Array<T,MA,MO>& DestinationArray, 
        RF_Type::Size Length);

    /**
    * Converts an array of one type to an array of another type.
    *
    * \param Converter A function that converts each element 
    *                  from one type to another type.
    */
    template<typename Out>
    Memory::AutoPointer<Array<Out> > ConvertAll(
        const Delegate1<Out(T&)>& Converter);

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
    void Copy(Array<T,MA,MO>& DestinationArray, 
        RF_Type::Size Length);

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
    void Copy(RF_Type::Size Index, 
        Array<T,MA,MO>& DestinationArray,
        RF_Type::Size DestinationIndex, 
        RF_Type::Size Length);

    /**
    * \brief Determines whether the specified array contains 
    *        elements that match the conditions defined by the
    *        specified Match.
    *
    * \param Match The function that defines the conditions of
    *              the elements to search for.
    */
    RF_Type::Bool Exists(const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Searches for an element that matches the conditions 
    *        defined by the specified Match, and returns the 
    *        first occurrence within the entire Array.
    *
    * \param Match The function that defines the conditions of 
    *              the element to search for.
    */
    T* Find(const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Retrieves all the elements that match the conditions 
    *        defined by the specified predicate.
    *
    * \param Match The function that defines the conditions of
    *              the elements to search for.
    */
    Memory::AutoPointer<Array<T,MA,MO> > FindAll(
        const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Searches for an element that matches the conditions 
    *        defined by the specified Match, and returns the 
    *        zero-based index of the first occurrence within 
    *        the entire Array.
    *
    * \param Match The function that defines the conditions of
    *              the element to search for.
    */
    RF_Type::Size FindIndex(
        const Delegate1<RF_Type::Bool(const T&)>& Match);

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
    RF_Type::Size FindIndex(RF_Type::Size StartIndex,
        const Delegate1<RF_Type::Bool(const T&)>& Match);

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
    RF_Type::Size FindIndex(RF_Type::Size StartIndex,
        RF_Type::Size Count, 
        const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Searches for an element that matches the conditions 
    *        defined by the specified predicate, and returns 
    *        the last occurrence within the entire Array.
    *
    * \param Match The function that defines the conditions of
    *              the element to search for.
    */
    T* FindLast(const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Searches for an element that matches the conditions 
    *        defined by the specified predicate, and returns the 
    *        zero-based index of the last occurrence within the
    *        entire Array.
    *
    * \param Match The function that defines the conditions of
    *              the element to search for.
    */
    RF_Type::Size FindLastIndex(
        const Delegate1<RF_Type::Bool(const T&)>& Match);

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
    RF_Type::Size FindLastIndex(
        RF_Type::Size StartIndex,
        const Delegate1<RF_Type::Bool(const T&)>& Match);

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
    RF_Type::Size FindLastIndex(
        RF_Type::Size StartIndex, RF_Type::Size Count, 
        const Delegate1<RF_Type::Bool(const T&)>& Match);

    /**
    * \brief Performs the specified action for each element of 
    *        the specified array and pass the element as parameter.
    *
    * \param Action The function to perform on each element of array.
    */
    void ForEach(const Delegate1<void(T&)>& Action);
            

    /**
    * \brief Performs the specified action for each element of 
    *        the specified array and pass the element and
    *        Param as parameters.
    *
    * \param Action The function to perform on each element of array.
    * \param Param A value which will be passed additionally to the Action.
    */
    template<typename X>
    void ForEach(const Delegate2<void(T&,X)>& Action,X Param);

    /**
    * Returns an IEnumerator for the Array.
    */
    ArrayEnumerator<T> GetArrayEnumerator()const;

    /**
    * Returns an Enumerator for the Array.
    */
    EnumeratorType GetEnumerator()const;

    /**
    * Returns an Enumerator for the Array.
    */
    ConstEnumeratorType GetConstEnumerator()const;

    /**
    * \brief Gets a system depended type that represents the
    *        number of elements in the specified dimension of 
    *        the Array.
    *
    * \param Dimension A system depend size that represents 
    *                  the number of elements in the specified 
    *                  dimension.
    */
    RF_Type::Size GetLength(RF_Type::Size Dimension);

    /**
    * \brief Gets the value at the specified position in the 
    *        one-dimensional Array.
    *
    * \param Index An Array of 32-bit unsigned integer indices.
    */
    const T& GetValue(Array<RF_Type::Size>& Index);

    /**
    * \brief Gets the value at the specified position in the 
    *        one-dimensional Array.
    *
    * \param Index A 32-bit unsigned integer that represents 
    *              the position of the Array element to get.
    */
    const T& GetValue(RF_Type::Size Index);

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
    const T& GetValue(RF_Type::Size Index1,
                        RF_Type::Size Index2);

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
    const T& GetValue(RF_Type::Size Index1,
                        RF_Type::Size Index2,
                        RF_Type::Size Index3);

    /**
    * \brief Searches for the specified object and returns the
    *        index of the first occurrence within the entire Array.
    *
    * \param Value The object to locate in array.
    * \return The zero-based index of the first occurrence of 
    *         value within the entire array, if found; 
    *         otherwise, –1.
    */
    RF_Type::Size IndexOf(const T& Value);

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
    *         otherwise, –1.
    */
    RF_Type::Size IndexOf(const T& Value, 
        const RF_Type::Size StartIndex);

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
    *         otherwise, –1.
    */
    RF_Type::Size IndexOf(const T& Value, 
        const RF_Type::Size StartIndex,
        const RF_Type::Size Count);
                    
    /**
    * \brief Searches for the specified object and returns the 
    *        index of the last occurrence within the entire Array.
    *
    * \param Value The object to locate in array.
    * \return The zero-based index of the last occurrence of 
    *         value within the range of elements in array that 
    *         contains the number of elements specified in count 
    *         and ends at startIndex, if found; otherwise, –1.
    */
    RF_Type::Size LastIndexOf(const T& Value);

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
    *         and ends at startIndex, if found; otherwise, –1.
    */
    RF_Type::Size LastIndexOf(const T& Value, 
        const RF_Type::Size StartIndex);

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
    *         and ends at startIndex, if found; otherwise, –1.
    */
    RF_Type::Size LastIndexOf(const T& Value, 
        const RF_Type::Size StartIndex,
        const RF_Type::Size Count);

    /**
    * \brief Changes the number of elements of an array to the 
    *        specified new size.
    *
    * \param NewSize The size of the new array.
    */
    void Resize(RF_Type::Size NewSize);

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
    void Reverse(RF_Type::Size Index, 
        RF_Type::Size Length);

    /**
    * \brief Sets a value to the element at the specified 
    *        position in the one-dimensional Array. The index 
    *        is specified as a system depended type.
    *
    * \param Value The new value for the specified element.
    * \param Index A system depended type that represents 
    *              the position of the Array element to set.
    */
    void SetValue(const T& Value, RF_Type::Size Index);

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
        Array<RF_Type::Size>& Indices);

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
    void SetValue(const T& Value, RF_Type::Size Index1,
        RF_Type::Size Index);

                    
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
    void SetValue(const T& Value, RF_Type::Size Index1,
        RF_Type::Size Index2, RF_Type::Size Index3);

    /**
    * \brief Sorts the elements in an Array using the specified 
    *        Comparer method.
    *
    * \param Comparer The method which will be called for each
    *                 element of the Array.
    */
    void Sort(const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer);

    /**
    * \brief Sorts the elements in a range of elements in an 
    *        Array using the specified Comparer method.
    *
    * \param Index The starting index of the range to sort.
    * \param Length The number of elements in the range to sort.
    * \param Comparer The method which will be called for each
    *                 element of the Array.
    */
    void Sort(RF_Type::Size Index, RF_Type::Size LastIndex,
        const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer);

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
    static void Sort(Array<TKey,MA,MO>& Keys, Array<TValue,MA,MO>& Items,
        const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer);

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
    static void Sort(Array<TKey,MA,MO>& Keys, Array<TValue,MA,MO>& Items,
                     RF_Type::Size Index, RF_Type::Size LastIndex,
                     const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer);

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
    RF_Type::Bool TrueForAll(
        const Delegate1<RF_Type::Bool(const T&)>& Match);

    void Swap(Array<T,MA,MO>& Other);
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
    Array<T,MA,MO>& operator=(
        const Array<T,MA,MO>& Other);

    T& operator()(const RF_Type::Size Index);
                    
    const T& operator()(const RF_Type::Size Index)const;

    T& operator()(const RF_Type::Size Index1,
                    const RF_Type::Size Index2);
                    
    const T& operator()(const RF_Type::Size Index1,
                        const RF_Type::Size Index2)const;

    T& operator()(const RF_Type::Size Index1,
                    const RF_Type::Size Index2,
                    const RF_Type::Size Index3);

    const T& operator()(const RF_Type::Size Index1,
                        const RF_Type::Size Index2,
                        const RF_Type::Size Index3)const;

    void Exchange(const RF_Type::Size IndexA, const RF_Type::Size IndexB);
protected:
    RF_Type::Size* m_Length;
    RF_Type::Size m_Rank;
    T* m_Data;
    RF_Type::Size m_ElementCount;

// helper functions
    /// setup the data part of the class
    RF_Type::Bool InitArray(RF_Type::Size Rank, 
        const RF_Type::Size* LengthArray);
};

template<typename T, typename MA, typename MO>
inline void Array<T, MA, MO>::Exchange( 
    const RF_Type::Size IndexA, const RF_Type::Size IndexB )
{
    T swap = m_Data[IndexA];
    m_Data[IndexA] = m_Data[IndexB];
    m_Data[IndexB] = swap;
}

// Constructor & Destructor

template<typename T, typename MA, typename MO>
Array<T,MA,MO>::Array()
{
    InitArray(0,0);
}

template<typename T, typename MA, typename MO>
Array<T,MA,MO>::Array(const Array<T,MA,MO>& Copy)
{
    *this=Copy;
}

template<typename T, typename MA, typename MO>
Array<T, MA, MO>::Array(Array<T, MA, MO>&& Move)
{
    InitArray(0,0);
    Swap(Move);
}

template<typename T, typename MA, typename MO>
Array<T,MA,MO>::Array(const RF_Type::Size Length1)
{
    InitArray(1,&Length1);
}

template<typename T, typename MA, typename MO>
Array<T,MA,MO>::Array(const RF_Type::Size Length1,
    const RF_Type::Size Length2)
{
    RF_Type::Size arr[2];
    arr[0]=Length1;arr[1]=Length2;
    InitArray(2,arr);
}

template<typename T, typename MA, typename MO>
Array<T,MA,MO>::Array(const RF_Type::Size Length1,
    const RF_Type::Size Length2,
    const RF_Type::Size Length3)
{
    RF_Type::Size arr[3];
    arr[0]=Length1; arr[1]=Length2; arr[2]=Length3;
    InitArray(3,arr);
}

template<typename T, typename MA, typename MO>
Memory::AutoPointer<Array<T,MA,MO> > Array<T,MA,MO>::CreateInstance(
    const T* CArray, 
    const RF_Type::Size Length)
{
    typename Memory::AutoPointer<Array<T,MA,MO> > arr(MA::template New<Array<T,MA,MO> >());
    if (arr.Get()!=0) // out of memory check
    {
        if (arr->InitArray(1,&Length))
            MO::Copy(arr->m_Data,CArray,Length);
        else // something was going wrong, clean up
            arr.Reset();
    }
    return arr;
}

template<typename T, typename MA, typename MO>
Memory::AutoPointer<Array<T,MA,MO> > Array<T,MA,MO>::CreateInstance(
    const Array<RF_Type::Size>& Lengths)
{
    typename Memory::AutoPointer<Array<T,MA,MO> > arr(MA::template New<Array>());
    if (arr.Get()!=0) // out of memory check
        if (false==arr->InitArray(Lengths.m_ElementCount, Lengths.m_Data))
        {// something was going wrong, clean up
            arr.Reset();
        }                                            
    return arr;
}
            
template<typename T, typename MA,typename MO>
Array<T,MA,MO>::~Array()
{
    if (m_Data!=0)
    {
        MA::FreeArray(m_Data);
        m_Data=0;
    }
}

// Properties

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::Count()const
{
    return m_ElementCount;
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::Rank()const
{
    return m_Rank;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::IsFixedSize()const
{
    return true;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::IsReadOnly()const
{
    return false;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Item(RF_Type::Size Index, const T& Value)
{
    Assert(m_Rank>0,"Try to access an item on an empty array.");
    Assert(m_ElementCount>Index,"Index out of bound.");
    m_Data[Index]=Value;
}

template<typename T, typename MA, typename MO>
T& Array<T,MA,MO>::Item(RF_Type::Size Index)const
{   
    Assert(m_Rank>0,"Try to access an item on an empty array.");
    Assert(m_ElementCount>Index,"Index out of bound.");
    return m_Data[Index];
}

// Methods

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::BinarySearch(const T& Value, 
    const Delegate2<RF_Type::Size(const T&, const T&)>* Comparer)
{
    return BinarySearch(0,m_ElementCount,Value,Comparer);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::BinarySearch(
    RF_Type::Size Index, RF_Type::Size Length, const T& Value, 
    const Delegate2<RF_Type::Size(const T&, const T&)>* Comparer)
{
    RF_Type::Size left=Index,right=Index+Length-1,middle;
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

template<typename T, typename MA, typename MO>
Memory::AutoPointer<Array<T,MA,MO> > Array<T,MA,MO>::Clone()const
{
    Array<RF_Type::Size,MA,MO> lengths(m_Rank);
    for (RF_Type::Size i=0;i<m_Rank;++i)
        lengths.m_Data[i]=m_Length[i];
    Memory::AutoPointer<Array> result=Array::CreateInstance(lengths);
    MO::Copy(result->m_Data,m_Data,m_ElementCount);
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::ConstrainedCopy(RF_Type::Size SourceIndex,
    Array<T,MA,MO>& DestinationArray,
    RF_Type::Size DestinationIndex,
    RF_Type::Size Length)
{
    if (m_Rank!=DestinationArray.m_Rank)
        return false;
    if (m_ElementCount<SourceIndex+Length)
        return false;
    if (DestinationArray.m_ElementCount<DestinationIndex+Length)
        return false;
    for (RF_Type::Size i=0;i<m_Rank;++i)
        if (m_Length[i]!=DestinationArray.m_Length[i])
            return false;
    MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[SourceIndex],Length);
    return true;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::ConstrainedCopy(
    Array<T,MA,MO>& DestinationArray, 
    RF_Type::Size Length)
{
    return ConstrainedCopy(0,DestinationArray,0,Length);
}

template<typename T, typename MA, typename MO>
template<typename Out>
Memory::AutoPointer<Array<Out> > Array<T,MA,MO>::ConvertAll(
    const Delegate1<Out(T&)>& Converter)
{
    Array<RF_Type::Size,MA,MO> lengths(m_Rank);
    for (RF_Type::Size i=0;i<m_Rank;++i)
        lengths.m_Data[i]=m_Length[i];

    Memory::AutoPointer<Array<Out,MA,MO> > result=Array<Out,MA,MO>::CreateInstance(lengths);
    for (RF_Type::Size i=0;i<m_ElementCount;++i)
        result->m_Data[i]=Converter(m_Data[i]);

    return result;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Copy(Array<T,MA,MO>& DestinationArray, 
    RF_Type::Size Length)
{
    Copy(0,DestinationArray,0,Length);
}
            
template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Copy(RF_Type::Size Index, 
    Array<T,MA,MO>& DestinationArray,
    RF_Type::Size DestinationIndex, 
    RF_Type::Size Length)
{
    Assert(m_Rank==DestinationArray.m_Rank,"Try to copy one array to an other with different dimensions.");
    Assert(m_ElementCount>=Index+Length,"Operation leave the memory bound of source array.");
    Assert(DestinationArray.m_ElementCount>=DestinationIndex+Length,"Operation leave the memory bound of the destination array.");
    MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[Index],Length);
}
            
template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::Exists(
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    RF_Type::Size end=m_ElementCount-1;
    for (RF_Type::Size i=0;i<end;++i)
        if (Match(m_Data[i]))
            return true;
    return false;
}

template<typename T, typename MA, typename MO>
T* Array<T,MA,MO>::Find(const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    RF_Type::Size end=m_ElementCount-1;
    for (RF_Type::Size i=0;i<end;++i)
        if (Match(m_Data[i]))
            return &m_Data[i];
    return 0;
}

template<typename T, typename MA, typename MO>
T* Array<T,MA,MO>::FindLast(const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    RF_Type::Size end=m_ElementCount-1;
    for (RF_Type::Size i=end; i <= end;--i)
        if (Match(m_Data[i]))
            return &m_Data[i];
    return 0;
}

template<typename T, typename MA, typename MO>
Memory::AutoPointer<Array<T,MA,MO> > Array<T,MA,MO>::FindAll(
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Memory::AutoPointer<Array<T,MA,MO> > result;
    // reserve memory with the size of pow
    RF_Type::Size reserved=2;
    RF_Type::Size size=0;
    T* arr=MA::template NewArray<T>(reserved);

    for (RF_Type::Size i=0;i<m_ElementCount;++i)
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
    result=Memory::AutoPointer<Array<T,MA,MO> >(new Array<T,MA,MO>(size));
    MO::Copy(result->m_Data,arr,size);
    MA::FreeArray(arr);
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindIndex(
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return FindIndex(0,m_Length[0],Match);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindIndex(
    RF_Type::Size StartIndex,
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return FindIndex(StartIndex,m_Length[0]-StartIndex,Match);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindIndex(
    RF_Type::Size StartIndex,
    RF_Type::Size Count, 
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    RF_Type::Size end=StartIndex+Count;
    for (RF_Type::Size i=StartIndex;i<end;++i)
        if (Match(m_Data[i]))
            return i;
    return -1;
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindLastIndex(
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return FindLastIndex(m_Length[0]-1,m_Length[0],Match);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindLastIndex(
    RF_Type::Size StartIndex,
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return FindLastIndex(StartIndex,m_Length[0]-StartIndex,Match);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::FindLastIndex(
    RF_Type::Size StartIndex, RF_Type::Size Count, 
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    RF_Type::Int32 end = StartIndex - (Count - 1);
    for (RF_Type::Int32 i = StartIndex; i >= end; --i)
    {
        if (Match(m_Data[i]))
        {
            return i;
        }
    }
    return -1;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::ForEach(const Delegate1<void(T&)>& Action)
{
    for (RF_Type::Size i=0;i<m_ElementCount;++i)
        Action(m_Data[i]);
}

template<typename T, typename MA, typename MO>
template<typename X>
void Array<T,MA,MO>::ForEach(const Delegate2<void(T&,X)>& Action, X Param)
{
    for (RF_Type::Size i=0;i<m_ElementCount;++i)
        Action(m_Data[i],Param);
}
             
template<typename T, typename MA, typename MO>
ArrayEnumerator<T> Array<T,MA,MO>::GetArrayEnumerator()const
{
    ArrayEnumerator<T> result(m_Data, &m_Data[m_ElementCount - 1]);
    return result;
}

template<typename T, typename MA, typename MO>
typename Array<T, MA, MO>::EnumeratorType Array<T, MA, MO>::GetEnumerator()const
{
    EnumeratorType result;
    result.m_Start = m_Data;
    result.m_Current = m_Data;
    result.m_Elements = m_ElementCount;
    return result;
}

template<typename T, typename MA, typename MO>
typename Array<T, MA, MO>::ConstEnumeratorType Array<T, MA, MO>::GetConstEnumerator()const
{
    ConstEnumeratorType result;
    result.m_Start = m_Data;
    result.m_Current = m_Data;
    result.m_Elements = m_ElementCount;
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::GetLength(
    RF_Type::Size Dimension)
{
    Assert(Dimension<m_Rank,"Dimension is out bound.");
    return m_Length[Dimension];
}
                   
template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::GetValue(RF_Type::Size Index)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    Assert(Index<m_Length[0],"Index out of bound.");
    return m_Data[Index];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::GetValue(RF_Type::Size Index1,
                                        RF_Type::Size Index2)
{
    Assert(m_Rank==2,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    return m_Data[(Index1*m_Length[1])+Index2];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::GetValue(RF_Type::Size Index1,
                                        RF_Type::Size Index2,
                                        RF_Type::Size Index3)
{
    Assert(m_Rank==3,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    Assert(Index3<m_Length[2],"Index out of bound.");
    return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::GetValue(Array<RF_Type::Size>& Index)
{
    RF_Type::Size index=0;
    RF_Type::Size i=0;
    for (;i<Index.Count()-1;++i)
    {
        index+=m_Length[i]*Index.m_Data[i];
        Assert(index<m_ElementCount,"Index out of bound.");
    }
    index+=Index.m_Data[i];
    Assert(index<m_ElementCount,"Index out of bound.");
    return m_Data[index];
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::IndexOf(const T& Value)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return IndexOf(Value,0,m_Length[0]);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::IndexOf(const T& Value,
    const RF_Type::Size StartIndex)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return IndexOf(Value,StartIndex,m_Length[0]-StartIndex);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::IndexOf(const T& Value,
    const RF_Type::Size StartIndex, 
    const RF_Type::Size Count)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    RF_Type::Size end=StartIndex+Count;
    Assert(end>=0,"Operation out of bound.");
    for (RF_Type::Size i=StartIndex;i<end;++i)
        if (m_Data[i]==Value)
            return i;
    return -1;
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::LastIndexOf(const T& Value)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return LastIndexOf(Value,m_Length[0]-1,m_Length[0]);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::LastIndexOf(const T& Value, 
    const RF_Type::Size StartIndex)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    return LastIndexOf(Value,StartIndex,m_Length[0]-StartIndex);
}

template<typename T, typename MA, typename MO>
RF_Type::Size Array<T,MA,MO>::LastIndexOf(
    const T& Value, const RF_Type::Size StartIndex,
    const RF_Type::Size Count)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    RF_Type::Int32 end=StartIndex-(Count-1);
    Assert(end>=0,"Operation out of bound.");
    for (RF_Type::Int32 i = StartIndex; i >= end; --i)
    {
        if (m_Data[i]==Value)
        {
            return i;
        }
    }
    return -1;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Resize(RF_Type::Size NewSize)
{
    if(m_Rank == 0)
    {
        InitArray(1, &NewSize);
    }

    Assert(m_Rank == 1, "Unexpected dimension of array.");

    if(NewSize != m_Length[0])
    {
        T* data = MA::template NewArray<T>(NewSize);
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        if(std::is_trivially_copyable<T>::value == false)
        {
        #endif
            for(RF_Type::Size i = 0, end = RF_Math::Integer<RF_Type::Size>::Min(m_Length[0], NewSize); i < end; ++i)
            {
                data[i] = m_Data[i];
            }
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        }
        else
        {
            MO::Copy(data, m_Data, RF_Math::Integer<RF_Type::Size>::Min(m_Length[0], NewSize));
        }
        #endif
        MA::FreeArray(m_Data);
        m_Data = data;
        m_Length[0] = NewSize;
        m_ElementCount = NewSize;
    }
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Reverse()
{
    Reverse(0,m_ElementCount);
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Reverse(RF_Type::Size Index, 
    RF_Type::Size Length)
{
    Assert(Index+Length<=m_ElementCount,"Operation out of bound.");
    RF_Type::Size end=Index+Length-1;
    RF_Type::Size halfEnd=Index + (Length >> 1);
    T* tmp=MA::template New<T>();
    for (RF_Type::Size i=Index; i<halfEnd; ++i)
    {
        MO::Copy(tmp,&m_Data[i],1);
        MO::Move(&m_Data[i],&m_Data[end-i],1);
        MO::Copy(&m_Data[end-i],tmp,1);
    }
    MA::Free(tmp);
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::SetValue(const T& Value, RF_Type::Size Index)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    Assert(Index<m_ElementCount,"Index out of bound.");
    m_Data[Index]=Value;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::SetValue(const T& Value, RF_Type::Size Index1,
    RF_Type::Size Index2)
{
    Assert(m_Rank==2,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    m_Data[(Index1*m_Length[1])+Index2]=Value;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::SetValue(const T& Value, RF_Type::Size Index1,
    RF_Type::Size Index2,
    RF_Type::Size Index3)
{
    Assert(m_Rank==3,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    Assert(Index3<m_Length[2],"Index out of bound.");
    m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3]=Value;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::SetValue(const T& Value, 
    Array<RF_Type::Size>& Indices)
{
    Assert(m_Rank==Indices.Count(),"Unexpected dimension of array.");
    RF_Type::Size index=0;
    RF_Type::Size i=0;
    for (;i<Indices.Count()-1;++i)
    {
        index+=m_Length[i]*Indices.m_Data[i];
        Assert(index<m_ElementCount,"Index out of bound.");
    }
    index+=Indices.m_Data[i];
    Assert(index<m_ElementCount,"Index out of bound.");
    m_Data[index]=Value;
}

template<typename T, typename MA, typename MO>
void Array<T, MA, MO>::Sort(const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer)
{
    Sort(0,m_ElementCount-1,Comparer);
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Sort(RF_Type::Size Index, 
    RF_Type::Size LastIndex,
    const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer)
{
    Assert(LastIndex < m_ElementCount,"Index out of bound.");
    if (LastIndex <= Index)
        return;

    T swap;

    T pivot1 = m_Data[Index];
    T pivot2 = m_Data[LastIndex];

    if (Comparer(pivot1,pivot2) > 0)
    {
        Exchange(Index, LastIndex);
        pivot1 = m_Data[Index];
        pivot2 = m_Data[LastIndex];
    }
    else
    {
        if (Comparer(pivot1,pivot2) == 0)
        {
            while(Comparer(pivot1,pivot2) == 0 && Index<LastIndex)
            {
                ++Index;
                pivot1 = m_Data[Index];
            }
        }
    }

    RF_Type::Size i = Index + 1;
    RF_Type::Size lt = Index + 1;
    RF_Type::Size gt = LastIndex - 1;

    while(i <= gt)
    {
        if (Comparer(m_Data[i], pivot1) < 0)
        {
            Exchange(i++, lt++);
        }
        else
        {
            if (Comparer(pivot2, m_Data[i]) < 0)
            {
                Exchange(i, gt--);
            }
            else
            {
                ++i;
            }
        }
    }

    Exchange(Index, --lt);
    Exchange(LastIndex, ++gt);

    if (lt > 0)
        Sort(Index, lt-1, Comparer);
    if (gt > 0)
        Sort(lt+1,gt-1, Comparer);
    Sort(gt+1, LastIndex, Comparer);
}

template<typename T, typename MA, typename MO>
template<typename TKey, typename TValue>
void Array<T,MA,MO>::Sort(Array<TKey,MA,MO>& Keys, 
    Array<TValue,MA,MO>& Items,
    const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer)
{
    Sort(Keys,Items,0,Keys.m_ElementCount-1,Comparer);
}

template<typename T, typename MA, typename MO>
template <typename TKey, typename TValue>
void Array<T,MA,MO>::Sort(Array<TKey,MA,MO>& Keys,
    Array<TValue,MA,MO>& Items, RF_Type::Size Index, RF_Type::Size LastIndex,
    const Delegate2<RF_Type::Size(const T&, const T&)>& Comparer)
{
    Assert(Keys.m_ElementCount==Items.m_ElementCount,"Invalid parameter.");
    Assert(LastIndex<Keys.m_ElementCount,"Index out of bound.");

    if (LastIndex <= Index)
        return;

    T swap;

    T pivot1 = Items.Item(Index);
    T pivot2 = Items.Item(LastIndex);

    if (Comparer(pivot1, pivot2) > 0)
    {
        Items.Exchange(Index, LastIndex);
        Keys.Exchange(Index, LastIndex);
        pivot1 = Items.Item(Index);
        pivot2 = Items.Item(LastIndex);
    }
    else
    {
        if (Comparer(pivot1, pivot2) == 0)
        {
            while(Comparer(pivot1, pivot2) == 0 && Index < LastIndex)
            {
                ++Index;
                pivot1 = Items.Item(Index);
            }
        }
    }

    RF_Type::Size i = Index + 1;
    RF_Type::Size lt = Index + 1;
    RF_Type::Size gt = LastIndex - 1;

    while(i <= gt)
    {
        if (Comparer(Items.Item(i), pivot1) < 0)
        {
            Keys.Exchange(i, lt);
            Items.Exchange(i++, lt++);
        }
        else
        {
            if (Comparer(pivot2, Items.Item(i)) < 0)
            {
                Keys.Exchange(i, gt);
                Items.Exchange(i, gt--);
            }
            else
            {
                ++i;
            }
        }
    }

    Items.Exchange(Index, --lt);
    Keys.Exchange(Index, lt);
    Items.Exchange(LastIndex, ++gt);
    Keys.Exchange(LastIndex, gt);

    if (lt > 0)
        Sort(Keys, Items, Index, lt-1, Comparer);
    if (gt > 0)
        Sort(Keys, Items, lt+1,gt-1, Comparer);
    Sort(Keys, Items, gt+1, LastIndex, Comparer);
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::TrueForAll(
    const Delegate1<RF_Type::Bool(const T&)>& Match)
{
    for (RF_Type::Size i=0;i<m_ElementCount;++i)
        if (false==Match(m_Data[i]))
            return false;
    return true;
}

template<typename T, typename MA, typename MO>
void Array<T,MA,MO>::Swap(Array<T,MA,MO>& Other)
{
    T* tmpData=m_Data;
    m_Data=Other.m_Data;
    Other.m_Data=tmpData;

    RF_Type::Size tmpCount=m_ElementCount;
    m_ElementCount=Other.m_ElementCount;
    Other.m_ElementCount=tmpCount;

    RF_Type::Size* tmpLen=m_Length;
    m_Length=Other.m_Length;
    Other.m_Length=tmpLen;

    RF_Type::Size tmpRank=m_Rank;
    m_Rank=Other.m_Rank;
    Other.m_Rank=tmpRank;
}

// Operators
template<typename T, typename MA, typename MO>
Array<T,MA,MO>& Array<T,MA,MO>::operator=(const Array<T,MA,MO>& Other)
{
    InitArray(Other.m_Rank,Other.m_Length);
    for (RF_Type::Size i=0;i<m_ElementCount;++i)
        m_Data[i]=Other.m_Data[i];
    return *this;
}

template<typename T, typename MA, typename MO>
T& Array<T,MA,MO>::operator()(const RF_Type::Size Index)
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    Assert(Index<m_Length[0],"Index out of bound.");                
    return m_Data[Index];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::operator()(const RF_Type::Size Index)const
{
    Assert(m_Rank==1,"Unexpected dimension of array.");
    Assert(Index<m_Length[0],"Index out of bound.");
    return m_Data[Index];
}

template<typename T, typename MA, typename MO>
T& Array<T,MA,MO>::operator()(const RF_Type::Size Index1,
                            const RF_Type::Size Index2)
{
    Assert(m_Rank==2,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    return m_Data[(Index1*m_Length[1])+Index2];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::operator()(const RF_Type::Size Index1,
                                    const RF_Type::Size Index2)const
{
    Assert(m_Rank==2,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    return m_Data[(Index1*m_Length[1])+Index2];
}

template<typename T, typename MA, typename MO>
T& Array<T,MA,MO>::operator()(const RF_Type::Size Index1,
                            const RF_Type::Size Index2,
                            const RF_Type::Size Index3)
{
    Assert(m_Rank==3,"Unexpected dimension of array");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    Assert(Index3<m_Length[2],"Index out of bound.");
    return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
}

template<typename T, typename MA, typename MO>
const T& Array<T,MA,MO>::operator()(
    const RF_Type::Size Index1,
    const RF_Type::Size Index2,
    const RF_Type::Size Index3)const
{
    Assert(m_Rank==3,"Unexpected dimension of array.");
    Assert(Index1<m_Length[0],"Index out of bound.");
    Assert(Index2<m_Length[1],"Index out of bound.");
    Assert(Index3<m_Length[2],"Index out of bound.");
    return m_Data[((Index1*m_Length[1]*m_Length[2])+Index2*m_Length[2])+Index3];
}

// internal helper functions

template<typename T, typename MA, typename MO>
RF_Type::Bool Array<T,MA,MO>::InitArray(
    RF_Type::Size Rank, 
    const RF_Type::Size* LengthArray)
{
    m_Rank=Rank;
    m_Data=0;
    m_Length=0;
    m_ElementCount=0;

    if (Rank>0)
    {
        m_Length=MA::template NewArray<RF_Type::Size>(Rank);

        if (m_Length==0)
            return false;

        RF_Type::Size len;
        for (RF_Type::Size i=0;i<Rank;++i)
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

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_ARRAY_HPP