#ifndef RF_DRAWING_OPENGLCAPABILITIESTYPE_HPP
#define RF_DRAWING_OPENGLCAPABILITIESTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Drawing::OpenGLCapabilitiesType {

enum Type
{
    NOTSET,
    GLFLOAT,
    GLDOUBLE,
    GLINT,
    GLINT64,
    GLBOOLEAN,
    GLSTRING,
    MAX
};

}

#endif // RF_DRAWING_OPENGLCAPABILITIESTYPE_HPP