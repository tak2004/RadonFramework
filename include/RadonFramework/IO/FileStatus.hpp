#ifndef RF_IO_FILESTATUS_HPP
#define RF_IO_FILESTATUS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        struct FileStatus
        {
            RFTYPE::UInt64 Size;
            RFTYPE::UInt64 LastModificationTimestamp;
            RFTYPE::UInt64 LastAccessTimestamp;
            RFTYPE::UInt64 CreateionTimestamp;
            RFTYPE::Bool IsDirectory;
            RFTYPE::Bool IsHidden;
        };
    }
}

#endif // RF_IO_FILESTATUS_HPP