#ifndef RF_FIXEDLENGTHALLOCATOR_HPP
#define RF_FIXEDLENGTHALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>

namespace RadonFramework
{
    namespace Memory
    {
        template <typename BLOCKOFFSETTYPE, typename BLOCKSIZETYPE, BLOCKSIZETYPE BLOCKSIZE>
        struct Chunk
        {
            RFTYPE::UInt8 *Data;
            BLOCKOFFSETTYPE FirstAvailableBlock;

            static BLOCKSIZETYPE BlockSize;

        };


    }
}

#endif // RF_FIXEDLENGTHALLOCATOR_HPP