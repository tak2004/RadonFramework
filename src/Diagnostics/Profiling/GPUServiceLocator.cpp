#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/GPUServiceLocator.hpp"

namespace RadonFramework::Diagnostics::Profiling {

NullGPUService::NullGPUService(const RF_Type::String& Name)
:GPUService(Name)
{
}

void NullGPUService::ObtainGPUs()
{

}

RF_Type::Size NullGPUService::GPUCount() const
{
    return 0;
}

const RF_Collect::Array<RF_Type::Float32>& NullGPUService::CurrentValues(const RF_Type::Size GPUIndex) const
{    
    return m_EmptyValues;
}

const RF_Collect::Array<RF_Type::Float32>& NullGPUService::MaxValues(const RF_Type::Size GPUIndex) const
{
    return m_EmptyValues;
}

const RF_Collect::Array<RF_Type::Float32>& NullGPUService::MinValues(const RF_Type::Size GPUIndex) const
{
    return m_EmptyValues;
}

const RF_Collect::Array<RF_Type::Bool>& NullGPUService::AvailableValues(const RF_Type::Size GPUIndex) const
{
    return m_EmptyAvailableValues;
}

void NullGPUService::Update(const RF_Type::Size GPUIndex)
{
}

}