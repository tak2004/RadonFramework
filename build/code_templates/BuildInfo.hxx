/*
 *
 * THIS FILE IS GENERATED FROM build/code_templates/BuildInfo.hxx !!!
 *
 */
#ifndef RF_BUILDINFO_HPP
#define RF_BUILDINFO_HPP

namespace RadonFramework::BuildInfo
{
enum class HostOS
{
  Unknown,
  Windows,
  Linux,
  MacOS,
  UNIX
};

enum class Compiler
{
  Unknown,
  VisualCpp,
  Clang,
  MinGW,
  GCC
};

enum class DebugMode
{
  True,
  False
};

enum class Endian
{
  Little,
  Big
};

extern HostOS CompiledInOS;
extern Compiler CompiledWith;
extern DebugMode CompiledForDebugMode;
constexpr HostOS HostingOS = HostOS::@HostOS@;
constexpr Compiler CompilingWith = Compiler::@CompilingWith@;
constexpr Endian CompilerEndian = Endian::@CompilerEndian@;
constexpr DebugMode CompileForDebugging =
#if defined(NDEBUG)
    DebugMode::False;
#else
    DebugMode::True;
#endif

}  // namespace RadonFramework::BuildInfo

#endif