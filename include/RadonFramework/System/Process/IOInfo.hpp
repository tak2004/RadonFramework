#ifndef RF_SYSTEM_PROCESS_IOINFO_HPP
#define RF_SYSTEM_PROCESS_IOINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Process {

struct IOInfo
{
    RF_Type::UInt64 ReadOperationCount;
    RF_Type::UInt64 WriteOperationCount;
    RF_Type::UInt64 OtherOperationCount;
    RF_Type::UInt64 ReadTransferedBytes;
    RF_Type::UInt64 WriteTransferedBytes;
    RF_Type::UInt64 OtherTransferedBytes;
};

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_IOINFO_HPP