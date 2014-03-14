#ifndef RF_DIAGNOSTICS_PROCESSINGUNITS_HPP
#define RF_DIAGNOSTICS_PROCESSINGUNITS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Diagnostics
    {
        struct ProcessorData;

        class ProcessingUnits
        {
            public:
                static Memory::AutoPointer<ProcessingUnits> GatherData();

                ProcessingUnits();
                virtual ~ProcessingUnits();

                RFTYPE::UInt32 GetLogicalUnitCount()const;
                RFTYPE::UInt32 GetProcessorCount()const;
                RFTYPE::UInt32 GetProcessorUnitCount()const;

                ProcessorData const* GetProcessorInformation(const RFTYPE::UInt32 Index)const;

                RFTYPE::String GetName(const RFTYPE::UInt32 Index)const;
                RFTYPE::String GetBrand(const RFTYPE::UInt32 Index)const;
                RFTYPE::UInt32 GetCacheLineSize(const RFTYPE::UInt32 Index)const;
                RFTYPE::UInt32 GetLogicalUnitCount(const RFTYPE::UInt32 Index)const;
                RFTYPE::UInt32 GetUnitCount(const RFTYPE::UInt32 Index)const;
            private:
                class PIMPL;
                PIMPL* m_PIMPL;
        };
    }
}

#endif // RF_DIAGNOSTICS_PROCESSINGUNITS_HPP