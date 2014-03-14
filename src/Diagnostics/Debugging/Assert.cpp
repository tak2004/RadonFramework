#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"
#include "RadonFramework/IO/Log.hpp"
#include <stdlib.h>

using namespace RadonFramework::Diagnostics::Debugging;
using namespace RadonFramework::IO;

#ifndef NDEBUG
    #ifdef RF_DEBUG
        AssertHandler::Callback AssertHandler::Override=0;

        void AssertHandler::Process( const char* Test, const char* Message, 
                                     const char* Filename, int Line )
        {
            LogFatalError("%s(%d): %s\n\t%s\n",Filename,Line,Test,Message);
            abort();
        }
    #endif
#endif