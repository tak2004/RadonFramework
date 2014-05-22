#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/Array.hpp>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class ArrayTest:public TestSuite
{
    public:
        ArrayTest()
            :TestSuite("RadonFramework::Collections::Array-Test")
        {
            AddTest(MakeDelegate(this,&ArrayTest::Constructor),
                "Constructor");

            AddTest(MakeDelegate(this,&ArrayTest::CopyConstructor),
                "Copy constructor");

            AddTest(MakeDelegate(this,&ArrayTest::Constructor1Dimension),
                "Constructor which create a 1 dimensional array.");

            AddTest(MakeDelegate(this,&ArrayTest::Constructor2Dimension),
                "Constructor which create a 2 dimensional array.");

            AddTest(MakeDelegate(this,&ArrayTest::Constructor3Dimension),
                "Constructor which create a 3 dimensional array.");

            AddTest(MakeDelegate(this,&ArrayTest::ConstructorMultiDimension),
                "Constructor which create a multi dimensional array.");
            
            AddTest(MakeDelegate(this,&ArrayTest::Constructor1DimensionC),
                "Constructor which copy from a 1 dimensional c array.");

            AddTest(MakeDelegate(this,&ArrayTest::ItemGet),
                "Get the item of a specific index.");

            AddTest(MakeDelegate(this,&ArrayTest::ItemSet),
                "Set the value of a specific item.");

            AddTest(MakeDelegate(this,&ArrayTest::BinarySearch),
                "Search a value in the array with binary search algorithm.");

            AddTest(MakeDelegate(this,&ArrayTest::SortComparer),
                "Sort the elements of the array by a comparer.");

            AddTest(MakeDelegate(this,&ArrayTest::SortArraysComparer),
                "Sort the elements of two coupled arrays by a comparer.");

            AddTest(MakeDelegate(this,&ArrayTest::TrueForAll),
                "Go through all elements of the array and execute a user \
                defined match algorithm.");

            AddTest(MakeDelegate(this,&ArrayTest::FunctionOperatorAccess1D),
                "Access an element of the array by the function operator.");

            AddTest(MakeDelegate(this,&ArrayTest::FunctionOperatorAccess2D),
                "Access an element of the 2 dimensional array by the function operator.");

            AddTest(MakeDelegate(this,&ArrayTest::FunctionOperatorAccess3D),
                "Access an element of the 3 dimensional array by the function operator.");

            AddTest(MakeDelegate(this,&ArrayTest::SetValue1D),
                "Set the value of an element of the 1D array.");

            AddTest(MakeDelegate(this,&ArrayTest::SetValue2D),
                "Set the value of an element of the 2D array.");

            AddTest(MakeDelegate(this,&ArrayTest::SetValue3D),
                "Set the value of an element of the 3D array.");

            AddTest(MakeDelegate(this,&ArrayTest::SetValueVariableDimension),
                "Set the value of an element of a multi dimension array.");

            AddTest(MakeDelegate(this,&ArrayTest::GetLength),
                "Return the number of elements in the specified dimension of the array.");

            AddTest(MakeDelegate(this,&ArrayTest::GetValue1D),
                "Get the value of an element of the 1D array.");

            AddTest(MakeDelegate(this,&ArrayTest::GetValue2D),
                "Get the value of an element of the 2D array.");

            AddTest(MakeDelegate(this,&ArrayTest::GetValue3D),
                "Get the value of an element of the 3D array.");

            AddTest(MakeDelegate(this,&ArrayTest::GetValueVariableDimension),
                "Get the value of an element of a multi dimension array.");

            AddTest(MakeDelegate(this,&ArrayTest::Reverse),
                "Reverses the sequence of the elements in the entire 1D Array.");

            AddTest(MakeDelegate(this,&ArrayTest::Resize),
                "Changes the number of elements of an array to the specified new size.");

            AddTest(MakeDelegate(this,&ArrayTest::LastIndexOf),
                "Searches for the specified object and returns the index of \
                the last occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::IndexOf),
                "Searches for the specified object and returns the index of \
                the first occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::GetEnumerator),
                "Returns an IEnumerator for the Array.");

            AddTest(MakeDelegate(this,&ArrayTest::ForEach),
                "Execute a method for each element of the array");

            AddTest(MakeDelegate(this,&ArrayTest::FindLastIndex),
                "Searches for the element which pass the method and returns \
                the index of the last occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::FindIndex),
                "Searches for the element which pass the method and returns \
                the index of the first occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::FindLast),
                "Searches for the element which pass the method and returns \
                the index of the last occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::Find),
                "Searches for the element which pass the method and returns \
                the index of the first occurrence.");

            AddTest(MakeDelegate(this,&ArrayTest::FindAll),
                "Retrieves all the elements that match the conditions defined \
                by the specified predicate.");

            AddTest(MakeDelegate(this,&ArrayTest::Exists),
                "Determines whether the specified array contains elements that \
                match the conditions defined by the specified predicate.");

            AddTest(MakeDelegate(this,&ArrayTest::Copy),
                "Copies a range of elements from an Array to an other.");

            AddTest(MakeDelegate(this,&ArrayTest::ConvertAll),
                "Converts an array of one type to an array of another type.");

            AddTest(MakeDelegate(this,&ArrayTest::ConstrainedCopy),
                "Copies a range of elements from an Array to an other if the \
                Arrays have the same structure.");

            AddTest(MakeDelegate(this,&ArrayTest::Clone),
                "Creates a shallow copy of the Array.");
        }

        Bool Constructor()
        {
            Array<UInt32> m_Array;
            return (0==m_Array.Count());
        }

        Bool CopyConstructor()
        {
            Array<UInt32> array1(1);
            Array<UInt32> array2(array1);
            return (1==array1.Count() && 1==array2.Count());
        }

        Bool Constructor1Dimension()
        {
            Array<UInt32> array(1);
            return (1==array.Count());
        }

        Bool Constructor2Dimension()
        {
            Array<UInt32> matrix(4,4);
            return (16==matrix.Count() && 2==matrix.Rank());
        }

        Bool Constructor3Dimension()
        {
            Array<UInt32> volume(4,4,4);
            return (64==volume.Count() && 3==volume.Rank());
        }

        Bool ConstructorMultiDimension()
        {
            AutoPointer<Array<UInt32> > array;
            Array<Size> arrayLen(3);
            arrayLen(0)=1; arrayLen(1)=2; arrayLen(2)=3;
            array=Array<UInt32>::CreateInstance(arrayLen);            
            return (array && 6==array->Count() && 3==array->Rank());
        }

        Bool Constructor1DimensionC()
        {
            AutoPointer<Array<UInt32> > m_Array;
            // test stack allocation
            UInt32 cArray[3]={1,2,3};
            m_Array=Array<UInt32>::CreateInstance(cArray,3);
            return (m_Array);
        }

        Bool ItemGet()
        {
            Array<UInt32> matrix(4,4);
            return matrix.Item(0) && matrix.Item(15);
        }

        Bool ItemSet()
        {
            Array<UInt32> matrix(4,4);
            matrix.Item(0,1);
            matrix.Item(15,1);
            return 1==matrix.Item(0) && 1==matrix.Item(15);
        }

        Bool BinarySearch()
        {
            Array<Int32> matrix(4,4);

            //this test a sorted list with an existing value
            for (Size i=0;i<matrix.Count();++i)
                matrix.Item(i, static_cast<Int32>(i));
            Size index=matrix.BinarySearch(6);// case 1
            
            //this cases test all possible negative answers of an sorted list
            for (Size i=0;i<matrix.Count();++i)
                matrix.Item(i,static_cast<Int32>(i*2));
            Size index1=~matrix.BinarySearch(5);// case 2: between 4 and 6
            Size index2=~matrix.BinarySearch(-1);// case 3: between begin and 0
            Size index3=~matrix.BinarySearch(33);// case 4: between 32 and end
            return index==6 && // case 1
                   2==(index1-1) && // case 2
                   0==index2 && // case 3
                   16==index3; // case 4                
        }

        Size Int32LargestFirst(Int32& A, Int32& B)
        {
            if (A==B)
                return 0;
            else
                if (A<B)//inverse of smallest first
                    return 1;
                else
                    return -1;
        }

        Bool SortComparer()
        {
            Array<Int32> list(16);

            //this test a sorted list with an existing value
            for (UInt32 i=0;i<list.Count();++i)
                list.Item(i,i);

            list.Sort(MakeDelegate(this,&ArrayTest::Int32LargestFirst));
            return list.Item(0)==15 &&
                   list.Item(15)==0;
        }

        Bool SortArraysComparer()
        {
            Array<Int32> keys(16);
            Array<Int32> values(16);

            //this test a sorted list with an existing value
            for (Size i=0;i<keys.Count();++i)
            {
                keys.Item(i, static_cast<Int32>(i));
                values.Item(i, static_cast<Int32>(i*3));
            }

            Array<Int32>::Sort(keys,values,MakeDelegate(this,&ArrayTest::Int32LargestFirst));
            return keys.Item(0)==15 && values.Item(0)==45 &&
                   keys.Item(15)==0 && values.Item(15)==0;
        }

        Bool OnlyEvenNumbers(UInt32 value)
        {
            return value%2==0;
        }

        Bool TrueForAll()
        {
            Array<UInt32> matrix(3,3);
            for (UInt32 i=0;i<9;++i)
                matrix.Item(i,i*2);
            return matrix.TrueForAll(MakeDelegate(this,&ArrayTest::OnlyEvenNumbers));
        }

        Bool FunctionOperatorAccess1D()
        {
            Array<UInt32> matrix(3);
            matrix.Item(0,1);
            matrix.Item(2,2);
            return 1==matrix(0) && 2==matrix(2);
        }

        Bool FunctionOperatorAccess2D()
        {
            Array<UInt32> matrix(3,3);
            matrix.Item(0,1);
            matrix.Item(4,2);
            matrix.Item(8,3);
            return 1==matrix(0,0) && 2==matrix(1,1) && 3==matrix(2,2);
        }

        Bool FunctionOperatorAccess3D()
        {
            Array<UInt32> matrix(3,3,3);
            matrix.Item(0,1);
            matrix.Item(13,2);
            matrix.Item(26,3);
            return 1==matrix(0,0,0) && 2==matrix(1,1,1) && 3==matrix(2,2,2);
        }

        Bool SetValue1D()
        {
            Array<UInt32> vector(3);
            vector.SetValue(1,0);
            vector.SetValue(2,2);
            return 1==vector(0) && 2==vector(2);
        }

        Bool SetValue2D()
        {
            Array<UInt32> matrix(3,3);
            matrix.SetValue(1,0,0);
            matrix.SetValue(2,1,1);
            matrix.SetValue(3,2,2);
            return 1==matrix(0,0) && 2==matrix(1,1) && 3==matrix(2,2);
        }

        Bool SetValue3D()
        {
            Array<UInt32> matrix(3,3,3);
            matrix.SetValue(1,0,0,0);
            matrix.SetValue(2,1,1,1);
            matrix.SetValue(3,2,2,2);
            return 1==matrix(0,0,0) && 2==matrix(1,1,1) && 3==matrix(2,2,2);
        }

        Bool SetValueVariableDimension()
        {
            Array<UInt32> matrix(3,3);
            Array<Size> indices(2);
            indices.Item(0,0);
            indices.Item(1,0);
            Array<Size> indices1(2);
            indices1.Item(0,1);
            indices1.Item(1,1);
            Array<Size> indices2(2);
            indices2.Item(0,2);
            indices2.Item(1,2);
            matrix.SetValue(1,indices);
            matrix.SetValue(2,indices1);
            matrix.SetValue(3,indices2);
            return 1==matrix(0,0) && 2==matrix(1,1) && 3==matrix(2,2);
        }

        Bool GetLength()
        {
            Array<UInt32> matrix(3,3);
            return 3==matrix.GetLength(0) && 3==matrix.GetLength(1);
        }

        Bool GetValue1D()
        {
            Array<UInt32> matrix(3);
            matrix.Item(0,1);
            matrix.Item(2,2);
            return 1==matrix.GetValue(0) && 2==matrix.GetValue(2);
        }

        Bool GetValue2D()
        {
            Array<UInt32> matrix(3,3);
            matrix.Item(0,1);
            matrix.Item(4,2);
            matrix.Item(8,3);
            return 1==matrix.GetValue(0,0) && 2==matrix.GetValue(1,1) && 
                   3==matrix.GetValue(2,2);
        }

        Bool GetValue3D()
        {
            Array<UInt32> matrix(3,3,3);
            matrix.Item(0,1);
            matrix.Item(13,2);
            matrix.Item(26,3);
            return 1==matrix.GetValue(0,0,0) && 2==matrix.GetValue(1,1,1) && 
                   3==matrix.GetValue(2,2,2);
        }

        Bool GetValueVariableDimension()
        {
            Array<UInt32> matrix(3,3);
            Array<Size> indices(2);
            indices.Item(0,0);
            indices.Item(1,0);
            Array<Size> indices1(2);
            indices1.Item(0,1);
            indices1.Item(1,1);
            Array<Size> indices2(2);
            indices2.Item(0,2);
            indices2.Item(1,2);
            matrix.SetValue(1,indices);
            matrix.SetValue(2,indices1);
            matrix.SetValue(3,indices2);
            return 1==matrix.GetValue(0,0) && 2==matrix.GetValue(1,1) && 
                   3==matrix.GetValue(2,2);
        }

        Bool Reverse()
        {
            Array<UInt32> vec1(2);
            Array<UInt32> vec2(3);
            vec1.Item(0,1);
            vec1.Item(1,2);
            vec2.Item(0,1);
            vec2.Item(1,2);
            vec2.Item(2,3);
            vec1.Reverse();
            vec2.Reverse();
            return 2==vec1.GetValue(0) && 1==vec1.GetValue(1) && 
                   3==vec2.GetValue(0) && 2==vec2.GetValue(1) &&
                   1==vec2.GetValue(2);
        }

        Bool Resize()
        {
            Array<UInt32> vec(1);
            vec.Item(0,1);
            vec.Resize(5);
            vec.Item(1,2);
            vec.Item(2,3);
            vec.Item(3,4);
            vec.Item(4,5);
            vec.Resize(3);
            return 1==vec(0) && 2==vec(1) && 3==vec(2);
        }

        Bool LastIndexOf()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            return 2==vec.LastIndexOf(3) && -1==vec.LastIndexOf(3,1,1) &&
                   -1==vec.LastIndexOf(0) && 0==vec.LastIndexOf(3,1,2) &&
                   0==vec.LastIndexOf(3,1);
        }

        Bool IndexOf()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            return 0==vec.IndexOf(3) && -1==vec.IndexOf(3,1,1) &&
                -1==vec.IndexOf(0) && 2==vec.IndexOf(3,1,2) &&
                2==vec.IndexOf(3,1);
        }

        Bool GetEnumerator()
        {
            Array<UInt32> vec(3);
            vec.Item(0,1);
            vec.Item(1,2);
            vec.Item(2,3);
            ArrayEnumerator<UInt32> enumerator=vec.GetArrayEnumerator();
            return enumerator.MoveNext() && *enumerator.Current()==1 &&
                   enumerator.MoveNext() && *enumerator.Current()==2 &&
                   enumerator.MoveNext() && *enumerator.Current()==3 &&
                   !enumerator.MoveNext() && enumerator.Current()==0;
        }

        void Increase(UInt32& Value)
        {
            ++Value;
        }

        Bool ForEach()
        {
            Array<UInt32> vec(3);
            vec.Item(0,1);
            vec.Item(1,2);
            vec.Item(2,3);
            vec.ForEach(MakeDelegate(this,&ArrayTest::Increase));
            return 2==vec(0) && 3==vec(1) && 4==vec(2);
        }

        Bool FindThree(UInt32 Value)
        {
            return Value==3;
        }

        Bool FindZero(UInt32 Value)
        {
            return Value==0;
        }

        Bool FindLastIndex()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            Delegate1<UInt32,Bool> three=MakeDelegate(this,&ArrayTest::FindThree);
            Delegate1<UInt32,Bool> zero=MakeDelegate(this,&ArrayTest::FindZero);
            return 2==vec.FindLastIndex(three) && -1==vec.FindLastIndex(1,1,three) &&
                   -1==vec.FindLastIndex(zero) && 0==vec.FindLastIndex(1,2,three) &&
                   0==vec.FindLastIndex(1,three);
        }

        Bool FindIndex()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            Delegate1<UInt32,Bool> three=MakeDelegate(this,&ArrayTest::FindThree);
            Delegate1<UInt32,Bool> zero=MakeDelegate(this,&ArrayTest::FindZero);
            return 0==vec.FindIndex(three) && -1==vec.FindIndex(1,1,three) &&
                  -1==vec.FindIndex(zero) && 2==vec.FindIndex(1,2,three) &&
                  2==vec.FindIndex(1,three);
        }

        Bool Find()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            Delegate1<UInt32,Bool> three=MakeDelegate(this,&ArrayTest::FindThree);
            Delegate1<UInt32,Bool> zero=MakeDelegate(this,&ArrayTest::FindZero);
            return 0!=vec.Find(three) && 0==vec.Find(zero);
        }

        Bool FindLast()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            Delegate1<UInt32,Bool> three=MakeDelegate(this,&ArrayTest::FindThree);
            Delegate1<UInt32,Bool> zero=MakeDelegate(this,&ArrayTest::FindZero);
            return 0!=vec.FindLast(three) && 0==vec.FindLast(zero);
        }
         
        Bool FindAll()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            AutoPointer<Array<UInt32> > results=vec.FindAll(MakeDelegate(this,&ArrayTest::FindThree));
            return results && results->Count()==2;
        }

        Bool Exists()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,3);
            Delegate1<UInt32,Bool> three=MakeDelegate(this,&ArrayTest::FindThree);
            Delegate1<UInt32,Bool> zero=MakeDelegate(this,&ArrayTest::FindZero);
            return true==vec.Exists(three) && false==vec.Exists(zero);
        }

        Bool Copy()
        {
            Array<UInt32> vec1(2);
            Array<UInt32> vec2(2);
            vec1.Item(0,1);
            vec1.Item(1,2);
            vec1.Copy(vec2,2);
            return 1==vec2(0) && 2==vec2(1);
        }

        Int32 ConvertSignSwitch(UInt32 Value)
        {
            return -static_cast<Int32>(Value);
        }

        Bool ConvertAll()
        {
            Array<UInt32> vec(3);
            vec.Item(0,3);
            vec.Item(1,2);
            vec.Item(2,1);
            AutoPointer<Array<Int32> > results=vec.ConvertAll<Int32>(MakeDelegate(this,&ArrayTest::ConvertSignSwitch));
            return results && results->Count()==3 && -3==results->Item(0) &&
                   -2==results->Item(1) && -1==results->Item(2);
        }

        Bool ConstrainedCopy()
        {
            Array<UInt32> vec1(2);
            Array<UInt32> vec2(2);
            Array<UInt32> vec3(3);
            vec1.Item(0,1);
            vec1.Item(1,2);            
            return true==vec1.ConstrainedCopy(vec2,2) && 
                   false==vec1.ConstrainedCopy(vec3,3) &&
                   1==vec2(0) && 2==vec2(1);
        }

        Bool Clone()
        {
            Array<UInt32> vec1(2);
            vec1.Item(0,1);
            vec1.Item(1,2);            
            AutoPointer<Array<UInt32> > results=vec1.Clone();
            return results && results->Count()==2 && 1==results->Item(0) &&
                   2==results->Item(1);
        }
};

ArrayTest collectionsGenericArrayTestInstance;
