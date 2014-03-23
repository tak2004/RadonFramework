#ifndef RF_SYSTEM_PROCESS_GENERALINFO_HPP
#define RF_SYSTEM_PROCESS_GENERALINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Process {

// This is no POD structure because of the String class.
class GeneralInfo
{
public:
    RFTYPE::UInt32 ID;
    RFTYPE::String BinaryName;
    RFTYPE::String Name;
};

} } }

#endif // RF_SYSTEM_PROCESS_GENERALINFO_HPP