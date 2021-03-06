#ifndef RF_SYSTEM_HARDWARE_PROCESSORFEATURES_HPP
#define RF_SYSTEM_HARDWARE_PROCESSORFEATURES_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/BitSet.hpp>

namespace RadonFramework::System::Hardware::ProcessorFeatures {

enum Type
{
    AES, // Advanced Encryption Standard instruction set
    AVX, // Advanced Vector Extensions instruction set
    CLFLUSH, // Prefetch and flush instructions
    CMOV, // conditional move instruction
    CX16, // compare and exchange 16 bytes instruction
    CX8, // compare and exchange 8 bytes instruction
    FMA, // FMA instruction set
    FMOV, // floating point conditional move instruction
    FPU, // Floating point unit
    HTT, // hyper threading
    MMX, // MMX instruction set
    MOVBE, // move big endian instruction                
    PCLMUL, // carry-less multiplication instruction
    POPCNT, // population count instruction
    SSE, // SSE1 instruction set
    SSE2, // SSE2 instruction set
    SSE3, // SSE3 instruction set
    SSSE3, // SSE4 instruction set
    SSE4_1, // SSE4.1 instruction set
    SSE4_2, // SSE4.2 instruction set
    SSE4A, // SSE4a instruction set
    TSC, // RDTSC instruction supported
    SHA1, // sha128 hash instruction set
    SHA2, // sha256 hash instruction set
    AVX512, // AVX512 instruction set
    FMA4, // FMA4 instruction set
    XOP, // XOP instruction set
    NEON, // NEON instruction set(ARM only)
    CRC32, // CRC32 instructions set(ARM only)
    MAX // number of extensions(internal use)
};

}

namespace RadonFramework::System::Hardware {

class ProcessorFeatureMask: public Collections::BitSet<ProcessorFeatures::MAX>
{
};

}

#endif // RF_SYSTEM_HARDWARE_PROCESSORFEATURES_HPP