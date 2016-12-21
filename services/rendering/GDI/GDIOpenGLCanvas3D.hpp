#ifndef RF_GDIOPENGLCANVAS3D_HPP
#define RF_GDIOPENGLCANVAS3D_HPP

#include <RadonFramework/backend/Windows/Drawing/WindowsOpenGLCanvas3D.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class AbstractWindow;
} }

namespace RadonFramework { namespace Drawing {

/// Provide the newest OpenGL context with the GDI interface.
class GDIOpenGLCanvas3D : public WindowsOpenGLCanvas3D
{
public:
    void Generate();
};

} }

#endif // RF_GDIOPENGLCANVAS3D_HPP
