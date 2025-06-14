export module rf.core.cpu:infos;
import rf.core.types;
import rf.core.memory;

export namespace rf {
enum class Features : u8 {
  FPU,     // Floating point unit
  VME,     // Virtual 8086 mode
  PSE,     // Page size extension
  TSC,     // RDTSC instruction supported
  PAE,     // Page size extension
  CX8,     // compare and exchange 8 bytes instruction
  CMOV,    // conditional move instruction
  CLFLUSH, // Prefetch and flush instructions
  MMX,     // MMX instruction set
  SSE,     // SSE1 instruction set
  SSE2,    // SSE2 instruction set
  HTT,     // hyper threading
  IA64,    // IA64 processor emulating x64

  SSE3,   // SSE3 instruction set
  PCLMUL, // carry-less multiplication instruction
  SSSE3,  // SSE4 instruction set
  FMA,    // FMA instruction set
  CX16,   // compare and exchange 16 bytes instruction
  SSE4_1, // SSE4.1 instruction set
  SSE4_2, // SSE4.2 instruction set
  MOVBE,  // move big endian instruction
  POPCNT, // population count instruction
  AES,    // Advanced Encryption Standard instruction set
  AVX,    // Advanced Vector Extensions instruction set
  F16C,   // Half-precision float conversion feature
  RDRND,  // On-chip random number generator

  BMI1,            // Bit Manipulation Instruction Set 1
  HLE,             // TXS Hardware Lock Elision
  AVX2,            // Advanced Vector Extensions 2 instruction set
  BMI2,            // Bit Manipulation Instruction Set 2
  ERMS,            // Enhanced REP MOVSB/STOSB(useful from 256bytes and up)
  MPX,             // Intel Memory Protection Extensions
  AVX512F,         // AVX512 Foundation instruction set
  AVX512DQ,        // AVX512 Doubleword and Quadword Instructions
  RDSEED,          // RDSEED instruction
  AVX512IFMA,      // AVX-512 Integer Fused Multiply-Add Instructions
  CLFLUSHOPT,      // CLFLUSHOPT instruction
  CLWB,            // CLWB instruction
  IntelPT,         // Intel Processor Trace
  AVX512PF,        // AVX512PF instruction set
  AVX512ER,        // AVX512ER instruction set
  AVX512CD,        // AVX512CD instruction set
  SHA1,            // sha128 hash instruction set
  SHA2,            // sha256 hash instruction set
  AVX512BW,        // AVX-512 Byte and Word Instructions
  AVX512VL,        // AVX-512 Vector Length Extensions
  PREFETCHWT1,     // PREFETCHWT1 instruction
  AVX512VBMI,      // AVX-512 Vector Bit Manipulation Instructions
  AVX512VBMI2,     // AVX-512 Vector Bit Manipulation Instructions 2
  GFNI,            // Galois Field instructions
  VAES,            // Vector AES instruction set
  VPCLMULQDQ,      // CLMUL instruction set (VEX-256/EVEX)
  AVX512VNNI,      // AVX-512 Vector Neural Network Instructions
  AVX512BITALG,    // AVX-512 BITALG instructions
  AVX512VPOPCNTDQ, // AVX-512 Vector Population Count Double and Quad-word
  CLDEMOTE,        // Cache line demote
  MOVDIRI,
  MOVDIR64B,
  AVX512_4VNNIW, // AVX-512 4-register Neural Network Instructions
  AVX512_4FMAPS, // AVX-512 4-register Multiply Accumulation Single precision
  FSRM,          // Fast Short REP MOVSB(useful for up to 128byte load/store)
  AVX512_VP2I,   // AVX-512 VP2INTERSECT Doubleword and Quadword Instructions
  AVX512_BF16,   // AVX-512 BFLOAT16 instructions
  MP,            // Multiprocessor Capable
  MMXEXT,        // Extended MMX
  PDPE1GB,       //  Gibibyte pages
  RDTSCP,        // RDTSCP instruction
  ABM,           // Advanced bit manipulation (lzcnt and popcnt)
  MisalignSSE,   // Misaligned SSE mode
  Prefetch3DNow, // PREFETCH and PREFETCHW instructions
  IBS,           // Instruction Based Sampling
  SSE4A,         // SSE4a instruction set
  XOP,           // XOP instruction set
  FMA4,          // FMA4 instruction set
  TBM,           // Trailing Bit Manipulation
  PERFCTR_CORE,  // Core performance counter extensions
  PERFCTR_NB,    // NB performance counter extensions
  PERFTSC,       // Performance TSC
  PCX_L2I,       // L2I perf counter extensions

  NEON, // NEON instruction set(ARM only)
  CRC32 // CRC32 instructions set(ARM only)
};

struct InstructionSet {
  static constexpr auto UsedBits = static_cast<u8>(Features::CRC32);
  static constexpr auto UsedBytes = UsedBits / 8;

  // Serialize the data to disk and use loadFrom to speedup the startup.
  bool data[static_cast<u32>(Features::CRC32)];
  // Detect all supported instruction sets of your CPU.
  InstructionSet &detect();
  // Instead of detecting the supported instruction sets they are loaded from
  // the specified memory.
  InstructionSet &loadFrom(constmem &Memory) {
    if (Memory.bytes == UsedBytes) {
      for (auto i = 0; i < UsedBytes; ++i)
        this->data[i] = reinterpret_cast<u8 const *>(Memory.address)[i];
    }
    return *this;
  }
  bool has(Features Feature) const {
    return this->data[static_cast<u32>(Feature)];
  }
};
// Start with the basic x64v1 features. 
// Use the detect function before calling any function to allow the dispatcher
// to choose the fastest supported implementation.
InstructionSet CPUFeatures = { .data = {
    true,true,true,true,true,true,true,true,true,true,true,
    false // all false
} };

enum class CacheAssociativity : u8 {
  Unknown,
  _2WaySetAssociative,
  _4WaySetAssociative,
  _6WaySetAssociative,
  _8WaySetAssociative,
  _12WaySetAssociative,
  _16WaySetAssociative,
  _24WaySetAssociative,
  FullyAssociative,
  Other
};

enum class CacheUseCase : u8 {
  Unknown,
  Data,
  Code,
  CodeAndData,
  CodeTLB,
  DataTLB,
  CodeAndDataTLB,
  Other
};

// Contains the information about a single cache.
struct CacheInfo {
  /// Cache size.
  u32 bytes;
  /// Cache line size in bytes.
  u16 lineBytes;
  /// Determine the cache level.
  u8 level;
  /// How does the cache will by filled.
  CacheAssociativity associativity;
  /// Describe the purpose of how the cache is used.
  CacheUseCase usedAs;
  /// This field is currently used as padding to fit into 16byte.
  u8 ReservedPadding[7];
};

// Commonly many core CPUs use the same cache layout for each logical processor.
struct CacheStack {
  union {
    bool mask[32];
    u32 raw;
  };
};

struct CacheLayout {
  mem data;
  CacheStack* lpCacheMask;
  CacheInfo* cacheInfos;
  struct View{
    u32 lps;
    u32 caches;
  } view;
  // Determine the necessary memory size to run the detect function.
  static size estimateScratchpad();
  // The function will use the Scratchpad for temporary data but also write the
  // final compact version to the data member. You need to clone and load this
  // to a persistent arena if you plan to throw away the Scratchpad arena.
  CacheLayout &detect(StackAdapter& Scratchpad);
  // Specify a memory block which will be read and used.
  CacheLayout &loadFrom(mem &Memory) {
    this->data = Memory;
    this->view = *reinterpret_cast<View*>(Memory.address);
    this->lpCacheMask = reinterpret_cast<CacheStack*>(offset(Memory, sizeof(View)));
    this->cacheInfos = reinterpret_cast<CacheInfo *>(
        offset(Memory, sizeof(View) + this->view.lps * sizeof(CacheStack)));
    return *this;
  }
  CacheInfo *get(u32 LogicalProcessor, u8 Level = 1,
                 CacheUseCase Kind = CacheUseCase::Data) {
    CacheInfo* result = nullptr;
    if (data.address != nullptr && LogicalProcessor < this->view.lps) {
      for (auto i = 0; i < sizeof(CacheStack)*8; ++i) {
          if (this->lpCacheMask[LogicalProcessor].mask[i]) {
              if (this->cacheInfos[i].usedAs == Kind && this->cacheInfos[i].level == Level) {
                  result = this->cacheInfos + i;
                  break;
              }
          }        
      }
    }
    return result;
  }
};
} // namespace rf