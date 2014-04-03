#ifndef RF_COLLECTIONS_GENERIC_IENUMERATOR_HPP
#define RF_COLLECTIONS_GENERIC_IENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        template<typename T>
        class IEnumerator
        {
            public:
                /** Gets the element in the collection at the current 
                    * position of the enumerator.
                    **/
                virtual T* Current()const=0;

                /// Advances the enumerator to the next element of the collection.
                virtual RFTYPE::Bool MoveNext()=0;

                /** Sets the enumerator to its initial position, which is 
                    * before the first element in the collection.
                    **/
                virtual void Reset()=0;
        };
    }
}

#endif // RF_COLLECTIONS_GENERIC_IENUMERATOR_HPP