#ifndef RF_GDIOPENGLCANVAS3DSERVICE_HPP
#define RF_GDIOPENGLCANVAS3DSERVICE_HPP

#ifdef RF_USE_GDI
#ifdef RF_USE_OPENGL

#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework { namespace Drawing {

class GDIOpenGLCanvas3DService : public Canvas3DService
{
public:
    GDIOpenGLCanvas3DService(const RF_Type::String &Name);
    ~GDIOpenGLCanvas3DService();
    ICanvas3D* CreateCanvas3D();
};

} }

#endif
#endif

#endif
