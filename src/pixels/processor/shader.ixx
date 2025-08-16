module;
#include <asmjit/x86.h>
export module rf.pixels.processor:shader;
import rf.pixels.data;
import rf.core.types;

export namespace rf {
struct PixelBufferLocation {
  u64 u;
  u64 v;
};

struct ShaderState {
  PixelBufferLocation pixelLocation;
  Buffer in;
  Buffer out;
};

struct Shader {
  asmjit::JitRuntime rt;
  ShaderState state;
  void (*fun)(ShaderState *State);
  void operator()() { fun(&state); }
};

void emit(Shader &Self,
          void (*CodeEmitter)(asmjit::x86::Compiler& Self, ShaderState &State)) {
  asmjit::CodeHolder code;
  code.init(Self.rt.environment(), Self.rt.cpuFeatures());
  asmjit::x86::Compiler cc(&code);
  auto fun = cc.addFunc(asmjit::FuncSignature::build<void, ShaderState *>());
  auto state = cc.newUIntPtr("state");
  fun->setArg(0, state);
  CodeEmitter(cc, Self.state);
  cc.endFunc();
  cc.finalize();
  auto err = Self.rt.add(&Self.fun, &code);
}

void release(Shader &Self) { Self.rt.release(Self.fun); }

} // namespace rf