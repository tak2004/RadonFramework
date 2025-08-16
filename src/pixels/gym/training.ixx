module;
#include <asmjit/x86.h>
export module rf.pixels.gym:training;
import rf.core.memory;
import rf.core.types;

export namespace rf {
struct TrainingsPlan {
  u16 limitCPUs = 0; // Zero means utilize all CPUs.
  bool needSignedValues = false;
  bool needFloatingPointPrecission = false;
};

struct RecommendedSettings {
  u16 threads = 0;
  bool useFibers = false;
  
};

template <IsAdvancedAllocator ALLOCATOR>
void exercise(TrainingsPlan &Plan, RecommendedSettings& Recommendation, ALLOCATOR &Allocator) {
  asmjit::JitRuntime rt;
  asmjit::CodeHolder code;
  code.init(rt.environment(), rt.cpuFeatures());
  asmjit::x86::Compiler cc(&code);
  cc.addFunc(asmjit::FuncSignature::build<void>());
  rt.cpuFeatures().x86().hasSSE4_1();
}
} // namespace rf