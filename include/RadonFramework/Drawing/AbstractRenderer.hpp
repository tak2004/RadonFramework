#ifndef RF_DRAWING_ABSTRACTRENDERER_HPP
#define RF_DRAWING_ABSTRACTRENDERER_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Drawing {

class Path2D;

class AbstractRenderer
{
public:
    virtual void StartFrame()=0;
    virtual void EndFrame()=0;
    virtual RF_Type::UInt32 Process(RF_Type::UInt32 EntityId, const Path2D& Path)=0;
    virtual void Draw()=0;
    virtual void ResizedViewport()=0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_ABSTRACTRENDERER_HPP
