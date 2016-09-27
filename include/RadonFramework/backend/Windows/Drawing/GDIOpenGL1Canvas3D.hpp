#ifndef RF_GDIOPENGL1CANVAS3D_HPP
#define RF_GDIOPENGL1CANVAS3D_HPP

#include <RadonFramework/backend/Windows/Drawing/WindowsOpenGLCanvas3D.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class AbstractWindow;
} }

namespace RadonFramework { namespace Drawing {

class GDIOpenGL1Canvas3D:public WindowsOpenGLCanvas3D
{
public:
    void Generate();
};
  
} }

#endif // RF_GDIOPENGL1CANVAS3D_HPP
