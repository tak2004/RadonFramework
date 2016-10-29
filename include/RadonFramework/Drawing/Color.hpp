#ifndef RF_DRAWING_COLOR_HPP
#define RF_DRAWING_COLOR_HPP

namespace RadonFramework { namespace Drawing {

struct Color4f
{
    static const Color4f& White();
    static const Color4f& Gray();

    Color4f();
    Color4f(const Color4f& CopyFrom);
    Color4f(RF_Type::Float32 Red, RF_Type::Float32 Green,
            RF_Type::Float32 Blue, RF_Type::Float32 Alpha);
    RF_Type::Float32 BGRA[4];
    RF_Type::Float32& operator [](RF_Type::Size Index);
    Color4f& operator = (const Color4f& AssignThis);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_COLOR_HPP