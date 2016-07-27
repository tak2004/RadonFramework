#ifndef RF_WDMOPENGLCANVAS3D_HPP
#define RF_WDMOPENGLCANVAS3D_HPP

#include <RadonFramework/backend/Windows/Drawing/WindowsOpenGLCanvas3D.hpp>

namespace RadonFramework { namespace Drawing {

class WDMOpenGLCanvas3D : public WindowsOpenGLCanvas3D
{
public:
    void Generate();
protected:
    virtual void GetExtensions(RF_Collect::Array<RF_Type::String>& Extensions) override;
    RF_Type::UInt32 m_MajorVersion;
};

} }

#endif // RF_WDMOPENGLCANVAS3D_HPP
