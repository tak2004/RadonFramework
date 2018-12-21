#ifndef RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
#define RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Concurrency/DynamicQueueMPSC.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Diagnostics/Profiling/ProfileScope.hpp>

namespace RadonFramework::Diagnostics::Profiling
{
class Recorder
{
public:
  void AddScope(const ProfileScopeData& Scope);

protected:
  RF_Con::DynamicQueueMPSC<ProfileScopeData> m_Timeline;
};

using GlobalRecorder = RF_Pattern::Singleton<Recorder>;

}  // namespace RadonFramework::Diagnostics::Profiling

#endif  //! RF_DIAGNOSTICS_PROFILING_RECORDER_HPP
