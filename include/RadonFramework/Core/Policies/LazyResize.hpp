#ifndef RF_CORE_POLICIES_LAZYRESIZE_HPP
#define RF_CORE_POLICIES_LAZYRESIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Core
    {        
        namespace Policies
        {
            template<int BlockSize, int ElementSizeInBits>
            struct LazyResize
            {
                void Init();
                void Free();
                Types::UInt32 Size()const;
                Types::UInt32 Count()const;
                void Resize(Types::UInt32 NewElementCount);
                Types::UInt32 ElementCount;
            };

            template<int BlockSize, int ElementSizeInBits>
            inline void LazyResize<BlockSize,ElementSizeInBits>::Init()
            {
                ElementCount=0;
            }

            template<int BlockSize, int ElementSizeInBits>
            inline void LazyResize<BlockSize,ElementSizeInBits>::Free()
            {

            }

            template<int BlockSize, int ElementSizeInBits>
            inline Types::UInt32 LazyResize<BlockSize,ElementSizeInBits>::Size()const
            {
                return (((ElementCount*ElementSizeInBits)-1)/(BlockSize*8))+1;
            }

            template<int BlockSize, int ElementSizeInBits>
            inline Types::UInt32 LazyResize<BlockSize,ElementSizeInBits>::Count()const
            {
                return ElementCount;
            }

            template<int BlockSize, int ElementSizeInBits>
            inline void LazyResize<BlockSize,ElementSizeInBits>::Resize(Types::UInt32 NewElementCount)
            {
                ElementCount=NewElementCount;
            }
        }
    }
}

#endif // RF_CORE_POLICIES_LAZYRESIZE_HPP