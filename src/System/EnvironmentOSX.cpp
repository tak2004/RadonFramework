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

namespace RadonFramework::System::Environment::OSX {

PlatformID::Type Platform()
{
    return PlatformID::MacOSX;
}

OperatingSystemFamily::Type OSFamily()
{
    return OperatingSystemFamily::MacOS;
}

}

namespace RadonFramework::System::Environment {

void Dispatch_OSX()
{
    Platform=OSX::Platform;
    OSFamily=OSX::OSFamily;
}

}