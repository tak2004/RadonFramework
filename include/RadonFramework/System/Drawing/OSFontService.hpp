#ifndef RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP
#define RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/FontService.hpp>

namespace RadonFramework { namespace System { namespace Drawing {

class OSFontService:public RF_Draw::FontService
{
public:
    OSFontService(const RF_Type::String &Name);
    virtual ~OSFontService() override;
    virtual void Update() override;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif // RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP