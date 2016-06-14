#ifndef RF_CANVAS3DSERVICE_HPP
#define RF_CANVAS3DSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Drawing/AbstractCanvas.hpp>

namespace RadonFramework { namespace Drawing {

class Canvas3DService:public Core::Pattern::Service
{
public:
    Canvas3DService(const RF_Type::String &Name);
    ~Canvas3DService();
    virtual AbstractCanvas* CreateCanvas3D() = 0;
};
  
} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif
