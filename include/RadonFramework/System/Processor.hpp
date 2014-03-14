#ifndef RF_SYSTEM_PROCESSOR_HPP
#define RF_SYSTEM_PROCESSOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        struct ProcessorData;
        struct ProcessorSharedData;
    }

    namespace System
    {
        class CPUID;

        /// Get the amount of logical processors.
        RFTYPE::UInt32 GetLogicalProcessorCount(const Collections::Array<Diagnostics::ProcessorData>& Processors);
        
        /// This method will generate a dump the specified cpu information.
        RFTYPE::Bool GetProcessorInfoDump(RFTYPE::UInt32 Index, CPUID& Out);
        
        /** This method will be detect the capabilities of all processors.
          * You don't need to call this method because Radon class already 
          * do this.
          **/
        void DetectProcessors(Collections::Array<Diagnostics::ProcessorData>& Out);

        /// Load and return the shared processor information.
        const Diagnostics::ProcessorSharedData& LoadSharedProcessorInfo();
    }
}

#endif // RF_SYSTEM_PROCESSOR_HPP