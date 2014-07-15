#ifndef RF_DIAGNOSTICS_DEBUGGING_SCOPELOGMESSAGE_HPP
#define RF_DIAGNOSTICS_DEBUGGING_SCOPELOGMESSAGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            class ScopeLogMessage
            {
                public:
                    ScopeLogMessage(const RF_Type::String& Functionname);
                    ~ScopeLogMessage();
                protected:
                    RF_Type::String m_Functionname;
            };            
        }
    }    
}

#define LogScope(FUNCTIONNAME,SCOPENAME) RadonFramework::Diagnostics::Debugging::ScopeLogMessage SCOPENAME(FUNCTIONNAME)

#endif // RF_DIAGNOSTICS_DEBUGGING_SCOPELOGMESSAGE_HPP
