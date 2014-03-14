#ifndef RF_SELECTMODE_HPP
#define RF_SELECTMODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Net
    {
        namespace SelectMode
        {
            enum Type{
                Read,
                Write,
                Error,
                ReadWrite,
                ReadError,
                WriteError,
                ReadWriteError
            };
        }
    }
}

#endif // RF_SELECTMODE_HPP

