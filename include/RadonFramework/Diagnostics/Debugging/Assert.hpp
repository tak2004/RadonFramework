#ifndef RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Diagnostics { namespace Debugging {

#ifndef NDEBUG

#ifdef RF_DEBUG
struct AssertHandler
{
    typedef void (*Callback)(const char* Test, const char* Message, 
                                const char* Filename, int Line);
    static Callback Override;
    static void Process(const char* Test, const char* Message, 
                        const char* Filename, int Line);
};

#define ASSERT_IMPL(test,msg)\
if(!(test))\
{\
    if (RadonFramework::Diagnostics::Debugging::AssertHandler::Override)\
        RadonFramework::Diagnostics::Debugging::AssertHandler::Override(#test,#msg,__FILE__,__LINE__);\
    else\
        RadonFramework::Diagnostics::Debugging::AssertHandler::Process(#test,#msg,__FILE__,__LINE__);\
}
#else
    #define ASSERT_IMPL(test,msg) { }
#endif

#else
    #define ASSERT_IMPL(test,msg) { }
#endif

#define Assert(test,msg)\
{\
    ASSERT_IMPL(test,msg)\
}

} } }

#endif // RF_DIAGNOSTICS_DEBUGGING_ASSERT_HPP