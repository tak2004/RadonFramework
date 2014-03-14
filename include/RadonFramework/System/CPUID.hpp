#ifndef RF_SYSTEM_CPUID_HPP
#define RF_SYSTEM_CPUID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace System
    {
        struct Level
        {
            RFTYPE::Int32 Code;
            RFTYPE::UInt32 Registers[4];
        };

        class CPUID
        {
            public:
                static RadonFramework::Memory::AutoPointerArray<RFTYPE::UInt8> MakeDump(
                    RFTYPE::UInt32 Count, Level* Levels);
                static void ReadDump(CPUID& Destination, 
                    RadonFramework::Memory::AutoPointerArray<RFTYPE::UInt8> BinaryData);

                RFTYPE::UInt32 Count()const;
                const Level& GetLevel(RFTYPE::UInt32 Index)const;
                const Level* GetLevelByID(RFTYPE::Int32 Code)const;
                RFTYPE::UInt32 MaxStandardLevel()const;
                RFTYPE::UInt32 MaxExtendedLevel()const;
                const RadonFramework::Memory::AutoPointerArray<RFTYPE::UInt8>& Data()const;

                // Magic numbers
                static const RFTYPE::UInt32 BITMASK_AES=0x2000000;
                static const RFTYPE::UInt32 BITMASK_AVX=0x10000000;
                static const RFTYPE::UInt32 BITMASK_CLFLUSH=0x80000;
                static const RFTYPE::UInt32 BITMASK_CMOV=0x8000;
                static const RFTYPE::UInt32 BITMASK_CX16=0x2000;
                static const RFTYPE::UInt32 BITMASK_CX8=0x100;
                static const RFTYPE::UInt32 BITMASK_FMA=0x1000;
                static const RFTYPE::UInt32 BITMASK_FMOV=0x8001;
                static const RFTYPE::UInt32 BITMASK_FPU=1;
                static const RFTYPE::UInt32 BITMASK_HTT=0x10000000;
                static const RFTYPE::UInt32 BITMASK_MMX=0x800000;
                static const RFTYPE::UInt32 BITMASK_MOVBE=0x400000;
                static const RFTYPE::UInt32 BITMASK_PCLMUL=2;
                static const RFTYPE::UInt32 BITMASK_POPCNT=0x800000;
                static const RFTYPE::UInt32 BITMASK_SSE=0x2000000;
                static const RFTYPE::UInt32 BITMASK_SSE2=0x4000000;
                static const RFTYPE::UInt32 BITMASK_SSE3=1;
                static const RFTYPE::UInt32 BITMASK_SSSE3=0x200;
                static const RFTYPE::UInt32 BITMASK_SSE4_1=0x80000;
                static const RFTYPE::UInt32 BITMASK_SSE4_2=0x100000;
                static const RFTYPE::UInt32 BITMASK_TSC=0x10;
                // Logical processor count
                static const RFTYPE::UInt32 BITMASK_LPCOUNT=0xFF0000;
                static const RFTYPE::UInt32 SHIFT_LPCOUNT=16;
                // Cores per Package
                static const RFTYPE::UInt32 BITMASK_CPP=0x3F0000;
                static const RFTYPE::UInt32 SHIFT_CPP=26;
            protected:
                RadonFramework::Memory::AutoPointerArray<RFTYPE::UInt8> m_Data;
        };
    }
}

#endif // RF_SYSTEM_CPUID_HPP