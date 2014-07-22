#ifndef RF_IO_ACCESSMODE_HPP
#define RF_IO_ACCESSMODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

namespace AccessMode
{
    enum Type
    {
        None=0,
        Exists,
        Write,
        WriteExists,
        Read,
        ReadExists,
        WriteRead,
        WriteReadExists,
        Execute,
        ExecuteExists,
        ExecuteWrite,
        ExecuteWriteExists,
        ExecuteRead,
        ExecuteReadExists,
        ExecuteWriteRead,
        ExecuteWriteReadExists,
        MAX
    };
}

AccessMode::Type operator |(const AccessMode::Type A, const AccessMode::Type B);
AccessMode::Type& operator |=(AccessMode::Type& A, const AccessMode::Type B);

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_ACCESSMODE_HPP