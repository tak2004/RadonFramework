#ifndef RF_IO_ACCESSMODE_HPP
#define RF_IO_ACCESSMODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        namespace AccessMode
        {
            enum Type
            {
                None=0,
                Exists,
                Read,
                ReadExists,
                Write,
                WriteExists,
                WriteRead,
                WriteReadExists,
                Execute,
                ExecuteExists,
                ExecuteRead,
                ExecuteReadExists,
                ExecuteWrite,
                ExecuteWriteExists,
                ExecuteWriteRead,
                ExecuteWriteReadExists,
                MAX
            };
        }

        AccessMode::Type operator |(const AccessMode::Type A, const AccessMode::Type B);
        AccessMode::Type& operator |=(AccessMode::Type& A, const AccessMode::Type B);
    }
}

#endif // RF_IO_ACCESSMODE_HPP