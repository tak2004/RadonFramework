#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Defines.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/ProcessorInformation.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

#ifdef RF_VISUALCPP
    #include <intrin.h>
#endif

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

#pragma pack(push,1)
struct ProcessorInformationStructure
{
    StructureHeader Header;
    UInt8 SocketDesignation;//string
    UInt8 ProcessorType;
    UInt8 ProcessorFamily;
    UInt8 ProcessorManufacturer;//string
    UInt64 ProcessorID;
    UInt8 ProcessorVersion;//string
    UInt8 Voltage;
    UInt16 ExternalClock;
    UInt16 MaxSpeed;
    UInt16 CurrentSpeed;
    UInt8 Satus;
    UInt8 ProcessorUpgrade;
    //2.1 and up
    UInt16 L1CacheHandle;
    UInt16 L2CacheHandle;
    UInt16 L3CacheHandle;
    //2.3 and up
    UInt8 SerialNumber;//string
    UInt8 AssetTag;//string
    UInt8 PartNumber;//string
    //2.5 and up
    UInt8 CoreCount;
    UInt8 CoreEnabled;
    UInt8 ThreadCount;
    UInt16 ProcessorCharacteristics;
};
#pragma pack(pop)

Float32 ProcessorInformation::GetProcessorVoltage(const UInt8 VoltageField)
{
    Float32 vol;
    if ((VoltageField & 128)==0)
    {
        switch(VoltageField & 7)
        {
        case 1:
            vol=5.0f;
            break;
        case 2:
            vol=3.3f;
            break;
        case 4:
            vol=2.9f;
            break;
        default:
            vol=0.0;
        }
    }
    else
    {//SMBIOS 2.7 specs page 49
        vol=(Float32)(VoltageField-128)/10.0f;
    }
    return vol;
}

ProcessorInformation::ProcessorInformation( AutoPointerArray<UInt8> Data,
                                            AutoVector<String> StringList,
                                            AutoVector<Information> Caches)
:m_IsCPUIDSupported(false)
{
    ProcessorInformationStructure* procinfo=(ProcessorInformationStructure*)Data.Get();
    m_Socket=procinfo->SocketDesignation!=0?StringList[procinfo->SocketDesignation-1]->TrimEnd(" "):"";
    m_ProcessorType=(ProcessorType::Type)procinfo->ProcessorType;
    m_Family=(ProcessorFamily::Type)procinfo->ProcessorFamily;
    m_Manufacturer=procinfo->ProcessorManufacturer!=0?StringList[procinfo->ProcessorManufacturer-1]->TrimEnd(" "):"";
    m_Version=procinfo->ProcessorVersion!=0?StringList[procinfo->ProcessorVersion-1]->TrimEnd(" "):"";
    m_Voltage=GetProcessorVoltage(procinfo->Voltage);
    m_ExternalClock=procinfo->ExternalClock;
    m_MaxPossibleSpeed=procinfo->MaxSpeed;
    m_CurrentSpeed=procinfo->CurrentSpeed;
    m_IsCPUSocketPopulated=(procinfo->Satus & 32)!=0;
    m_CPUStatus=(CPUStatus::Type)(procinfo->Satus & 7);
    m_Upgrade=(ProcessorUpgrade::Type)procinfo->ProcessorUpgrade;

    if (procinfo->Header.Length>0x20)
    {
        m_SerialNumber=procinfo->SerialNumber!=0?StringList[procinfo->SerialNumber-1]->TrimEnd(" "):"";
        m_AssetTag=procinfo->AssetTag!=0?StringList[procinfo->AssetTag-1]->TrimEnd(" "):"";
        m_PartNumber=procinfo->PartNumber!=0?StringList[procinfo->PartNumber-1]->TrimEnd(" "):"";
    }

    if (procinfo->Header.Length>0x23)
    {
        m_CoreCount=procinfo->CoreCount;
        m_EnabledCoreCount=procinfo->CoreEnabled;
        m_MaxSupportedThreadCount=procinfo->ThreadCount;
        m_CharacteristicsBitField=(ProcessorCharacteristics::Type)procinfo->ProcessorCharacteristics;
    }

    if (procinfo->Header.Length>0x1A)
        for (Collections::AutoVector<SMBios::Information>::Iterator it=Caches.Begin();it!=Caches.End();++it)
        {
            if ((*it)->Handle==procinfo->L1CacheHandle || (*it)->Handle==procinfo->L2CacheHandle || (*it)->Handle==procinfo->L3CacheHandle)
            {
                Memory::AutoPointer<CacheInformation> cache(new CacheInformation((*it)->Data,(*it)->StringList));
                m_Caches.PushBack(cache);
            }
        }

    if (procinfo->ProcessorID & 0xffff000000000000)//check if cpuid is supported
    {
        m_IsCPUIDSupported=true;
        ParseCPUID();
    }
}

void ProcessorInformation::ParseCPUID()
{
    unsigned int _ecx=0;
    unsigned int _edx=0;


    #if defined(RF_GCC) || defined(RF_MINGW)
    asm ("cpuid"
        : "=c" (_ecx),
          "=d" (_edx)
        : "a" (1));

    #else
        #ifdef RF_VISUALCPP
        int cpuinfo[4];
        __cpuid(cpuinfo,1);
        _ecx=cpuinfo[2];
        _edx=cpuinfo[3];
        #else
            RF_COMPILER_WARNING("Pls implement the cpuid for this compiler.");
        #endif
    #endif

    m_Features[ProcessorFeatures::FPU]=(_edx & 1)!=0;//FPU
    m_Features[ProcessorFeatures::VME]=(_edx & 2)!=0;//VME
    m_Features[ProcessorFeatures::DE]=(_edx & 4)!=0;//DE
    m_Features[ProcessorFeatures::PSE]=(_edx & 8)!=0;//PSE
    m_Features[ProcessorFeatures::TSC]=(_edx & 0x10)!=0;//TSC
    m_Features[ProcessorFeatures::MSR]=(_edx & 0x20)!=0;//MSR
    m_Features[ProcessorFeatures::PAE]=(_edx & 0x40)!=0;//PAE
    m_Features[ProcessorFeatures::MCE]=(_edx & 0x80)!=0;//MCE
    m_Features[ProcessorFeatures::CX8]=(_edx & 0x100)!=0;//CX8
    m_Features[ProcessorFeatures::APIC]=(_edx & 0x200)!=0;//APIC
    m_Features[ProcessorFeatures::SEP]=(_edx & 0x800)!=0;//SEP
    m_Features[ProcessorFeatures::MTRR]=(_edx & 0x1000)!=0;//MTRR
    m_Features[ProcessorFeatures::PGE]=(_edx & 0x2000)!=0;//PGE
    m_Features[ProcessorFeatures::MCA]=(_edx & 0x4000)!=0;//MCA
    m_Features[ProcessorFeatures::CMOV]=(_edx & 0x8000)!=0;//CMOV
    m_Features[ProcessorFeatures::PAT]=(_edx & 0x10000)!=0;//PAT
    m_Features[ProcessorFeatures::PSE36]=(_edx & 0x20000)!=0;//PSE36
    m_Features[ProcessorFeatures::PSN]=(_edx & 0x40000)!=0;//PSN
    m_Features[ProcessorFeatures::CLFL]=(_edx & 0x80000)!=0;//CLFL
    m_Features[ProcessorFeatures::DTES]=(_edx & 0x200000)!=0;//DTES
    m_Features[ProcessorFeatures::ACPI]=(_edx & 0x400000)!=0;//ACPI
    m_Features[ProcessorFeatures::MMX]=(_edx & 0x800000)!=0;//MMX
    m_Features[ProcessorFeatures::FXSR]=(_edx & 0x1000000)!=0;//FXSR
    m_Features[ProcessorFeatures::SSE]=(_edx & 0x2000000)!=0;//SSE
    m_Features[ProcessorFeatures::SSE2]=(_edx & 0x4000000)!=0;//SSE2
    m_Features[ProcessorFeatures::SS]=(_edx & 0x8000000)!=0;//SS
    m_Features[ProcessorFeatures::HTT]=(_edx & 0x10000000)!=0;//HTT
    m_Features[ProcessorFeatures::TM1]=(_edx & 0x20000000)!=0;//TM1
    m_Features[ProcessorFeatures::IA64]=(_edx & 0x40000000)!=0;//IA64
    m_Features[ProcessorFeatures::PBE]=(_edx & 0x80000000)!=0;//PBE
    m_Features[ProcessorFeatures::SSE3]=(_ecx & 1)!=0;//SSE3
    m_Features[ProcessorFeatures::PCLMUL]=(_ecx & 2)!=0;//PCLMUL
    m_Features[ProcessorFeatures::DTES64]=(_ecx & 4)!=0;//DTES64
    m_Features[ProcessorFeatures::MON]=(_ecx & 8)!=0;//MON
    m_Features[ProcessorFeatures::DSCPL]=(_ecx & 0x10)!=0;//DSCPL
    m_Features[ProcessorFeatures::VMX]=(_ecx & 0x20)!=0;//VMX
    m_Features[ProcessorFeatures::SMX]=(_ecx & 0x40)!=0;//SMX
    m_Features[ProcessorFeatures::EST]=(_ecx & 0x80)!=0;//EST
    m_Features[ProcessorFeatures::TM2]=(_ecx & 0x100)!=0;//TM2
    m_Features[ProcessorFeatures::SSSE3]=(_ecx & 0x200)!=0;//SSSE3
    m_Features[ProcessorFeatures::CID]=(_ecx & 0x400)!=0;//CID
    m_Features[ProcessorFeatures::FMA]=(_ecx & 0x1000)!=0;//FMA
    m_Features[ProcessorFeatures::CX16]=(_ecx & 0x2000)!=0;//CX16
    m_Features[ProcessorFeatures::ETPRD]=(_ecx & 0x4000)!=0;//ETPRD
    m_Features[ProcessorFeatures::PDCM]=(_ecx & 0x8000)!=0;//PDCM
    m_Features[ProcessorFeatures::DCA]=(_ecx & 0x40000)!=0;//DCA
    m_Features[ProcessorFeatures::SSE4_1]=(_ecx & 0x80000)!=0;//SSE4.1
    m_Features[ProcessorFeatures::SSE4_2]=(_ecx & 0x100000)!=0;//SSE4.2
    m_Features[ProcessorFeatures::x2APIC]=(_ecx & 0x200000)!=0;//x2APIC
    m_Features[ProcessorFeatures::MOVBE]=(_ecx & 0x400000)!=0;//MOVBE
    m_Features[ProcessorFeatures::POPCNT]=(_ecx & 0x800000)!=0;//POPCNT
    m_Features[ProcessorFeatures::AES]=(_ecx & 0x2000000)!=0;//AES
    m_Features[ProcessorFeatures::XSAVE]=(_ecx & 0x4000000)!=0;//XSAVE
    m_Features[ProcessorFeatures::OSXSAVE]=(_ecx & 0x8000000)!=0;//OSXSAVE
    m_Features[ProcessorFeatures::AVX]=(_ecx & 0x10000000)!=0;//AVX
}

Float32 ProcessorInformation::Voltage()const
{
    return m_Voltage;
}

Bool ProcessorInformation::IsCPUIDSupported()const
{
    return m_IsCPUIDSupported;
}

String ProcessorInformation::Socket()const
{
    return m_Socket;
}

ProcessorType::Type ProcessorInformation::Type()const
{
    return m_ProcessorType;
}

String ProcessorInformation::TypeAsString()const
{
    String str;
    switch (m_ProcessorType)
    {
        case ProcessorType::CentralProcessor:str="Central processor";break;
        case ProcessorType::DSPProcessor:str="DSP processor";break;
        case ProcessorType::MathProcessor:str="Math processor";break;
        case ProcessorType::Other:str="Other";break;
        case ProcessorType::Unknown:str="Unknown";break;
        case ProcessorType::VideoProcessor:str="Video processor";break;
    }
    return str;
}

ProcessorFamily::Type ProcessorInformation::Family()const
{
    return m_Family;
}

String ProcessorInformation::FamilyAsString()const
{
    String str;
    switch (m_Family)
    {
        case ProcessorFamily::_8087:str="8087";break;
        case ProcessorFamily::_8086:str="8086";break;
        case ProcessorFamily::_80487:str="80487";break;
        case ProcessorFamily::_80387:str="80387";break;
        case ProcessorFamily::_80287:str="80287";break;
        case ProcessorFamily::_80286:str="80286";break;
        case ProcessorFamily::_6x86:str="6x86";break;
        case ProcessorFamily::_68xxx:str="68xxx";break;
        case ProcessorFamily::_68040Family:str="68040 Family";break;
        case ProcessorFamily::_68030:str="68030";break;
        case ProcessorFamily::_68020:str="68020";break;
        case ProcessorFamily::_68010:str="68010";break;
        case ProcessorFamily::_68000:str="68000";break;
        case ProcessorFamily::zArchitecturBase:str="z architectur base";break;
        case ProcessorFamily::WinChip:str="Win Chip";break;
        case ProcessorFamily::Weitek:str="Weitek";break;
        case ProcessorFamily::VideoProcessor:str="Video processor";break;
        case ProcessorFamily::VIANanoProcessorFamily:str="VIA nano family";break;
        case ProcessorFamily::VIAEdenProcessorFamily:str="VIA eden family";break;
        case ProcessorFamily::VIAC7ProcessorFamily:str="VIA C7 family";break;
        case ProcessorFamily::VIAC7MProcessorFamily:str="VIA C7M family";break;
        case ProcessorFamily::VIAC7DProcessorFamily:str="VIA C7D family";break;
        case ProcessorFamily::V30Family:str="V30 family";break;
        case ProcessorFamily::Unknown:str="Unknown";break;
        case ProcessorFamily::UltraSPARC3i:str="Ultra SPARC 3i";break;
        case ProcessorFamily::UltraSPARC3:str="Ultra SPARC 3";break;
        case ProcessorFamily::UltraSPARC2i:str="Ultra SPARC 2i";break;
        case ProcessorFamily::UltraSPARC2:str="Ultra SPARC 2";break;
        case ProcessorFamily::UltraSPARC:str="Ultra SPARC";break;
        case ProcessorFamily::ThirdGenerationAmdOpteronProcessorFamily:str="3rd generation AMD Opteron family";break;
        case ProcessorFamily::SuperSPARC:str="Super SPARC";break;
        case ProcessorFamily::StrongARM:str="Strong ARM";break;
        case ProcessorFamily::SPARCFamily:str="SPARC family";break;
        case ProcessorFamily::SixCoreAMDOpteronProcessorFamily:str="6 core AMD Opteron family";break;
        case ProcessorFamily::SH4:str="SH4";break;
        case ProcessorFamily::SH3:str="SH3";break;
        case ProcessorFamily::Reserved:str="Reserved";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor7xxxSeries:str="Quad core Intel Xeon 7xxx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor7400Series:str="Quad core Intel Xeon 74xx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor7300Series:str="Quad core Intel Xeon 73xx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor5xxxSeries:str="Quad core Intel Xeon 5xxx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor5400Series:str="Quad core Intel Xeon 54xx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor5300Series:str="Quad core Intel Xeon 53xx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor3xxxSeries:str="Quad core Intel Xeon 3xxx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor3200Series:str="Quad core Intel Xeon 32xx series";break;
        case ProcessorFamily::QuadCoreIntelXeonProcessor:str="Quad core Intel Xeon";break;
        case ProcessorFamily::QuadCoreAMDOpteronProcessorFamily:str="Quad core AMD Opteron family";break;
        case ProcessorFamily::PowerPCx704:str="PowerPC x704";break;
        case ProcessorFamily::PowerPCFamily:str="PowerPC family";break;
        case ProcessorFamily::PowerPC750:str="PowerPC 750";break;
        case ProcessorFamily::PowerPC620:str="PowerPC 620";break;
        case ProcessorFamily::PowerPC604:str="PowerPC 604";break;
        case ProcessorFamily::PowerPC603Plus:str="PowerPC 603+";break;
        case ProcessorFamily::PowerPC603:str="PowerPC 603";break;
        case ProcessorFamily::PowerPC601:str="PowerPC 601";break;
        case ProcessorFamily::PentiumProProcessor:str="Pentium Pro";break;
        case ProcessorFamily::PentiumProcessorWithMMXTechnology:str="Pentium with MMX technology";break;
        case ProcessorFamily::Pentium4Processor:str="Pentium 4";break;
        case ProcessorFamily::Pentium3XeonProcessor:str="Pentium 3 Xeon";break;
        case ProcessorFamily::Pentium3ProcessorWithIntelSpeedStepTechnology:str="Pentium 3 with Intel SpeedStep technology";break;
        case ProcessorFamily::Pentium3Processor:str="Pentium 3";break;
        case ProcessorFamily::Pentium2XeonProcessor:str="Pentium 2 Xeon";break;
        case ProcessorFamily::Pentium2Processor:str="Pentium 2";break;
        case ProcessorFamily::PA_RISCFamily:str="PA RISC family";break;
        case ProcessorFamily::PA_RISC8500:str="PA RISC 8500";break;
        case ProcessorFamily::PA_RISC8000:str="PA RISC 8000";break;
        case ProcessorFamily::PA_RISC7300LC:str="PA RISC 7500LC";break;
        case ProcessorFamily::PA_RISC7200:str="PA RISC 7200";break;
        case ProcessorFamily::PA_RISC7100LC:str="PA RISC 7100LC";break;
        case ProcessorFamily::PA_RISC7100:str="PA RISC 7100";break;
        case ProcessorFamily::Other:str="Other";break;
        case ProcessorFamily::MultiCoreIntelXeonProcessor7xxxSeries:str="Multi core Intel Xeon 7xxx series";break;
        case ProcessorFamily::MultiCoreIntelXeonProcessor7400Series:str="Multi core Intel Xeon 7400 series";break;
        case ProcessorFamily::MultiCoreIntelXeonProcessor3400Series:str="Multi core Intel Xeon 3400 series";break;
        case ProcessorFamily::MultiCoreIntelXeonProcessor:str="Multi core Intel Xeon";break;
        case ProcessorFamily::MIPSR4600:str="MIPSR4600";break;
        case ProcessorFamily::MIPSR4400:str="MIPSR4400";break;
        case ProcessorFamily::MIPSR4200:str="MIPSR4200";break;
        case ProcessorFamily::MIPSR4000:str="MIPSR4000";break;
        case ProcessorFamily::MIPSR10000:str="MIPSR10000";break;
        case ProcessorFamily::MIPSFamily:str="MIPS family";break;
        case ProcessorFamily::MII:str="MII";break;
        case ProcessorFamily::microSPARC2ep:str="micro SPARC 2ep";break;
        case ProcessorFamily::microSPARC2:str="micro SPARC 2";break;
        case ProcessorFamily::MediaGX:str="MediaGX";break;
        case ProcessorFamily::M2Family:str="M2 family";break;
        case ProcessorFamily::M1Family:str="M1 family";break;
        case ProcessorFamily::K6_3:str="K6 3";break;
        case ProcessorFamily::K6_2Plus:str="K6 2+";break;
        case ProcessorFamily::K6_2:str="K6 2";break;
        case ProcessorFamily::K6Family:str="K6 family";break;
        case ProcessorFamily::K5Family:str="k5 family";break;
        case ProcessorFamily::ItaniumProcessor:str="Itanium";break;
        case ProcessorFamily::IntelXeonProcessorMP:str="Intel Xeon MP";break;
        case ProcessorFamily::IntelXeonProcessor:str="Intel Xeon";break;
        case ProcessorFamily::IntelPentiumProcessorExtremeEdition:str="Intel Pentium Extrem edition";break;
        case ProcessorFamily::IntelPentiumProcessor:str="Intel Pentium";break;
        case ProcessorFamily::IntelPentiumMProcessor:str="Intel Pentium M";break;
        case ProcessorFamily::IntelPentiumDProcessor:str="Intel Pentium D";break;
        case ProcessorFamily::IntelPentium4HTProcessor:str="Intel Pentium 4 HT";break;
        case ProcessorFamily::IntelItanium2Processor:str="Intel Itanium 2";break;
        case ProcessorFamily::IntelCoreSoloProcessor:str="Intel Core solo";break;
        case ProcessorFamily::IntelCoreSoloMobileProcessor:str="Intel Core solo mobile";break;
        case ProcessorFamily::IntelCorei7Processor:str="Intel Core i7";break;
        case ProcessorFamily::IntelCorei5Processor:str="Intel Core i5";break;
        case ProcessorFamily::IntelCorei3Processor:str="Intel Core i3";break;
        case ProcessorFamily::IntelCoreExtremeProcessor:str="Intel Core Extreme";break;
        case ProcessorFamily::IntelCoreDuoProcessor:str="Intel Core Duo";break;
        case ProcessorFamily::IntelCoreDuoMobileProcessor:str="Intel Core Duo mobile";break;
        case ProcessorFamily::IntelCore2SoloProcessor:str="Intel Core 2 solo";break;
        case ProcessorFamily::IntelCore2SoloMobileProcessor:str="Intel Core 2 solo mobile";break;
        case ProcessorFamily::IntelCore2QuadProcessor:str="Intel Core 2 Quad";break;
        case ProcessorFamily::IntelCore2ExtremeMobileProcessor:str="Intel Core 2 Extreme mobile";break;
        case ProcessorFamily::IntelCore2DuoProcessor:str="Intel Core 2 Duo";break;
        case ProcessorFamily::IntelCore2DuoMobileProcessor:str="Intel Core 2 Duo mobile";break;
        case ProcessorFamily::IntelCeleronProcessor:str="Intel Celeron";break;
        case ProcessorFamily::IntelCeleronMProcessor:str="Intel Celeron M";break;
        case ProcessorFamily::IntelCeleronDProcessor:str="Intel Celeron D";break;
        case ProcessorFamily::IntelAtomProcessor:str="Intel Atom";break;
        case ProcessorFamily::Intel486Processor:str="Intel 486";break;
        case ProcessorFamily::Intel386Processor:str="Intel 386";break;
        case ProcessorFamily::IndicatorToObtainTheProcessorFamilyFromTheProcessorFamily2Field:str="Indicator to obtain the processor family from the ProcessorFamily2Field";break;
        case ProcessorFamily::IBM390Family:str="IBM 390 family";break;
        case ProcessorFamily::i960:str="i960";break;
        case ProcessorFamily::i860:str="i860";break;
        case ProcessorFamily::HobbitFamily:str="Hobbit family";break;
        case ProcessorFamily::G5:str="G5";break;
        case ProcessorFamily::G4:str="G4";break;
        case ProcessorFamily::ESA390G6:str="ESA390 G6";break;
        case ProcessorFamily::EmbeddedAMDOpteronQuadCoreProcessorFamily:str="Embedded AMD Opteron Quad Core family";break;
        case ProcessorFamily::EfficeonTM8000Family:str="Efficeon TM8000 family";break;
        case ProcessorFamily::DualCoreIntelXeonProcessorULV:str="Dual Core Intel Xeon ULV";break;
        case ProcessorFamily::DualCoreIntelXeonProcessorLV:str="Dual Core Intel Xeon LV";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor7xxxSeries:str="Dual Core Intel Xeon 7xxx series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor7200Series:str="Dual Core Intel Xeon 7200 series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor7100Series:str="Dual Core Intel Xeon 7100 series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor5xxxSeries:str="Dual Core Intel Xeon 5xxx series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor5200Series:str="Dual Core Intel Xeon 5200 series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor5100Series:str="Dual Core Intel Xeon 5100 series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor5000Series:str="Dual Core Intel Xeon 5000 series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor3xxxSeries:str="Dual Core Intel Xeon 3xxx series";break;
        case ProcessorFamily::DualCoreIntelXeonProcessor3000Series:str="Dual Core Intel Xeon 3000 series";break;
        case ProcessorFamily::DualCoreIntelCeleronProcessor:str="Dual Core Intel Celeron";break;
        case ProcessorFamily::DualCoreAMDOpteronProcessorFamily:str="Dual Core AMD Opteron family";break;
        case ProcessorFamily::DSP:str="DSP";break;
        case ProcessorFamily::CrusoeTM5000Family:str="Crusoe TM5000 family";break;
        case ProcessorFamily::CrusoeTM3000Family:str="Crusoe TM3000 family";break;
        case ProcessorFamily::AS400Family:str="AS400 family";break;
        case ProcessorFamily::ARM:str="ARM";break;
        case ProcessorFamily::AMDTurionDualCoreMobileProcessorFamily:str="AMD Turion Dual Core mobile family";break;
        case ProcessorFamily::AMDTurion64MobileTechnology:str="AMD Turion64 mobile technology";break;
        case ProcessorFamily::AMDTurion64X2MobileTechnology:str="AMD Turion64 X2 mobile technology";break;
        case ProcessorFamily::AMDTurionUltraDualCoreMobileProcessorFamily:str="AMD Turion Ultra Dual Core mobile family";break;
        case ProcessorFamily::AMDTurion2UltraDualCoreMobileMProcessorFamily:str="AMD Turion2 Ultra Dual Core mobile M family";break;
        case ProcessorFamily::AMDTurion2DualCoreMobileMProcessorFamily:str="AMD Turion2 Dual Core mobile M family";break;
        case ProcessorFamily::AMDSempronSIProcessorFamily:str="AMD Sempron SI family";break;
        case ProcessorFamily::AMDSempronProcessorFamily:str="AMD Sempron family";break;
        case ProcessorFamily::AMDSempronMProcessorFamily:str="AMD Sempron M family";break;
        case ProcessorFamily::AMDPhenomX4QuadCoreProcessorFamily:str="AMD Phenom X4 Quad Core family";break;
        case ProcessorFamily::AMDPhenomX2DualCoreProcessorFamily:str="AMD Phenom X2 Dual Core family";break;
        case ProcessorFamily::AMDPhenomTripleCoreProcessorFamily:str="AMD Phenom Triple Core family";break;
        case ProcessorFamily::AMDPhenomFXQuadCoreProcessorFamily:str="AMD Phenom FX Quad Core family";break;
        case ProcessorFamily::AMDPhenom2ProcessorFamily:str="AMD Phenom 2 family";break;
        case ProcessorFamily::AMDOpteronProcessorFamily:str="AMD Opteron family";break;
        case ProcessorFamily::AMDOpteron6100SeriesProcessor:str="AMD Opteron 6100 series";break;
        case ProcessorFamily::AMDOpteron4100SeriesProcessor:str="AMD Opteron 4100 series";break;
        case ProcessorFamily::AMDDuronProcessorFamily:str="AMD Duron family";break;
        case ProcessorFamily::AMDAthlonXPProcessorFamily:str="AMD Athlon XP family";break;
        case ProcessorFamily::AMDAthlonX2DualCoreProcessorFamily:str="AMD Athlon X2 Dual Core family";break;
        case ProcessorFamily::AMDAthlonProcessorFamily:str="AMD Athlon family";break;
        case ProcessorFamily::AMDAthlonMPProcessorFamily:str="AMD Athlon MP family";break;
        case ProcessorFamily::AMDAthlonDualCoreProcessorFamily:str="AMD Athlon Dual Core family";break;
        case ProcessorFamily::AMDAthlon64X2DualCoreProcessorFamily:str="AMD Athlon 64 X2 Dual Core family";break;
        case ProcessorFamily::AMDAthlon64ProcessorFamily:str="AMD Athlon 64 family";break;
        case ProcessorFamily::AMDAthlon2ProcessorFamily:str="AMD Athlon 2 family";break;
        case ProcessorFamily::AMDAthlon2DualCoreMProcessorFamily:str="AMD Athlon 2 Dual Core M family";break;
        case ProcessorFamily::AMD29000Family:str="AMD 29000 family";break;
        case ProcessorFamily::AlphaFamily:str="Alpha family";break;
        case ProcessorFamily::Alpha21364:str="Alpha 21364";break;
        case ProcessorFamily::Alpha21264:str="Alpha 21264";break;
        case ProcessorFamily::Alpha21164PC:str="Alpha 21164PC";break;
        case ProcessorFamily::Alpha21164a:str="Alpha 21164a";break;
        case ProcessorFamily::Alpha21164:str="Alpha 21164";break;
        case ProcessorFamily::Alpha21066:str="Alpha 21066";break;
        case ProcessorFamily::Alpha21064:str="Alpha 21064";break;
    }
    return str;
}

String ProcessorInformation::Manufacturer()const
{
    return m_Manufacturer;
}

String ProcessorInformation::Version()const
{
    return m_Version;
}

UInt16 ProcessorInformation::ExternalClock()const
{
    return m_ExternalClock;
}

UInt16 ProcessorInformation::MaxPossibleSpeed()const
{
    return m_MaxPossibleSpeed;
}

UInt16 ProcessorInformation::CurrentSpeed()const
{
    return m_CurrentSpeed;
}

Bool ProcessorInformation::IsCPUSocketPopulated()const
{
    return m_IsCPUSocketPopulated;
}

CPUStatus::Type ProcessorInformation::Status()const
{
    return m_CPUStatus;
}

String ProcessorInformation::StatusAsString()const
{
    String str;
    switch (m_CPUStatus)
    {
        case CPUStatus::DiabledByBIOS:str="Disabled by BIOS";break;
        case CPUStatus::DisabledByUserViaBIOS:str="Disabled by user via BIOS";break;
        case CPUStatus::Enabled:str="Enabled";break;
        case CPUStatus::IdleWaitingToBeEnabled:str="Idle waiting to be enabled";break;
        case CPUStatus::Other:str="Other";break;
        case CPUStatus::Unknown:str="Unknown";break;
        case CPUStatus::Unknown1:str="Unknown1";break;
        case CPUStatus::Unknown2:str="Unknown2";break;
    }
    return str;
}

ProcessorUpgrade::Type ProcessorInformation::Upgrade()const
{
    return m_Upgrade;
}

String ProcessorInformation::UpgradeAsString()const
{
    String str;
    switch (m_Upgrade)
    {
        case ProcessorUpgrade::_370PinSocket:str="370pin socket";break;
        case ProcessorUpgrade::ZIFSocket:str="ZIF socket";break;
        case ProcessorUpgrade::Unknown:str="Unknown";break;
        case ProcessorUpgrade::SocketS1:str="Socket S1";break;
        case ProcessorUpgrade::SocketPGA988A:str="Socket PGA988A";break;
        case ProcessorUpgrade::SocketmPGA604:str="Socket mPGA604";break;
        case ProcessorUpgrade::SocketLGA775:str="Socket LGA775";break;
        case ProcessorUpgrade::SocketLGA771:str="Socket LGA771";break;
        case ProcessorUpgrade::SocketLGA1567:str="Socket LGA1567";break;
        case ProcessorUpgrade::SocketLGA1366:str="Socket LGA1366";break;
        case ProcessorUpgrade::SocketLGA1156:str="Socket LGA1156";break;
        case ProcessorUpgrade::SocketG34:str="Socket G34";break;
        case ProcessorUpgrade::SocketF:str="Socket F";break;
        case ProcessorUpgrade::SocketC32:str="Socket C32";break;
        case ProcessorUpgrade::SocketBGA1288:str="Socket BGA1288";break;
        case ProcessorUpgrade::SocketAM3:str="Socket AM3";break;
        case ProcessorUpgrade::SocketAM2:str="Socket AM2";break;
        case ProcessorUpgrade::SocketA:str="Socket A";break;
        case ProcessorUpgrade::Socket940:str="Socket 940";break;
        case ProcessorUpgrade::Socket939:str="Socket 939";break;
        case ProcessorUpgrade::Socket754:str="Socket 754";break;
        case ProcessorUpgrade::Socket478:str="Socket 478";break;
        case ProcessorUpgrade::Socket423:str="Socket 423";break;
        case ProcessorUpgrade::SlotM:str="Slot M";break;
        case ProcessorUpgrade::SlotA:str="Slot A";break;
        case ProcessorUpgrade::Slot2:str="Slot 2";break;
        case ProcessorUpgrade::Slot1:str="Slot 1";break;
        case ProcessorUpgrade::ReplaceablePiggyBack:str="Replaceable piggy back";break;
        case ProcessorUpgrade::Other:str="Other";break;
        case ProcessorUpgrade::None:str="None";break;
        case ProcessorUpgrade::LIFSocket:str="LIF socket";break;
        case ProcessorUpgrade::DaughterBoard:str="Daughter board";break;
    }
    return str;
}

UInt32 ProcessorInformation::CacheCount()const
{
    return m_Caches.Size();
}

const CacheInformation& ProcessorInformation::Cache(UInt32 Index)const
{
    return *m_Caches[Index];
}

String ProcessorInformation::SerialNumber()const
{
    return m_SerialNumber;
}

String ProcessorInformation::AssetTag()const
{
    return m_AssetTag;
}

String ProcessorInformation::PartNumber()const
{
    return m_PartNumber;
}

UInt8 ProcessorInformation::CoreCount()const
{
    return m_CoreCount;
}

UInt8 ProcessorInformation::EnabledCoreCount()const
{
    return m_EnabledCoreCount;
}

UInt8 ProcessorInformation::MaxSupportedThreadCount()const
{
    return m_MaxSupportedThreadCount;
}

ProcessorCharacteristics::Type ProcessorInformation::CharacteristicsBitField()const
{
    return m_CharacteristicsBitField;
}

Bool ProcessorInformation::IsFeatureSupported( ProcessorFeatures::Type Feature )const
{
    return m_Features[Feature];
}
