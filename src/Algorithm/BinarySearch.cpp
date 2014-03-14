#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Algorithm/BinarySearch.hpp"

using namespace RadonFramework::Algorithm;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections::Generic;

Int32 BinarySearch(const AutoPointer<IEnumerator<T> >& Start,
    const AutoPointer<IEnumerator<T> >& End, const T& Value,
    const Delegate2<T&,T&,Int32>* Comparer /* =0 */)
{
    Int32 left=Index, right=Index+Length-1, middle;
    while(left<=right)
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