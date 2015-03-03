#ifndef RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
#define RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/System/Drawing/SystemTrayService.hpp>

namespace RadonFramework { namespace System { namespace Drawing {

class NullSystemTrayService:public SystemTrayService
{
public:
    NullSystemTrayService(const RF_Type::String &Name):SystemTrayService(Name)
    {}

    virtual ~NullSystemTrayService()
    {}
    
    virtual Handle AddIcon(const RF_Draw::TrayIcon& Settings){return 0;}
    virtual void Remove(Handle IconInstance){}
    virtual RF_Type::Bool IsSupported() { return false; }
};

typedef RF_Pattern::Locator<SystemTrayService, NullSystemTrayService> SystemTrayServiceLocator;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif // RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
