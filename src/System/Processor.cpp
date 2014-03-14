#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Processor.hpp"
#include "RadonFramework/Diagnostics/ProcessorData.hpp"
#include "RadonFramework/Collections/Array.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/CPUID.hpp"
#include "RadonFramework/IO/Log.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

extern void cpuidex(Int32 code, UInt32 registers[4], Int32 ECXRegister);
extern void cpuid(Int32 code, UInt32 registers[4]);
extern UInt32 clz( UInt32 x );
extern UInt32 LogicalProcessorCount();
extern UInt32 RunCodeOnLogicalProcessor(UInt32 Mask);
extern Bool IsRunningOnAllProcessors();

static ProcessorSharedData* processorSharedData = 0;

// external functions
Bool LoadLogicalProcessorInfo(CPUID& Destination)
{
    UInt32 count=0;
    UInt32 lastCount=0;
    Level* levels=0;
    Level* p=0;
    UInt32 reg[4]={0,0,0,0};

    // is cpuid supported
    cpuid(0,reg);

    // read maximum supported standard level
    count=1+reg[0];
    if (count>1)
    {
        levels=new Level[count];
        levels[0].Code=0;
        RFMEM::Copy(levels[0].Registers,reg,16);

        for (UInt32 i=1;i<count;++i)
        {
            if (i==11)
                cpuidex(i,reg,0);
            else
                cpuid(i,reg);
            levels[i].Code=i;
            RFMEM::Copy(levels[i].Registers,reg,16);
        }

        // read maximum supported extended level
        cpuid(RFTYPE::Int32Min, reg);
        lastCount=count;
        count+=reg[0]-RFTYPE::Int32Min;
        p=new Level[count];
        RFMEM::Copy(p,levels,sizeof(Level)*lastCount);
        delete[] levels;    
        levels=p;
        levels[lastCount].Code=RFTYPE::Int32Min;
        RFMEM::Copy(levels[lastCount].Registers,reg,16);

        UInt32 id=0;
        for (UInt32 i=lastCount+1;i<count;++i)
        {
            id=i+RFTYPE::Int32Min-lastCount;
            cpuid(id,reg);
            levels[i].Code=id;
            RFMEM::Copy(levels[i].Registers,reg,16);
        }

        CPUID::ReadDump(Destination,CPUID::MakeDump(count,levels));
        delete[] levels;
    }
    return true;
}

void DetectExtensionsInternal(const UInt32 Registers[4], ProcessorSharedData& Data)
{
    Data.Extensions[ProcessorExtension::AES]=(Registers[2] & CPUID::BITMASK_AES)!=0;
    Data.Extensions[ProcessorExtension::AVX]=(Registers[2] & CPUID::BITMASK_AVX)!=0;
    Data.Extensions[ProcessorExtension::CLFLUSH]=(Registers[3] & CPUID::BITMASK_CLFLUSH)!=0;
    Data.Extensions[ProcessorExtension::CMOV]=(Registers[3] & CPUID::BITMASK_CMOV)!=0;
    Data.Extensions[ProcessorExtension::CX16]=(Registers[2] & CPUID::BITMASK_CX16)!=0;
    Data.Extensions[ProcessorExtension::CX8]=(Registers[3] & CPUID::BITMASK_CX8)!=0;
    Data.Extensions[ProcessorExtension::FMA]=(Registers[2] & CPUID::BITMASK_FMA)!=0;
    Data.Extensions[ProcessorExtension::FMOV]=(Registers[3] & CPUID::BITMASK_FMOV)!=0;    
    Data.Extensions[ProcessorExtension::FPU]=(Registers[3] & CPUID::BITMASK_FPU)!=0;
    Data.Extensions[ProcessorExtension::HTT]=(Registers[3] & CPUID::BITMASK_HTT)!=0;
    Data.Extensions[ProcessorExtension::MMX]=(Registers[3] & CPUID::BITMASK_MMX)!=0;
    Data.Extensions[ProcessorExtension::MOVBE]=(Registers[2] & CPUID::BITMASK_MOVBE)!=0;
    Data.Extensions[ProcessorExtension::PCLMUL]=(Registers[2] & CPUID::BITMASK_PCLMUL)!=0;
    Data.Extensions[ProcessorExtension::POPCNT]=(Registers[2] & CPUID::BITMASK_POPCNT)!=0;
    Data.Extensions[ProcessorExtension::SSE]=(Registers[3] & CPUID::BITMASK_SSE)!=0;
    Data.Extensions[ProcessorExtension::SSE2]=(Registers[3] & CPUID::BITMASK_SSE2)!=0;
    Data.Extensions[ProcessorExtension::SSE3]=(Registers[2] & CPUID::BITMASK_SSE3)!=0;
    Data.Extensions[ProcessorExtension::SSSE3]=(Registers[2] & CPUID::BITMASK_SSSE3)!=0;
    Data.Extensions[ProcessorExtension::SSE4_1]=(Registers[2] & CPUID::BITMASK_SSE4_1)!=0;
    Data.Extensions[ProcessorExtension::SSE4_2]=(Registers[2] & CPUID::BITMASK_SSE4_2)!=0;
    Data.Extensions[ProcessorExtension::TSC]=(Registers[3] & CPUID::BITMASK_TSC)!=0;
}

const ProcessorSharedData& RadonFramework::System::LoadSharedProcessorInfo()
{
    if (processorSharedData == 0)
    {
        UInt32 reg[4]={0,0,0,0};
        // is cpuid supported
        cpuid(0, reg);
        if (reg[0] > 0)
        {
            cpuid(1, reg);
            processorSharedData = new ProcessorSharedData;
            DetectExtensionsInternal(reg, *processorSharedData);
            if ((reg[3] & CPUID::BITMASK_CLFLUSH)!=0)// is CLFLUSH available
                processorSharedData->CacheLineSize = (reg[1]&0xFF00)>>5;
        }
    }
    return *processorSharedData;
}

void DetectExtensions(CPUID& CPUInfo,ProcessorData& Data)
{
    const Level* level=CPUInfo.GetLevelByID(1);
    if(level)
    {
        DetectExtensionsInternal(level->Registers, Data.SharedData);
    }
    else
        LogInfo("Can't determinate processor features. This will be affect the performance.");
}

void DetectCaches(CPUID& CPUInfo,ProcessorData& Data)
{
    const Level* level=CPUInfo.GetLevelByID(1);
    if(level)
        if ((level->Registers[3] & CPUID::BITMASK_CLFLUSH)!=0)// is CLFLUSH available
        {
            Data.SharedData.CacheLineSize=(level->Registers[1]&0xFF00)>>5;
            return;
        }
    LogInfo("Can't determinate CacheLineSize. This will be affect the performance.");
}

void DetectName(CPUID& CPUInfo,ProcessorData& Data)
{
    // find CPU type name
    const Level* level=CPUInfo.GetLevelByID(0);
    if(level)
    {
        char* p=const_cast<char*>(Data.Name.c_str());
        *reinterpret_cast<Int32*>(p)=level->Registers[1];
        *reinterpret_cast<Int32*>(p+4)=level->Registers[3];
        *reinterpret_cast<Int32*>(p+8)=level->Registers[2];
    }
    else
        Data.Name="Unknown";

    // find CPU brand name
    level=CPUInfo.GetLevelByID(RFTYPE::Int32Min);
    if (level)
    {
        if (level->Registers[0]>=static_cast<UInt32>(RFTYPE::Int32Min+4))
        {
            char* p=const_cast<char*>(Data.Brand.c_str());
            for (RFTYPE::Size i=RFTYPE::Int32Min+2; i<RFTYPE::Int32Min+5; ++i)
            {
                level=CPUInfo.GetLevelByID(static_cast<Int32>(i));
                RFMEM::Copy(p,level->Registers,16);
                p=p+16;
            }
            return;
        }        
    }
    Data.Brand="Unknown";
}

UInt32 GetMaxNumLPPerPackage(CPUID& CPUInfo)
{
    const Level* level=CPUInfo.GetLevelByID(1);
    if (level)
    {
        if ((level->Registers[3] & CPUID::BITMASK_HTT)==0)
            return 1;

        return (level->Registers[1] & CPUID::BITMASK_LPCOUNT)>>CPUID::SHIFT_LPCOUNT;
    }
    return 1;
}

UInt32 GetMaxNumCoresPerPackage(CPUID& CPUInfo)
{
    const Level* level=CPUInfo.GetLevelByID(1);
    UInt32 cores=0;
    if (level)
    {
        if ((level->Registers[3] & CPUID::BITMASK_HTT)==0)
            return 1;

        if(CPUInfo.MaxStandardLevel()>=4)
        {
            level=CPUInfo.GetLevelByID(4);
            cores=(level->Registers[0]&CPUID::BITMASK_CPP)>>CPUID::SHIFT_CPP;
        }
    }
    return cores+1;
}

UInt32 FindMaskWidth(UInt32 CountItem)
{
    UInt32 maskWidth=0;
    if (CountItem>1)
        maskWidth=clz(CountItem);
    return maskWidth;
}

UInt32 DetectID(CPUID& CPUInfo)
{
    UInt32 result=0;
    const Level* level=CPUInfo.GetLevelByID(1);
    if (level)
    {
        if (CPUInfo.MaxStandardLevel()>=11)
        {// 2xAPIC ID(new CPUs)
            level=CPUInfo.GetLevelByID(11);
            result=level->Registers[3];
        }

        if (result==0)
        {// APIC ID(old CPUs)
            level=CPUInfo.GetLevelByID(1);
            result=level->Registers[1]>>24;
        }
    }
    return result;
}

UInt32 BelongsToCPUCore(CPUID& CPUInfo, UInt32 ID)
{
    UInt32 result=ID;
    const Level* level=CPUInfo.GetLevelByID(1);
    if (level)
    {
        if ((level->Registers[3] & CPUID::BITMASK_HTT)==0)
            result&=0xFFFFFFFE;
    }
    return result;
}

UInt32 BelongsToCPU(CPUID& CPUInfo, UInt32 ID)
{
    UInt32 result=ID;
    result&=RFTYPE::UInt32Max<<FindMaskWidth(GetMaxNumLPPerPackage(CPUInfo));
    return result;
}

UInt32 RadonFramework::System::GetLogicalProcessorCount(const Array<ProcessorData>& Processors)
{
    UInt32 result=0;
    for (UInt32 i=0;i<Processors.Count();++i)
        result+=Processors(i).LogicalProcessorCount;
    return result;
}

Bool RadonFramework::System::GetProcessorInfoDump(UInt32 Index, CPUID& Out)
{
    Bool result=false;
    UInt32 count=LogicalProcessorCount();
    if (Index<count)
    {
        UInt32 mask=RunCodeOnLogicalProcessor(1<<Index);
        // following code will be executed on the specified core
        result=LoadLogicalProcessorInfo(Out);
        // reset processor assignment for process
        RunCodeOnLogicalProcessor(mask);
    }
    return result;
}

void RadonFramework::System::DetectProcessors(Array<ProcessorData>& out)
{
    if (IsRunningOnAllProcessors())// used by the OS
    {
        // cleanup
        out.Resize(0);

        UInt32 count=LogicalProcessorCount(); // available due OS 
        UInt32 id=0,cpuid=0,coreid=0;
        Array<UInt32> cpuids;
        Array<UInt32> ids(count);
        UInt32 idLength=0;
        CPUID data;
        ProcessorData processor;
        for (UInt32 i=0;i<count;++i)
        {           
            if (GetProcessorInfoDump(i,data))
            {
                Memory::Set(&processor, 0, sizeof(ProcessorData));

                DetectExtensions(data, processor);
                DetectCaches(data, processor);
                DetectName(data, processor);
                id=DetectID(data);                    
                // collect core IDs to get core count of each cpu
                coreid=BelongsToCPUCore(data,id);
                if (ids.IndexOf(coreid)<0 || idLength==0)
                {
                    ids(idLength)=coreid;
                    ++idLength;
                }
                // collect cpu IDs to get the cpu count
                cpuid=BelongsToCPU(data, id);
                if (cpuids.Count()==0 || cpuids.IndexOf(cpuid)<0)
                {
                    cpuids.Resize(cpuids.Count()+1);
                    cpuids(cpuids.Count()-1)=cpuid;
                    out.Resize(out.Count()+1);
                    out(out.Count()-1)=processor;
                }
                // increase logical processor count for the specified cpu
                ++out(cpuids.IndexOf(cpuid)).LogicalProcessorCount;
            }
            else
                LogError("Processor detection isn't supported on this system.\
                            This will be have an impact on performance and availability\
                            of some features.");
        }
        for (UInt32 i=0;i<idLength;++i)
        {
            cpuid=BelongsToCPU(data, ids(i));
            ++out(cpuids.IndexOf(cpuid)).CoreCount;
        }
    }
    else
        LogInfo("This process can't run on all processors. This can affect\
                the identification of all CPUs.");
}
