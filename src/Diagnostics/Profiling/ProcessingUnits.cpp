#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/ProcessingUnits.hpp"
#include "RadonFramework/Diagnostics/ProcessorData.hpp"
#include "RadonFramework/System/Processor.hpp"
#include "RadonFramework/Collections/Array.hpp"

using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

class RadonFramework::Diagnostics::ProcessingUnits::PIMPL
{
    public:
        Array<ProcessorData> m_Processors;
};

ProcessingUnits::ProcessingUnits()
:m_PIMPL(0)
{
    m_PIMPL = new PIMPL();
}

RadonFramework::Diagnostics::ProcessingUnits::~ProcessingUnits()
{
    delete m_PIMPL;
    m_PIMPL = 0;
}

UInt32 ProcessingUnits::GetUnitCount( const UInt32 Index ) const
{
    UInt32 result;
    if (Index < m_PIMPL->m_Processors.Count())
        result = m_PIMPL->m_Processors(Index).CoreCount;
    return result;
}

UInt32 ProcessingUnits::GetLogicalUnitCount( const UInt32 Index ) const
{
    UInt32 result;
    if (Index < m_PIMPL->m_Processors.Count())
        result = m_PIMPL->m_Processors(Index).LogicalProcessorCount;
    return result;
}

UInt32 ProcessingUnits::GetCacheLineSize( const UInt32 Index ) const
{
    UInt32 result;
    if (Index < m_PIMPL->m_Processors.Count())
        result = m_PIMPL->m_Processors(Index).SharedData.CacheLineSize;
    return result;
}

String ProcessingUnits::GetBrand( const UInt32 Index ) const
{
    String result;
    if (Index < m_PIMPL->m_Processors.Count())
        result = m_PIMPL->m_Processors(Index).Brand.ToString();
    return result;
}

String ProcessingUnits::GetName( const UInt32 Index ) const
{
    String result;
    if (Index < m_PIMPL->m_Processors.Count())
        result = m_PIMPL->m_Processors(Index).Name.ToString();
    return result;
}

ProcessorData const* ProcessingUnits::GetProcessorInformation( const UInt32 Index ) const
{
    ProcessorData* result = 0;
    if (Index < m_PIMPL->m_Processors.Count())
        result = &m_PIMPL->m_Processors(Index);
    return result;
}

UInt32 ProcessingUnits::GetLogicalUnitCount()const
{
    UInt32 result=0;
    for (UInt32 i=0;i<m_PIMPL->m_Processors.Count();++i)
        result+=m_PIMPL->m_Processors(i).LogicalProcessorCount;
    return result;
}

UInt32 ProcessingUnits::GetProcessorCount()const
{
    UInt32 result=0;
    result = static_cast<UInt32>(m_PIMPL->m_Processors.Count());
    return result;
}

UInt32 ProcessingUnits::GetProcessorUnitCount()const
{
    UInt32 result=0;
    for (UInt32 i=0;i<m_PIMPL->m_Processors.Count();++i)
        result+=m_PIMPL->m_Processors(i).CoreCount;
    return result;
}

AutoPointer<ProcessingUnits> ProcessingUnits::GatherData()
{
    AutoPointer<ProcessingUnits> result(new ProcessingUnits());
    RadonFramework::System::DetectProcessors(result->m_PIMPL->m_Processors);
    return result;
}
