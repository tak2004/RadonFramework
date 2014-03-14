#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/ScopeLogMessage.hpp"
#include "RadonFramework/IO/Log.hpp"

using RadonFramework::Diagnostics::Debugging::ScopeLogMessage;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;


ScopeLogMessage::ScopeLogMessage(const String& Functionname)
:m_Functionname(Functionname)
{
    LogDebug("Enter '%s'",m_Functionname.c_str());
}

ScopeLogMessage::~ScopeLogMessage()
{
    LogDebug("Leave '%s'",m_Functionname.c_str());
}
