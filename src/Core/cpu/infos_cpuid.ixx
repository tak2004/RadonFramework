export module rf.core.cpu:infos_cpuid;
import rf.core.types;
import :infos;
import :intrinsics;

void HighestExtendedFunctions(bool *Flags);
void ExtendedFunctions(bool *Flags);

export namespace rf {
InstructionSet &InstructionSet::detect() {
  ::ExtendedFunctions(this->data);
  ::HighestExtendedFunctions(this->data);
  return *this;
}
} // namespace rf

void ExtendedFunctions(bool *Flags) {
  rf::i32 registers[4];
  rf::cpuid(0, 0, registers);
  auto totalIDs = registers[0];
  if (totalIDs >= 7) {
    rf::cpuid(7, 0, registers);
    // 1 reserved
    // 2 reserved
    Flags[static_cast<rf::i32>(rf::Features::AVX512_4VNNIW)] |=
        (registers[3] & 4) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512_4FMAPS)] |=
        (registers[3] & 8) != 0;
    Flags[static_cast<rf::i32>(rf::Features::FSRM)] |= (registers[3] & 16) != 0;
    // 32 reserved
    // 64 reserved
    Flags[static_cast<rf::i32>(rf::Features::AVX512_VP2I)] |=
        (registers[3] & 128) != 0;
    // 256 reserved
    // 512 VERW instruction clears CPU buffers
    // 1024 reserved
    // 2048 reserved
    // 4096 tsx_force_abort
    // 8192 Serialize instruction execution
    // 1<<15 Hybrid
    // 1<<16 TSX suspend load address tracking
    // 1<<17 reserved
    // 1<<18 Platform configuration (Memory Encryption Technologies
    // Instructions) 1<<19 reserved 1<<20 Control flow enforcement (CET)
    // indirect branch tracking 1<<21 reserved 1<<22 reserved 1<<23 reserved
    // 1<<24 reserved
    // 1<<25 reserved
    // 1<<26 IBRS_IBPB / spec_ctrl
    // 1<<27 Single Thread Indirect Branch Predictor, part of IBC
    // 1<<28 reserved
    // 1<<29 Speculative Side Channel Mitigations
    // 1<<30 Support for a MSR listing model-specific core capabilities
    // 1<<31 Speculative Store Bypass Disable,[18] as mitigation for Speculative
    // Store Bypass

    Flags[static_cast<rf::i32>(rf::Features::PREFETCHWT1)] |=
        (registers[2] & 1) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512VBMI)] |=
        (registers[2] & 2) != 0;
    // 4 User-mode Instruction Prevention
    // 8 Memory Protection Keys for User-mode pages
    // 16 PKU enabled by OS
    // 32 waitpkg
    Flags[static_cast<rf::i32>(rf::Features::AVX512VBMI2)] |=
        (registers[2] & 64) != 0;
    // 128 Control flow enforcement (CET) shadow stack
    Flags[static_cast<rf::i32>(rf::Features::GFNI)] |= (registers[2] & 256) != 0;
    Flags[static_cast<rf::i32>(rf::Features::VAES)] |= (registers[2] & 512) != 0;
    Flags[static_cast<rf::i32>(rf::Features::VPCLMULQDQ)] |=
        (registers[2] & 1024) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512VNNI)] |=
        (registers[2] & 2048) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512BITALG)] |=
        (registers[2] & 4096) != 0;
    // 8192 reserved
    Flags[static_cast<rf::i32>(rf::Features::AVX512VPOPCNTDQ)] |=
        (registers[2] & 1 << 14) != 0;
    // 1<<15 reserved
    // 1<<16 5-level paging
    // 1<<17 mawau
    // 1<<18 mawau
    // 1<<19 mawau
    // 1<<20 mawau
    // 1<<21 mawau
    // 1<<22 rdpid
    // 1<<23 reserved
    // 1<<24 reserved
    Flags[static_cast<rf::i32>(rf::Features::CLDEMOTE)] |=
        (registers[2] & 1 << 25) != 0;
    // 1<<26 reserved
    Flags[static_cast<rf::i32>(rf::Features::MOVDIRI)] |=
        (registers[2] & 1 << 27) != 0;
    Flags[static_cast<rf::i32>(rf::Features::MOVDIR64B)] |=
        (registers[2] & 1 << 28) != 0;
    // 1<<29 Enqueue Stores
    // 1<<30 SGX Launch Configuration
    // 1<<31 Protection keys for supervisor-mode pages

    // 1 fsgsbasef
    // 2 IA32_TSC_ADJUST
    // 4 Software Guard Extensions
    Flags[static_cast<rf::i32>(rf::Features::BMI1)] |= (registers[1] & 8) != 0;
    Flags[static_cast<rf::i32>(rf::Features::HLE)] |= (registers[1] & 16) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX2)] |= (registers[1] & 32) != 0;
    // 64 Reserved
    // 128 Supervisor Mode Execution Preventionn
    Flags[static_cast<rf::i32>(rf::Features::BMI2)] |= (registers[1] & 256) != 0;
    Flags[static_cast<rf::i32>(rf::Features::ERMS)] |= (registers[1] & 512) != 0;
    // 1024 INVPCID instruction
    // 2048 TSX Restricted Transactional Memory
    // 4096 Platform Quality of Service Monitoring
    // 8192 FPU CS and FPU DS deprecated
    Flags[static_cast<rf::i32>(rf::Features::MPX)] |= (registers[1] & 1 << 14) != 0;
    // 1<<15 Platform Quality of Service Enforcement
    Flags[static_cast<rf::i32>(rf::Features::AVX512F)] |=
        (registers[1] & 1 << 16) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512DQ)] |=
        (registers[1] & 1 << 17) != 0;
    Flags[static_cast<rf::i32>(rf::Features::RDSEED)] |=
        (registers[1] & 1 << 18) != 0;
    // 1<<19 Multi-Precision Add-Carry Instruction Extensions
    // 1<<20 Supervisor Mode Access Prevention
    Flags[static_cast<rf::i32>(rf::Features::AVX512IFMA)] |=
        (registers[1] & 1 << 21) != 0;
    // 1<<22 PCOMMIT instruction
    Flags[static_cast<rf::i32>(rf::Features::CLFLUSHOPT)] |=
        (registers[1] & 1 << 23) != 0;
    Flags[static_cast<rf::i32>(rf::Features::CLWB)] |=
        (registers[1] & 1 << 24) != 0;
    Flags[static_cast<rf::i32>(rf::Features::IntelPT)] |=
        (registers[1] & 1 << 25) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512PF)] |=
        (registers[1] & 1 << 26) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512ER)] |=
        (registers[1] & 1 << 27) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512CD)] |=
        (registers[1] & 1 << 28) != 0;
    // sha-1 and -256 are on the same flag
    Flags[static_cast<rf::i32>(rf::Features::SHA1)] |=
        (registers[1] & 1 << 29) != 0;
    Flags[static_cast<rf::i32>(rf::Features::SHA2)] |=
        (registers[1] & 1 << 29) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512BW)] |=
        (registers[1] & 1 << 30) != 0;
    Flags[static_cast<rf::i32>(rf::Features::AVX512VL)] |=
        (registers[1] & 1 << 31) != 0;

    rf::cpuid(7, 1, registers);
    Flags[static_cast<rf::i32>(rf::Features::AVX512_BF16)] |=
        (registers[0] & 16) != 0;
  }
  if (totalIDs >= 1) {
    rf::cpuid(1, 0, registers);
    Flags[static_cast<rf::i32>(rf::Features::FPU)] |= (registers[3] & 1) != 0;
    Flags[static_cast<rf::i32>(rf::Features::VME)] |= (registers[3] & 2) != 0;
    // 4 debugging extensions
    Flags[static_cast<rf::i32>(rf::Features::PSE)] |= (registers[3] & 8) != 0;
    Flags[static_cast<rf::i32>(rf::Features::TSC)] |= (registers[3] & 16) != 0;
    // 32 model-specific registers
    Flags[static_cast<rf::i32>(rf::Features::PAE)] |= (registers[3] & 64) != 0;
    // 128 Machine check exception
    Flags[static_cast<rf::i32>(rf::Features::CX8)] |= (registers[3] & 256) != 0;
    // 512 APIC
    // 1024 Reserved
    // 2048 SYSENTER and SYSEXIT instructions
    // 4096 Memory Type Range Registers
    // 8192 Page Global Enabled
    // 1<<14 Machine check architecture
    Flags[static_cast<rf::i32>(rf::Features::CMOV)] |=
        (registers[3] & 1 << 15) != 0;
    // 1<<16 Page Attribute Table
    // 1<<17 36-bit page size extension
    // 1<<18 Processor Serial Number
    Flags[static_cast<rf::i32>(rf::Features::CLFLUSH)] |=
        (registers[3] & 1 << 19) != 0;
    // 1<<20 Reserved
    // 1<<21 Debug store
    // 1<<22 ACPI
    Flags[static_cast<rf::i32>(rf::Features::MMX)] |= (registers[3] & 1 << 23) != 0;
    // 1<<24 FXSAVE, FXRESTORE instructions
    Flags[static_cast<rf::i32>(rf::Features::SSE)] |= (registers[3] & 1 << 25) != 0;
    Flags[static_cast<rf::i32>(rf::Features::SSE2)] |=
        (registers[3] & 1 << 26) != 0;
    // 1<<27 CPU cache implements self-snoop
    Flags[static_cast<rf::i32>(rf::Features::HTT)] |= (registers[3] & 1 << 28) != 0;
    // 1<<29 Thermal monitor automatically limits temperature
    Flags[static_cast<rf::i32>(rf::Features::IA64)] |=
        (registers[3] & 1 << 10) != 0;
    // 1<<31 Pending break enable wakeup capability

    Flags[static_cast<rf::i32>(rf::Features::SSE3)] |= (registers[2] & 1) != 0;
    Flags[static_cast<rf::i32>(rf::Features::PCLMUL)] |= (registers[2] & 2) != 0;
    // 4 64-bit debug store
    // 8 MONITOR and MWAIT instructions
    // 16 CPL qualified debug store
    // 32 Virtual Machine eXtensions
    // 64 Safer Mode Extension
    // 128 Enhanced SpeedStep
    // 256 Thermal Monitor 2
    Flags[static_cast<rf::i32>(rf::Features::SSSE3)] |= (registers[2] & 512) != 0;
    // 1024 L1 Context ID
    // 2048 Silicon Debug interface
    Flags[static_cast<rf::i32>(rf::Features::FMA)] |= (registers[2] & 4096) != 0;
    Flags[static_cast<rf::i32>(rf::Features::CX16)] |= (registers[2] & 8192) != 0;
    // 1<<14 Can disable sending task priority messages
    // 1<<15 Perfmon & debug capability
    // 1<<16 Reserved
    // 1<<17 Process context identifier
    // 1<<18 Direct cache access for DMA writes
    Flags[static_cast<rf::i32>(rf::Features::SSE4_1)] |=
        (registers[2] & 1 << 19) != 0;
    Flags[static_cast<rf::i32>(rf::Features::SSE4_2)] |=
        (registers[2] & 1 << 20) != 0;
    // 1<<21 x2APIC
    Flags[static_cast<rf::i32>(rf::Features::MOVBE)] |=
        (registers[2] & 1 << 22) != 0;
    Flags[static_cast<rf::i32>(rf::Features::POPCNT)] |=
        (registers[2] & 1 << 23) != 0;
    // 1<<24 APIC implements one-shot operation using a TSC deadline value
    Flags[static_cast<rf::i32>(rf::Features::AES)] |= (registers[2] & 1 << 25) != 0;
    // 1<<26 XSAVE
    // 1<<27 XSAVE enabled by OS
    Flags[static_cast<rf::i32>(rf::Features::AVX)] |= (registers[2] & 1 << 28) != 0;
    Flags[static_cast<rf::i32>(rf::Features::F16C)] |=
        (registers[2] & 1 << 29) != 0;
    Flags[static_cast<rf::i32>(rf::Features::RDRND)] |=
        (registers[2] & 1 << 30) != 0;
    // 1<<31 Hypervisor present
  }
}

void HighestExtendedFunctions(bool *Flags) {
  rf::i32 registers[4];
  // 0x80000000 and above describe the AMD feature set.
  rf::cpuid(0x80000000, 0, registers);
  auto totalIDs = registers[0];
  if (totalIDs >= 0x80000001) {
    rf::cpuid(0x80000001, 0, registers);
    Flags[static_cast<rf::i32>(rf::Features::FPU)] |= (registers[3] & 1) != 0;
    Flags[static_cast<rf::i32>(rf::Features::VME)] |= (registers[3] & 2) != 0;
    // 4 Debugging extensions
    Flags[static_cast<rf::i32>(rf::Features::PSE)] |= (registers[3] & 8) != 0;
    Flags[static_cast<rf::i32>(rf::Features::TSC)] |= (registers[3] & 16) != 0;
    // 32 Model-specific registers
    Flags[static_cast<rf::i32>(rf::Features::PAE)] |= (registers[3] & 64) != 0;
    // 128 Machine Check Exception
    Flags[static_cast<rf::i32>(rf::Features::CX8)] |= (registers[3] & 256) != 0;
    // 512 Onboard Advanced Programmable Interrupt Controller
    // 1024 reserved
    // 2048 SYSCALL and SYSRET instructions
    // 4096 Memory Type Range Registers
    // 8192 Page Global Enable bit in CR4
    // 1<<14 Machine check architecture
    Flags[static_cast<rf::i32>(rf::Features::CMOV)] |=
        (registers[3] & 1 << 15) != 0;
    // 1<<16 Page Attribute Table
    // 1<<17 36-bit page size extension
    // 1<<18 reserved
    Flags[static_cast<rf::i32>(rf::Features::MP)] |= (registers[3] & 1 << 19) != 0;
    // 1<<20 NX bit
    // 1<<21 reserved
    Flags[static_cast<rf::i32>(rf::Features::MMXEXT)] |=
        (registers[3] & 1 << 22) != 0;
    Flags[static_cast<rf::i32>(rf::Features::MMX)] |= (registers[3] & 1 << 23) != 0;
    // 1<<24 FXSAVE, FXRESTORE instructions
    // 1<<25 FXSAVE, FXRESTORE optimizations
    Flags[static_cast<rf::i32>(rf::Features::PDPE1GB)] |=
        (registers[3] & 1 << 26) != 0;
    Flags[static_cast<rf::i32>(rf::Features::RDTSCP)] |=
        (registers[3] & 1 << 27) != 0;
    // 1<<28 reserved
    // 1<<29 long mode
    // 1<<30 3DNowExt
    // 1<<31 3DNow

    // 1 LAHF/SAHF in long mode
    // 2 Hyperthreading not valid
    // 4 Secure Virtual Machine
    // 8 Extended APIC space
    // 16 CR8 in 32-bit mode
    Flags[static_cast<rf::i32>(rf::Features::ABM)] |= (registers[2] & 32) != 0;
    Flags[static_cast<rf::i32>(rf::Features::SSE4A)] |= (registers[2] & 64) != 0;
    Flags[static_cast<rf::i32>(rf::Features::MisalignSSE)] |=
        (registers[2] & 128) != 0;
    Flags[static_cast<rf::i32>(rf::Features::Prefetch3DNow)] |=
        (registers[2] & 256) != 0;
    // 512 OS Visible Workaround
    Flags[static_cast<rf::i32>(rf::Features::IBS)] |= (registers[2] & 1024) != 0;
    Flags[static_cast<rf::i32>(rf::Features::XOP)] |= (registers[2] & 2048) != 0;
    // 4096 SKINIT/STGI instructions
    // 8192 Watchdog timer
    // 1<<14 reserved
    // 1<<15 Light Weight Profiling
    Flags[static_cast<rf::i32>(rf::Features::FMA4)] |=
        (registers[2] & 1 << 16) != 0;
    // 1<<17 Translation Cache Extension
    // 1<<18 reserved
    // 1<<19 NodeID MSR
    // 1<<20 reserved
    Flags[static_cast<rf::i32>(rf::Features::TBM)] |= (registers[2] & 1 << 21) != 0;
    // 1<<22 Topology Extensions
    Flags[static_cast<rf::i32>(rf::Features::PERFCTR_CORE)] |=
        (registers[2] & 1 << 23) != 0;
    Flags[static_cast<rf::i32>(rf::Features::PERFCTR_NB)] |=
        (registers[2] & 1 << 24) != 0;
    // 1<<25 reserved
    // 1<<26 Data breakpoint extensions
    Flags[static_cast<rf::i32>(rf::Features::PERFTSC)] |=
        (registers[2] & 1 << 27) != 0;
    Flags[static_cast<rf::i32>(rf::Features::PCX_L2I)] |=
        (registers[2] & 1 << 28) != 0;
    // 1<<29 reserved
    // 1<<30 reserved
    // 1<<31 reserved
  }
}