#ifndef RF_DIAGNOSTICS_PROFILING_GPUSERVICELOCATOR_HPP
#define RF_DIAGNOSTICS_PROFILING_GPUSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Diagnostics/Profiling/GPUService.hpp>

namespace RadonFramework::Diagnostics::Profiling
{
class NullGPUService : public GPUService
{
public:
  NullGPUService(const RF_Type::String& Name);
  void ObtainGPUs() final;
  RF_Type::Size GPUCount() const final;
  const RF_Collect::Array<RF_Type::Float32>&
  CurrentValues(const RF_Type::Size GPUIndex) const final;
  const RF_Collect::Array<RF_Type::Float32>&
  MaxValues(const RF_Type::Size GPUIndex) const final;
  const RF_Collect::Array<RF_Type::Float32>&
  MinValues(const RF_Type::Size GPUIndex) const final;
  const RF_Collect::Array<RF_Type::Bool>&
  AvailableValues(const RF_Type::Size GPUIndex) const final;
  void Update(const RF_Type::Size GPUIndex) final;

private:
  RF_Collect::Array<RF_Type::Float32> m_EmptyValues;
  RF_Collect::Array<RF_Type::Bool> m_EmptyAvailableValues;
};

class GPUServiceLocator : public RF_Pattern::Locator<GPUService, NullGPUService>
{
};

}  // namespace RadonFramework::Diagnostics::Profiling

#ifndef RF_SHORTHAND_NAMESPACE_PROF
#define RF_SHORTHAND_NAMESPACE_PROF
namespace RF_Prof = RadonFramework::Diagnostics::Profiling;
#endif

#endif  //! RF_DIAGNOSTICS_PROFILING_GPUSERVICELOCATOR_HPP