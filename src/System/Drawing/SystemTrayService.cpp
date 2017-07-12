#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/SystemTrayService.hpp"

namespace RadonFramework::System::Drawing {

SystemTrayService::SystemTrayService(const RF_Type::String &Name)
:Service(Name)
,OnAction(0)
{
}

SystemTrayService::~SystemTrayService()
{
}

}