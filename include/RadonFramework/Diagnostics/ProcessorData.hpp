#ifndef RF_DIAGNOSTICS_PROCESSORDATA_HPP
#define RF_DIAGNOSTICS_PROCESSORDATA_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/BitSet.hpp>
#include <RadonFramework/Diagnostics/ProcessorExtension.hpp>
#include <RadonFramework/Net/FixedLengthString.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        struct ProcessorSharedData
        {
            Collections::BitSet<ProcessorExtension::MAX> Extensions;
            Core::Types::UInt32 CacheLineSize;
        };

        struct ProcessorData
        {
            ProcessorSharedData SharedData;
            Net::FixedLengthString<Core::Types::UInt8,12> Name;
            Net::FixedLengthString<Core::Types::UInt8,48> Brand;
            Core::Types::UInt32 LogicalProcessorCount;
            Core::Types::UInt32 CoreCount;
        };
    }
}

#endif // RF_DIAGNOSTICS_PROCESSORDATA_HPP