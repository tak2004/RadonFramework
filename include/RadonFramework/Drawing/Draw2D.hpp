#ifndef RF_DRAWING_DRAW2D_HPP
#define RF_DRAWING_DRAW2D_HPP

namespace RadonFramework { namespace Drawing {

class Draw2D
{
public:
    Path2D& BeginPath();
    void EndPath(const Path2D& Path);

    Text2D Text(const Font& WhichFont, const RF_Type::String& Text);

    void DrawPath(const Path2D& Instance, const RF_Geo::Point2Df& Position);
    void DrawText(const Text2D& Instance, const RF_Geo::Point2Df& Position);
};

} }

#endif // RF_DRAWING_DRAW2D_HPP