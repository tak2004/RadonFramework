#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/SystemTrayService.hpp"

namespace RadonFramework { namespace System { namespace Drawing {

SystemTrayService::SystemTrayService(const RF_Type::String &Name)
:Service(Name)
,OnAction(0)
{
}

SystemTrayService::~SystemTrayService()
{
}

} } }