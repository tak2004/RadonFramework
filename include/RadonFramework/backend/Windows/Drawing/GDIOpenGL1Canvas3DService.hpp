#ifndef RF_GDIOPENGL1CANVAS3DSERVICE_HPP
#define RF_GDIOPENGL1CANVAS3DSERVICE_HPP

#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework { namespace Drawing {

class GDIOpenGL1Canvas3DService:public Canvas3DService
{
    public:
    GDIOpenGL1Canvas3DService(const RadonFramework::Core::Types::String &Name);
    ~GDIOpenGL1Canvas3DService();
    ICanvas3D* CreateCanvas3D();
};

} }

#endif
