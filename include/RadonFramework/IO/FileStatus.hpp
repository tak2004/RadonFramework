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
            Core::Types::UInt64 Size;
            Core::Types::UInt64 LastModificationTimestamp;
            Core::Types::UInt64 LastAccessTimestamp;
            Core::Types::UInt64 CreateionTimestamp;
            Core::Types::Bool IsDirectory;
            Core::Types::Bool IsHidden;
        };
    }
}

#endif // RF_IO_FILESTATUS_HPP