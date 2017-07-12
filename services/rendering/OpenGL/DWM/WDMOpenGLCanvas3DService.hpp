#ifndef RF_WDMOPENGLCANVAS3DSERVICE_HPP
#define RF_WDMOPENGLCANVAS3DSERVICE_HPP

#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework::Drawing {

class WDMOpenGLCanvas3DService : public Canvas3DService
{
public:
    WDMOpenGLCanvas3DService(const RF_Type::String &Name);
    ~WDMOpenGLCanvas3DService();
    AbstractCanvas* CreateCanvas3D();
    static void Register();
};

}

#endif // RF_WDMOPENGLCANVAS3DSERVICE_HPP
