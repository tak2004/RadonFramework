#ifndef RF_THREADING_WORKBALANCER_HPP
#define RF_THREADING_WORKBALANCER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework::Threading {

class WorkBalancer
{
public:
    typedef RF_Collect::Array<RF_Type::UInt8> IdleList;
    typedef RF_Collect::Array<RF_Type::UInt16> BucketList;
    typedef RF_Collect::Array<RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16>> PerCoreBucketList;
    typedef RF_Collect::Array<RF_Type::UInt8> Configuration;

    WorkBalancer();
    ~WorkBalancer();

    void Configure(const RF_Type::UInt32 HardwareHash, const RF_Type::Size Cores, 
        const RF_Type::Size Threads = 0);
    void Configure(const RF_Type::UInt32 HardwareHash, const RF_Type::Size Cores,
        const Configuration& NewConfiguration);
    void BalancePerCore(const RF_Type::Size Tasks, PerCoreBucketList& Buckets)const;
    void BalanceForPool(const RF_Type::Size Tasks, BucketList& Buckets)const;
    void RewardBalancing(const IdleList& IdlePerCore);
    Configuration GetConfiguration()const;
private:
    RF_Idiom::PImpl<WorkBalancer> m_PImpl;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif

#endif // !RF_THREADING_WORKBALANCER_HPP