#ifndef RF_WDMOPENGLCANVAS3DSERVICE_HPP
#define RF_WDMOPENGLCANVAS3DSERVICE_HPP

#ifdef RF_USE_WDM
#ifdef RF_USE_OPENGL

#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework { namespace Drawing {

class WDMOpenGLCanvas3DService : public Canvas3DService
{
public:
    WDMOpenGLCanvas3DService(const RF_Type::String &Name);
    ~WDMOpenGLCanvas3DService();
    ICanvas3D* CreateCanvas3D();
};

} }

#endif // RF_USE_OPENGL
#endif // RF_USE_WDM

#endif // RF_WDMOPENGLCANVAS3DSERVICE_HPP
