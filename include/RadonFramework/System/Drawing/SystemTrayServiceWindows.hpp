#ifndef RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP
#define RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Drawing/SystemTrayService.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework { namespace System { namespace Drawing {

class SystemTrayServiceWindows:public SystemTrayService
{
public:
    SystemTrayServiceWindows(const RF_Type::String &Name);
    virtual ~SystemTrayServiceWindows();
    
    virtual RF_Type::Bool IsSupported();

    virtual Handle AddIcon(const RF_Draw::TrayIcon& Settings);
    virtual void Remove(Handle IconInstance);
    //virtual void Modify(Handle IconInstance, ) = 0;
protected:
    RF_Idiom::PImpl<SystemTrayServiceWindows> m_PImpl;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif // RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP