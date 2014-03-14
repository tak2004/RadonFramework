#ifndef RF_IO_SEEKORIGIN_HPP
#define RF_IO_SEEKORIGIN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        namespace SeekOrigin
        {
            enum Type
            {
                Begin=0,
                Current,
                End,
                MAX
            };
        }
    }
}

#endif // RF_IO_SEEKORIGIN_HPP
