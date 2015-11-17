#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/CompilerConfig.hpp"
#include "RadonFramework/Core/Common/DataManagment.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::System;

#include <sys/utsname.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace RadonFramework { namespace System { namespace Environment {

namespace Unix {

PlatformID::Type Platform()
{
    return PlatformID::Unix;
}

Bool Is32BitEmulation()
{
    FILE *fp = NULL;
    char cb64[3];

    fp = popen("getconf LONG_BIT", "r");
    if(fp != NULL)
    {
        if(fgets(cb64, 3, fp) && !strncmp(cb64, "64", 3))
            return CompilerConfig::CompiledForArchitecture == MemoryArchitecture::_32Bit;
        pclose(fp);
    }
    return false;
}

MemoryArchitecture::Type MemoryArchitectureOfOS()
{
    static const MemoryArchitecture::Type arch = false == Is32BitEmulation()
        && CompilerConfig::CompiledForArchitecture == MemoryArchitecture::_32Bit
        ? MemoryArchitecture::_32Bit : MemoryArchitecture::_64Bit;
    return arch;
}

const OperatingSystem& OSVersion()
{
    static OperatingSystem os = OperatingSystem(Platform(), Version());
    return os;
}

void GetVariable(const RF_Type::String& Name, RF_Type::String& Result)
{
    Result = RF_Type::String::UnsafeStringCreation(getenv(Name.c_str()), DataManagment::TransfereOwnership);
}

OperatingSystemFamily::Type OSFamily()
{
    return OperatingSystemFamily::Unkown;
}

}

void Dispatch()
{
    MemoryArchitectureOfOS = Unix::MemoryArchitectureOfOS;
    Is32BitEmulation = Unix::Is32BitEmulation;
    GetVariable = Unix::GetVariable;
    Platform = Unix::Platform;
    OSFamily = Unix::OSFamily;
    OSVersion = Unix::OSVersion;
#ifdef RF_LINUX
    extern void Dispatch_Linux();
    Dispatch_Linux();
#else
#ifdef RF_OSX
    extern void Dispatch_OSX();
    Dispatch_OSX();
#endif
#endif

}

} } }