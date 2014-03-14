#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/CPUID.hpp"
#include <string.h>

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

AutoPointerArray<UInt8> CPUID::MakeDump(UInt32 Count, Level* Levels)
{
    UInt32 size=sizeof(Level)*Count+4;
    AutoPointerArray<UInt8> result(new UInt8[size],size);
    *reinterpret_cast<UInt32*>(result.Get())=Count;
    RFMEM::Copy(result.Get()+4,Levels,size-4);
    return result;
}

void CPUID::ReadDump(CPUID& Destination, AutoPointerArray<UInt8> BinaryData)
{
    Destination.m_Data=BinaryData;
}

UInt32 CPUID::Count()const
{
    return *reinterpret_cast<UInt32*>(m_Data.Get());
}

const Level& CPUID::GetLevel(UInt32 Index)const
{
    return reinterpret_cast<Level*>(m_Data.Get()+4)[Index];
}

const Level* CPUID::GetLevelByID(Int32 Code)const
{
    const Level* result=0;
    for (UInt32 i=0;i<Count();++i)
    {
        const Level& level=GetLevel(i);
        if (level.Code==Code)
        {
            result=&level;
            break;
        }
    }
    return result;
}

UInt32 CPUID::MaxStandardLevel()const
{
    if (Count()==0)
        return 0;
    return reinterpret_cast<Level*>(m_Data.Get()+4)[0].Registers[0];
}

UInt32 CPUID::MaxExtendedLevel()const
{
    UInt32 maxStdLvl=MaxStandardLevel();
    if (maxStdLvl==0 || maxStdLvl==Count()-1)
        return 0;
    return reinterpret_cast<Level*>(m_Data.Get()+4)[maxStdLvl].Registers[0];
}

const AutoPointerArray<UInt8>& CPUID::Data()const
{
    return m_Data;
}