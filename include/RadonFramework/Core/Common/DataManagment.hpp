#ifndef RF_CORE_COMMON_DATAMANAGMENT_HPP
#define RF_CORE_COMMON_DATAMANAGMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Common {

namespace DataManagment
{
    enum Type : RFTYPE::UInt8
    {
        // create a copy of data
        Copy=0,
        // prioritize dynamic buffers over locale one
        AllocateAndCopy,
        // data are managed from outside 
        UnmanagedInstance,
        // data are managed from this object now
        TransfereOwnership
    };
}

} } }
#endif // RF_CORE_COMMON_DATAMANAGMENT_HPP