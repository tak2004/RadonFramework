#ifndef RF_IO_FILESTATUS_HPP
#define RF_IO_FILESTATUS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt64.hpp>

namespace RadonFramework::IO {

struct FileStatus
{
    RF_Type::UInt64 Size;
    RF_Type::UInt64 LastModificationTimestamp;
    RF_Type::UInt64 LastAccessTimestamp;
    RF_Type::UInt64 CreateionTimestamp;
    RF_Type::Bool IsDirectory;
    RF_Type::Bool IsHidden;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_FILESTATUS_HPP