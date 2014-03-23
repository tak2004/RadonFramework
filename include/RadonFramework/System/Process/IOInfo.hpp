#ifndef RF_SYSTEM_PROCESS_IOINFO_HPP
#define RF_SYSTEM_PROCESS_IOINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Process {

struct IOInfo
{
    RFTYPE::UInt64 ReadOperationCount;
    RFTYPE::UInt64 WriteOperationCount;
    RFTYPE::UInt64 OtherOperationCount;
    RFTYPE::UInt64 ReadTransferedBytes;
    RFTYPE::UInt64 WriteTransferedBytes;
    RFTYPE::UInt64 OtherTransferedBytes;
};

} } }

#endif // RF_SYSTEM_PROCESS_IOINFO_HPP