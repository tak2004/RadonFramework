#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/CompilerConfig.hpp"
#include "RadonFramework/Core/Common/Version.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Common;

const Endian RadonFramework::System::CompilerConfig::Endianness = Endian::@RADONFRAMEWORK_ENDIANNESS@;
const MemoryArchitecture::Type RadonFramework::System::CompilerConfig::CompiledForArchitecture = MemoryArchitecture::@RADONFRAMEWORK_COMPILEDFORARCHITECTURE@;
const Version FrameworkVersion = Version(@RADONFRAMEWORK_MAJORNUMBER@, @RADONFRAMEWORK_MINORNUMBER@, @RADONFRAMEWORK_BUILDNUMBER@, @RADONFRAMEWORK_REVISIONNUMBER@);