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

Version GetOSVersion()
{
    struct utsname name;
    if (uname(&name)>=0)
    {
        UInt32 maj,min,build,rev,len=strlen(name.release);
        int number=-1,state=1;            
        for (UInt32 i=0;i<len;++i)
        {
            if(isdigit(name.release[i]))
            {
                if (number<0)
                    number=name.release[i]-'0';
                else
                    number=(number*10)+(name.release[i]-'0');                        
            }
            else
                if (number>=0)
                {
                    switch(state)
                    {
                        case 1: maj=number;
                                break;
                        case 2: min=number;
                                break;
                        case 3: build=number;
                                break;
                        case 4: rev=number;
                                break;
                    }
                    number=-1;
                    state++;
                }
            if(state==5)
                break;
        }
            
        if (number>=0)
        {
            switch(state)
            {
                case 1: maj=number;
                        break;
                case 2: min=number;
                        break;
                case 3: build=number;
                        break;
                case 4: rev=number;
                        break;
            }
        }
        // since kernel 3.0.0 there are only 3 numbers
        // 1)major 2)minor 3)bugfix
        // before this version there were following
        // 1)kernel completly changed number 2)major 3)minor 4)bugfix
        if (maj>2)
            rev=0;
        return Version(maj,min,build,rev);
    }
    return Version();
}

PlatformID::Type Platform()
{
    return PlatformID::Unix;
}

Bool Is32BitEmulation()
{
    FILE *fp=NULL;
    char cb64[3];

    fp = popen ("getconf LONG_BIT", "r");
    if (fp!=NULL)
    {
        if (fgets(cb64, 3, fp) && !strncmp(cb64, "64", 3))
            return CompilerConfig::CompiledForArchitecture==MemoryArchitecture::_32Bit;
        pclose(fp);
    }
    return false;
}

MemoryArchitecture::Type MemoryArchitectureOfOS()
{
    static const MemoryArchitecture::Type arch = false==Is32BitEmulation()
        && CompilerConfig::CompiledForArchitecture==MemoryArchitecture::_32Bit
        ? MemoryArchitecture::_32Bit : MemoryArchitecture::_64Bit;
    return arch;
}

const OperatingSystem& OSVersion()
{
    static OperatingSystem os=OperatingSystem(Platform(),GetOSVersion());
    return os;
}

void GetVariable(const RFTYPE::String& Name, RFTYPE::String& Result)
{
    Result=RFTYPE::String(getenv(Name.c_str()),DataManagment::TransfereOwnership);
}

OperatingSystemFamily::Type OSFamily()
{
    return OperatingSystemFamily::Windows;
}

void RadonFramework::System::Environment::Dispatch()
{
    MemoryArchitectureOfOS=::MemoryArchitectureOfOS;
    Is32BitEmulation=::Is32BitEmulation;
    OSVersion=::OSVersion;
    GetVariable=::GetVariable;
    Platform=::Platform;
    //OSFamily=::OSFamily;
}