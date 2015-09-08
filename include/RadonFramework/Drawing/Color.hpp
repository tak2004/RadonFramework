#ifndef RF_DRAWING_COLOR_HPP
#define RF_DRAWING_COLOR_HPP

namespace RadonFramework { namespace Drawing {

struct Color4f
{
    Color4f(RF_Type::Float32 Red, RF_Type::Float32 Green,
            RF_Type::Float32 Blue, RF_Type::Float32 Alpha);
    RF_Type::Float32 BGRA[4];
    RF_Type::Float32& operator [](RF_Type::Size Index);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_COLOR_HPP