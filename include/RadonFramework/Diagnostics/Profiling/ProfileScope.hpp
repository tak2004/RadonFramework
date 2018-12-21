#ifndef RF_DIAGNOSTICS_PROFILING_PROFILESCOPE_HPP
#define RF_DIAGNOSTICS_PROFILING_PROFILESCOPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt64.hpp>

namespace RadonFramework::Diagnostics::Profiling
{
struct ProfileScopeData
{
  RF_Type::UInt64 Start;
  RF_Type::UInt64 Stop;
};

class ProfileScope
{
public:
  ProfileScope();
  ~ProfileScope();

protected:
  ProfileScopeData m_Data;
};

}  // namespace RadonFramework::Diagnostics::Profiling

#endif  //! RF_DIAGNOSTICS_PROFILING_PROFILESCOPE_HPP
