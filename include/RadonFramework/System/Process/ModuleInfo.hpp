#ifndef RF_SYSTEM_PROCESS_MODULEINFO_HPP
#define RF_SYSTEM_PROCESS_MODULEINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace System { namespace Process {

typedef RadonFramework::Collections::Array<RFTYPE::String> ModuleInfo;

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_MODULEINFO_HPP