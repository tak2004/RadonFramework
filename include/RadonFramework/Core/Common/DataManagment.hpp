#ifndef RF_CORE_COMMON_DATAMANAGMENT_HPP
#define RF_CORE_COMMON_DATAMANAGMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework::Core::Common {

enum class DataManagment
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

#ifndef RF_SHORTHAND_NAMESPACE_COMMON
#define RF_SHORTHAND_NAMESPACE_COMMON
namespace RF_Common = RadonFramework::Core::Common;
#endif

#endif // RF_CORE_COMMON_DATAMANAGMENT_HPP