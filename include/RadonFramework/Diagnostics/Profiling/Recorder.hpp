#ifndef RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
#define RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Concurrency/DynamicQueueMPSC.hpp>
#include <RadonFramework/Diagnostics/Profiling/ProfileScope.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Profiling {

class Recorder
{
public:
	void AddScope(const ProfileScopeData& Scope);
protected:
	RF_Con::DynamicQueueMPSC<ProfileScopeData> m_Timeline;
};

typedef RF_Pattern::Singleton<Recorder> GlobalRecorder;

} } }

#endif //!RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
