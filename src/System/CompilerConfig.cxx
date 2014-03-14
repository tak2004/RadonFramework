#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/CompilerConfig.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Common;

const Endian::Type CompilerConfig::Endianness=Endian::@RADONFRAMEWORK_ENDIANNESS@;
const MemoryArchitecture::Type CompilerConfig::CompiledForArchitecture=MemoryArchitecture::@RADONFRAMEWORK_COMPILEDFORARCHITECTURE@;
const Version CompilerConfig::FrameworkVersion=Version(@RADONFRAMEWORK_MAJORNUMBER@,@RADONFRAMEWORK_MINORNUMBER@,@RADONFRAMEWORK_BUILDNUMBER@,@RADONFRAMEWORK_REVISIONNUMBER@);