#ifndef RF_DRAWING_MESHGENERATOR2D_HPP
#define RF_DRAWING_MESHGENERATOR2D_HPP

namespace RadonFramework { namespace Drawing {

class NativeShape;
class Path2D;

class MeshGenerator2D
{
public:
    RF_Mem::AutoPointer<NativeShape> Generate(const Path2D& Path)const;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_MESHGENERATOR2D_HPP