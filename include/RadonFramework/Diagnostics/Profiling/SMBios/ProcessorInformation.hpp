#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_PROCESSORINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_PROCESSORINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/CacheInformation.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace ProcessorType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        CentralProcessor=3,
                        MathProcessor=4,
                        DSPProcessor=5,
                        VideoProcessor=6
                    };
                }

                namespace ProcessorFamily
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        _8086=3,
                        _80286=4,
                        Intel386Processor=5,
                        Intel486Processor=6,
                        _8087=7,
                        _80287=8,
                        _80387=9,
                        _80487=10,
                        IntelPentiumProcessor=11,
                        PentiumProProcessor=12,
                        Pentium2Processor=13,
                        PentiumProcessorWithMMXTechnology=14,
                        IntelCeleronProcessor=15,
                        Pentium2XeonProcessor=16,
                        Pentium3Processor=17,
                        M1Family=18,
                        M2Family=19,
                        IntelCeleronMProcessor=20,
                        IntelPentium4HTProcessor=21,
                        //22-23 are not assign
                        AMDDuronProcessorFamily=24,
                        K5Family=25,
                        K6Family=26,
                        K6_2=27,
                        K6_3=28,
                        AMDAthlonProcessorFamily=29,
                        AMD29000Family=30,
                        K6_2Plus=31,
                        PowerPCFamily=32,
                        PowerPC601=33,
                        PowerPC603=34,
                        PowerPC603Plus=35,
                        PowerPC604=36,
                        PowerPC620=37,
                        PowerPCx704=38,
                        PowerPC750=39,
                        IntelCoreDuoProcessor=40,
                        IntelCoreDuoMobileProcessor=41,
                        IntelCoreSoloMobileProcessor=42,
                        IntelAtomProcessor=43,
                        //44-47 are not assign
                        AlphaFamily=48,
                        Alpha21064=49,
                        Alpha21066=50,
                        Alpha21164=51,
                        Alpha21164PC=52,
                        Alpha21164a=53,
                        Alpha21264=54,
                        Alpha21364=55,
                        AMDTurion2UltraDualCoreMobileMProcessorFamily=56,
                        AMDTurion2DualCoreMobileMProcessorFamily=57,
                        AMDAthlon2DualCoreMProcessorFamily=58,
                        AMDOpteron6100SeriesProcessor=59,
                        AMDOpteron4100SeriesProcessor=60,
                        //61-63 are not assign
                        MIPSFamily=61,
                        MIPSR4000=62,
                        MIPSR4200=63,
                        MIPSR4400=64,
                        MIPSR4600=65,
                        MIPSR10000=66,
                        //70-79 are not assign
                        SPARCFamily=80,
                        SuperSPARC=81,
                        microSPARC2=82,
                        microSPARC2ep=83,
                        UltraSPARC=84,
                        UltraSPARC2=85,
                        UltraSPARC2i=86,
                        UltraSPARC3=87,
                        UltraSPARC3i=88,
                        //89-95 are not assign
                        _68040Family=96,
                        _68xxx=97,
                        _68000=98,
                        _68010=99,
                        _68020=100,
                        _68030=101,
                        //102-111 are not assign
                        HobbitFamily=112,
                        //113-119 are not assign
                        CrusoeTM5000Family=120,
                        CrusoeTM3000Family=121,
                        EfficeonTM8000Family=122,
                        //123-127 are not assign
                        Weitek=128,
                        //129 is not assign
                        ItaniumProcessor=130,
                        AMDAthlon64ProcessorFamily=131,
                        AMDOpteronProcessorFamily=132,
                        AMDSempronProcessorFamily=133,
                        AMDTurion64MobileTechnology=134,
                        DualCoreAMDOpteronProcessorFamily=135,
                        AMDAthlon64X2DualCoreProcessorFamily=136,
                        AMDTurion64X2MobileTechnology=137,
                        QuadCoreAMDOpteronProcessorFamily=138,
                        ThirdGenerationAmdOpteronProcessorFamily=139,
                        AMDPhenomFXQuadCoreProcessorFamily=140,
                        AMDPhenomX4QuadCoreProcessorFamily=141,
                        AMDPhenomX2DualCoreProcessorFamily=142,
                        AMDAthlonX2DualCoreProcessorFamily=143,
                        PA_RISCFamily=144,
                        PA_RISC8500=145,
                        PA_RISC8000=146,
                        PA_RISC7300LC=147,
                        PA_RISC7200=148,
                        PA_RISC7100LC=149,
                        PA_RISC7100=150,
                        //151-159 are not assign
                        V30Family=160,
                        QuadCoreIntelXeonProcessor3200Series=161,
                        DualCoreIntelXeonProcessor3000Series=162,
                        QuadCoreIntelXeonProcessor5300Series=163,
                        DualCoreIntelXeonProcessor5100Series=164,
                        DualCoreIntelXeonProcessor5000Series=165,
                        DualCoreIntelXeonProcessorLV=166,
                        DualCoreIntelXeonProcessorULV=167,
                        DualCoreIntelXeonProcessor7100Series=168,
                        QuadCoreIntelXeonProcessor5400Series=169,
                        QuadCoreIntelXeonProcessor=170,
                        DualCoreIntelXeonProcessor5200Series=171,
                        DualCoreIntelXeonProcessor7200Series=172,
                        QuadCoreIntelXeonProcessor7300Series=173,
                        QuadCoreIntelXeonProcessor7400Series=174,
                        MultiCoreIntelXeonProcessor7400Series=175,
                        Pentium3XeonProcessor=176,
                        Pentium3ProcessorWithIntelSpeedStepTechnology=177,
                        Pentium4Processor=178,
                        IntelXeonProcessor=179,
                        AS400Family=180,
                        IntelXeonProcessorMP=181,
                        AMDAthlonXPProcessorFamily=182,
                        AMDAthlonMPProcessorFamily=183,
                        IntelItanium2Processor=184,
                        IntelPentiumMProcessor=185,
                        IntelCeleronDProcessor=186,
                        IntelPentiumDProcessor=187,
                        IntelPentiumProcessorExtremeEdition=188,
                        IntelCoreSoloProcessor=189,
                        //190 Reserved
                        IntelCore2DuoProcessor=191,
                        IntelCore2SoloProcessor=192,
                        IntelCoreExtremeProcessor=193,
                        IntelCore2QuadProcessor=194,
                        IntelCore2ExtremeMobileProcessor=195,
                        IntelCore2DuoMobileProcessor=196,
                        IntelCore2SoloMobileProcessor=197,
                        IntelCorei7Processor=198,
                        DualCoreIntelCeleronProcessor=199,
                        IBM390Family=200,
                        G4=201,
                        G5=202,
                        ESA390G6=203,
                        zArchitecturBase=204,
                        IntelCorei5Processor=205,
                        IntelCorei3Processor=206,
                        //207-209 are not assign
                        VIAC7MProcessorFamily=210,
                        VIAC7DProcessorFamily=211,
                        VIAC7ProcessorFamily=212,
                        VIAEdenProcessorFamily=213,
                        MultiCoreIntelXeonProcessor=214,
                        DualCoreIntelXeonProcessor3xxxSeries=215,
                        QuadCoreIntelXeonProcessor3xxxSeries=216,
                        VIANanoProcessorFamily=217,
                        DualCoreIntelXeonProcessor5xxxSeries=218,
                        QuadCoreIntelXeonProcessor5xxxSeries=219,
                        //220 is not assign
                        DualCoreIntelXeonProcessor7xxxSeries=221,
                        QuadCoreIntelXeonProcessor7xxxSeries=222,
                        MultiCoreIntelXeonProcessor7xxxSeries=223,
                        MultiCoreIntelXeonProcessor3400Series=224,
                        //225-229 are not assign
                        EmbeddedAMDOpteronQuadCoreProcessorFamily=230,
                        AMDPhenomTripleCoreProcessorFamily=231,
                        AMDTurionUltraDualCoreMobileProcessorFamily=232,
                        AMDTurionDualCoreMobileProcessorFamily=233,
                        AMDAthlonDualCoreProcessorFamily=234,
                        AMDSempronSIProcessorFamily=235,
                        AMDPhenom2ProcessorFamily=236,
                        AMDAthlon2ProcessorFamily=237,
                        SixCoreAMDOpteronProcessorFamily=238,
                        AMDSempronMProcessorFamily=239,
                        //240-249 are not assign
                        i860=250,
                        i960=251,
                        //252-253 are not assign
                        IndicatorToObtainTheProcessorFamilyFromTheProcessorFamily2Field=254,
                        Reserved=255,
                        //256-259 are not assign
                        SH3=260,
                        SH4=261,
                        //262-279 are not assign
                        ARM=280,
                        StrongARM=281,
                        //282-299 are not assign
                        _6x86=300,
                        MediaGX=301,
                        MII=302,
                        //303-319 are not assign
                        WinChip=320,
                        //321-349 are not assign
                        DSP=350,
                        //351-499 are not assign
                        VideoProcessor=500,
                        //512-65533 available for assignment
                        //65534-65535 reserved
                    };
                }

                namespace ProcessorUpgrade
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        DaughterBoard=3,
                        ZIFSocket=4,
                        ReplaceablePiggyBack=5,
                        None=6,
                        LIFSocket=7,
                        Slot1=8,
                        Slot2=9,
                        _370PinSocket=10,
                        SlotA=11,
                        SlotM=12,
                        Socket423=13,
                        SocketA=14,
                        Socket478=15,
                        Socket754=16,
                        Socket940=17,
                        Socket939=18,
                        SocketmPGA604=19,
                        SocketLGA771=20,
                        SocketLGA775=21,
                        SocketS1=22,
                        SocketAM2=23,
                        SocketF=24,
                        SocketLGA1366=25,
                        SocketG34=26,
                        SocketAM3=27,
                        SocketC32=28,
                        SocketLGA1156=29,
                        SocketLGA1567=30,
                        SocketPGA988A=31,
                        SocketBGA1288=32
                    };
                }

                namespace CPUStatus
                {
                    enum Type
                    {
                        Unknown=0,
                        Enabled=1,
                        DisabledByUserViaBIOS=2,
                        DiabledByBIOS=3,
                        IdleWaitingToBeEnabled=4,
                        Unknown1=5,
                        Unknown2=6,
                        Other=7
                    };
                }

                namespace ProcessorCharacteristics
                {
                    enum Type
                    {
                        Unknown=1,
                        _64BitCapable=2,
                        MultiCore=4,
                        HardwareThread=8,
                        ExecuteProtection=16,
                        EnhancedVirtualization=32,
                        PowerPerformanceControl=64
                    };
                }

                namespace ProcessorFeatures
                {
                    enum Type
                    {
                        FPU,
                        VME,
                        DE,
                        PSE,
                        TSC,
                        MSR,
                        PAE,
                        MCE,
                        CX8,
                        APIC,
                        SEP,
                        MTRR,
                        PGE,
                        MCA,
                        CMOV,
                        PAT,
                        PSE36,
                        PSN,
                        CLFL,
                        DTES,
                        ACPI,
                        MMX,
                        FXSR,
                        SSE,
                        SSE2,
                        SS,
                        HTT,
                        TM1,
                        IA64,
                        PBE,
                        SSE3,
                        PCLMUL,
                        DTES64,
                        MON,
                        DSCPL,
                        VMX,
                        SMX,
                        EST,
                        TM2,
                        SSSE3,
                        CID,
                        FMA,
                        CX16,
                        ETPRD,
                        PDCM,
                        DCA,
                        SSE4_1,
                        SSE4_2,
                        x2APIC,
                        MOVBE,
                        POPCNT,
                        AES,
                        XSAVE,
                        OSXSAVE,
                        AVX,
                        MAX//number of features(internal use)
                    };
                }

                class ProcessorInformation
                {
                    public:
                        ProcessorInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                            Collections::AutoVector<Core::Types::String> StringList,
                            Collections::AutoVector<SMBios::Information> Caches);
                        Core::Types::Bool IsCPUIDSupported()const;
                        Core::Types::String Socket()const;
                        ProcessorType::Type Type()const;
                        Core::Types::String TypeAsString()const;
                        ProcessorFamily::Type Family()const;
                        Core::Types::String FamilyAsString()const;
                        Core::Types::String Manufacturer()const;
                        Core::Types::String Version()const;
                        Core::Types::Float32 Voltage()const;
                        Core::Types::UInt16 ExternalClock()const;
                        Core::Types::UInt16 MaxPossibleSpeed()const;//of system not processor itself
                        Core::Types::UInt16 CurrentSpeed()const;
                        Core::Types::Bool IsCPUSocketPopulated()const;
                        CPUStatus::Type Status()const;
                        Core::Types::String StatusAsString()const;
                        ProcessorUpgrade::Type Upgrade()const;
                        Core::Types::String UpgradeAsString()const;
                        Core::Types::UInt32 CacheCount()const;
                        const CacheInformation& Cache(Core::Types::UInt32 Index)const;
                        Core::Types::String SerialNumber()const;
                        Core::Types::String AssetTag()const;
                        Core::Types::String PartNumber()const;
                        Core::Types::UInt8 CoreCount()const;
                        Core::Types::UInt8 EnabledCoreCount()const;
                        Core::Types::UInt8 MaxSupportedThreadCount()const;
                        ProcessorCharacteristics::Type CharacteristicsBitField()const;
                        Core::Types::Bool IsFeatureSupported(ProcessorFeatures::Type Feature)const;
                    protected:
                        //smbios
                        RadonFramework::Core::Types::Bool m_IsCPUIDSupported;
                        RadonFramework::Core::Types::String m_Socket;
                        ProcessorType::Type m_ProcessorType;
                        ProcessorFamily::Type m_Family;
                        RadonFramework::Core::Types::String m_Manufacturer;
                        RadonFramework::Core::Types::String m_Version;
                        RadonFramework::Core::Types::Float32 m_Voltage;
                        RadonFramework::Core::Types::UInt16 m_ExternalClock;
                        RadonFramework::Core::Types::UInt16 m_MaxPossibleSpeed;//of system not processor itself
                        RadonFramework::Core::Types::UInt16 m_CurrentSpeed;
                        RadonFramework::Core::Types::Bool m_IsCPUSocketPopulated;
                        CPUStatus::Type m_CPUStatus;
                        ProcessorUpgrade::Type m_Upgrade;
                        Collections::AutoVector<CacheInformation> m_Caches;
                        RadonFramework::Core::Types::String m_SerialNumber;
                        RadonFramework::Core::Types::String m_AssetTag;
                        RadonFramework::Core::Types::String m_PartNumber;
                        RadonFramework::Core::Types::UInt8 m_CoreCount;
                        RadonFramework::Core::Types::UInt8 m_EnabledCoreCount;
                        RadonFramework::Core::Types::UInt8 m_MaxSupportedThreadCount;
                        ProcessorCharacteristics::Type m_CharacteristicsBitField;

                        RadonFramework::Core::Types::Float32 GetProcessorVoltage(const RadonFramework::Core::Types::UInt8 VoltageField);

                        //cpuid
                        RadonFramework::Core::Types::Bool m_Features[ProcessorFeatures::MAX];

                        void ParseCPUID();
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_PROCESSORINFORMATION_HPP
