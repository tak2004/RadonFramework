#ifndef RF_DIAGNOSTICS_PROFILING_GPUSERVICE_HPP
#define RF_DIAGNOSTICS_PROFILING_GPUSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework::Diagnostics::Profiling
{
class GPUService : public RF_Pattern::Service
{
public:
  GPUService(const RF_Type::String& Name);

  enum ValueSymbol
  {
    FanSpeedPercentage = 0,
    GPUTemperature = 1,
    CoreClock = 2,
    MemoryClock = 3,
    Lanes = 4,
    BusSpeed = 5,
    GPUActivity = 6,
    FanSpeedRPM = 8
  };

  virtual void ObtainGPUs() = 0;
  virtual RF_Type::Size GPUCount() const = 0;
  virtual const RF_Collect::Array<RF_Type::Float32>&
  CurrentValues(const RF_Type::Size GPUIndex) const = 0;
  virtual const RF_Collect::Array<RF_Type::Float32>&
  MaxValues(const RF_Type::Size GPUIndex) const = 0;
  virtual const RF_Collect::Array<RF_Type::Float32>&
  MinValues(const RF_Type::Size GPUIndex) const = 0;
  virtual const RF_Collect::Array<RF_Type::Bool>&
  AvailableValues(const RF_Type::Size GPUIndex) const = 0;
  virtual void Update(const RF_Type::Size GPUIndex) = 0;
};

}  // namespace RadonFramework::Diagnostics::Profiling

#ifndef RF_SHORTHAND_NAMESPACE_PROF
#define RF_SHORTHAND_NAMESPACE_PROF
namespace RF_Prof = RadonFramework::Diagnostics::Profiling;
#endif

#endif  //! RF_DIAGNOSTICS_PROFILING_GPUSERVICE_HPP