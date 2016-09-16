#ifndef RF_ICANVAS3D_HPP
#define RF_ICANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework {
    
namespace System { namespace Threading {

class Mutex;

} }
    
namespace Forms{
    
class AbstractWindow;

}

namespace Drawing {

class GraphicDriverInformation;

/// This is a abstract class which should be used as interface for the backend implementation.
class AbstractCanvas
{
public:
    virtual void Generate()=0;
    virtual void SetWindowInfos(const Forms::AbstractWindow& Window)=0;
    virtual void Clear()=0;
    virtual void SwapBuffer()=0;
    virtual void UpdateRectangle(Math::Geometry::Rectangle<RF_Type::Int32> &Rec)=0;
    /** All upcoming rendering commands will piped to this canvas.
    * This is necessary if you use two or more canvas in one process.
    **/
    virtual void MakeCurrent()=0;

    virtual const GraphicDriverInformation& GetGraphicDriverInformation()=0;
    /** Synchronize specifies VSync On or Off and ShouldContinue hint to 
    * continue or wait till the buffer was swapped.
    **/
    virtual void SetVSync(const RF_Type::Bool Synchronize = true, 
        const RF_Type::Bool ShouldContinue = true)=0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif
