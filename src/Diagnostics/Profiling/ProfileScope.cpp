#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/ProfileScope.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/Diagnostics/Profiling/Recorder.hpp"

namespace RadonFramework { namespace Diagnostics { namespace Profiling {

ProfileScope::ProfileScope()
{
	m_Data.Start = RF_SysTime::GetHighResolutionCounter();
}

ProfileScope::~ProfileScope()
{
	m_Data.Stop = RF_SysTime::GetHighResolutionCounter();
	GlobalRecorder::GetInstance().AddScope(m_Data);
}

} } }