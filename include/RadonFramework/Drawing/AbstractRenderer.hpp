#ifndef RF_DRAWING_ABSTRACTRENDERER_HPP
#define RF_DRAWING_ABSTRACTRENDERER_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/CommandBucket.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework { namespace Drawing {

class Path2D;

class AbstractRenderer
{
public:
    virtual void Generate() = 0;
    virtual void StartFrame()=0;
    virtual void EndFrame()=0;
    virtual RF_Type::UInt32 Process(RF_Type::UInt32 EntityId, const Path2D& Path)=0;
    virtual void Draw()=0;
    virtual void ResizedViewport(const RF_Geo::Size2D<>& NewSize)=0;
protected:
    RF_Collect::Array<RF_Collect::CommandBucket<>> m_Buckets;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_ABSTRACTRENDERER_HPP
