#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Threading/Condition.hpp"
#include "RadonFramework/IO/Log.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

namespace RadonFramework::System::Threading::OSX {

void Rename(void* Data, const RF_Type::String& Name)
{
    RF_Type::String shortName(Name);
    if(shortName.Size() > 63)
        shortName = shortName.SubString(0, 63);
    pthread_setname_np(shortName.c_str());
}

}

namespace RadonFramework::System::Threading {

void Dispatch_OSX()
{
    Rename = OSX::Rename;
}

}