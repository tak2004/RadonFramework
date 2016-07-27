#ifndef RF_GDIOPENGL3CANVAS3D_HPP
#define RF_GDIOPENGL3CANVAS3D_HPP

#include <RadonFramework/backend/Windows/Drawing/WindowsOpenGLCanvas3D.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Drawing/MeshGenerator2D.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class AbstractWindow;
} }

namespace RadonFramework { namespace Drawing {

class GDIOpenGL3Canvas3D:public WindowsOpenGLCanvas3D
{
public:
    void Generate();
};

} }

#endif // RF_GDIOPENGL3CANVAS3D_HPP
