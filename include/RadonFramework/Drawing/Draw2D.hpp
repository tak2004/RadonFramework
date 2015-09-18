#ifndef RF_DRAWING_DRAW2D_HPP
#define RF_DRAWING_DRAW2D_HPP

namespace RadonFramework { namespace Math { namespace Geometry { 
template<typename T>
class Point2D;
} } }

namespace RadonFramework { namespace Drawing {

class MeshGenerator2D;
class Path2D;
class Text2D;
class NativeShape;
class FontDescription;

class Draw2D
{
public:
    Draw2D();
    ~Draw2D();

    RF_Mem::AutoPointer<Path2D> BeginPath()const;
    RF_Mem::AutoPointer<NativeShape> EndPath(Path2D& Path)const;

    RF_Mem::AutoPointer<Text2D> BeginText(const FontDescription& WhichFont, 
                                          const RF_Type::String& Text)const;
    RF_Mem::AutoPointer<NativeShape> EndText(Text2D& Text)const;

    void DrawPath(const NativeShape& Instance, const Math::Geometry::Point2D<RF_Type::Float32>& Position,
                  RF_Type::Float32 Angle=0.0f);
    void DrawText(const NativeShape& Instance, const Math::Geometry::Point2D<RF_Type::Float32>& Position,
                  RF_Type::Float32 Angle = 0.0f);

    void SetMeshGenerator(const MeshGenerator2D& Instance);
    const MeshGenerator2D* GetMeshGenerator()const;
protected:
    const MeshGenerator2D* m_MeshGenerator;
    RF_Type::UInt32 m_UIShader;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_DRAW2D_HPP