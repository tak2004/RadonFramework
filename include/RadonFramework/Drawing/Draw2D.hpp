#ifndef RF_DRAWING_DRAW2D_HPP
#define RF_DRAWING_DRAW2D_HPP

#include <RadonFramework/Drawing/Text2D.hpp>
#include <RadonFramework/Drawing/Path2D.hpp>
#include <RadonFramework/Drawing/FontService.hpp>

namespace RadonFramework { namespace Drawing {

class Draw2D
{
public:
    Draw2D();
    ~Draw2D();

    void Clear();

    Path2D& BeginPath();
    void EndPath(const Path2D& Path);

    Text2D& Text(const FontDescription& WhichFont, const RF_Type::String& Text);

    void DrawPath(const Path2D& Instance, const RF_Geo::Point2Df& Position, 
                  RF_Type::Float32 Angle=0.0f);
    void DrawText(const Text2D& Instance, const RF_Geo::Point2Df& Position, 
                  RF_Type::Float32 Angle = 0.0f);
protected:
    RF_Collect::Array<Path2D> m_PathList;
    RF_Collect::Array<Text2D> m_TextList;
    RF_Type::Size m_PathListUsed;
    RF_Type::Size m_TextListUsed;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_DRAW2D_HPP