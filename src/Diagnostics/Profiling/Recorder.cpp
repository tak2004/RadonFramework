#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/Recorder.hpp"

namespace RadonFramework { namespace Diagnostics { namespace Profiling {

void Recorder::AddScope(const ProfileScopeData& Scope)
{
	m_Timeline.Enqueue(Scope);
}

} } }