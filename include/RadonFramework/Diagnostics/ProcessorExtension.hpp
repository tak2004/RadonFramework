#ifndef RF_DIAGNOSTICS_PROCESSOREXTENSION_HPP
#define RF_DIAGNOSTICS_PROCESSOREXTENSION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace ProcessorExtension
        {
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
                TSC, // RDTSC instruction supported
                MAX // number of extensions(internal use)
            };
        }
    }
}

#endif // RF_DIAGNOSTICS_PROCESSOREXTENSION_HPP