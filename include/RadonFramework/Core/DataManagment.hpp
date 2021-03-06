#ifndef RF_CORE_DATAMANAGMENT_HPP
#define RF_CORE_DATAMANAGMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Core/Types/UInt8.hpp>

namespace RadonFramework::Core {

enum class DataManagment : RF_Type::UInt8
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

}  // namespace RadonFramework::Core

#ifndef RF_SHORTHAND_NAMESPACE_CORE
#define RF_SHORTHAND_NAMESPACE_CORE
namespace RF_Core = RadonFramework::Core;
#endif

#endif // RF_CORE_DATAMANAGMENT_HPP