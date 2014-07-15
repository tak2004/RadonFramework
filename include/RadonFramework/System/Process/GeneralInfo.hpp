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
    RF_Type::UInt32 ID;
    RF_Type::String BinaryName;
    RF_Type::String Name;
};

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_GENERALINFO_HPP