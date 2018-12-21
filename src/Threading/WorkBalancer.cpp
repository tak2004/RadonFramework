#include "RadonFramework/Threading/WorkBalancer.hpp"
#include "RadonFramework/Memory/AutoPointerArray.hpp"
#include "RadonFramework/Memory/ObserverPointer.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Core::Idioms
{
template <>
class PImpl<RF_Thread::WorkBalancer>::Data
{
public:
  Data() = default;

  ~Data() = default;

  RF_Type::Size m_Cores = 1;
  RF_Type::Size m_Threads = 1;
  RF_Mem::AutoPointerArray<RF_Type::UInt8> m_ScratchPad;
  RF_Mem::ObserverPointer<RF_Type::UInt16> m_AssignedCoreIndices;
  RF_Mem::ObserverPointer<RF_Type::UInt16> m_Multiplier;
  RF_Mem::ObserverPointer<RF_Type::UInt16> m_Tasks;
  RF_Type::UInt32 m_HardwareHash = 0;
};

}  // namespace RadonFramework::Core::Idioms

namespace RadonFramework::Threading
{
void WorkBalancer::Configure(const RF_Type::UInt32 HardwareHash,
                             const RF_Type::Size Cores,
                             const RF_Type::Size Threads /*= 0*/)
{
  m_PImpl->m_Cores = Cores;
  m_PImpl->m_Threads = Threads != 0 ? Threads : Cores;
  m_PImpl->m_HardwareHash = HardwareHash;
}

void WorkBalancer::Configure(const RF_Type::UInt32 HardwareHash,
                             const RF_Type::Size Cores,
                             const Configuration& NewConfiguration)
{
}

void WorkBalancer::BalancePerCore(const RF_Type::Size Tasks,
                                  PerCoreBucketList& Buckets) const
{
}

void WorkBalancer::BalanceForPool(const RF_Type::Size Tasks,
                                  BucketList& Buckets) const
{
}

void WorkBalancer::RewardBalancing(const IdleList& IdlePerCore) {}

WorkBalancer::Configuration WorkBalancer::GetConfiguration() const
{
  return Configuration();
}

}  // namespace RadonFramework::Threading