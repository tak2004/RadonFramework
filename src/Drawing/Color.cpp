#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Color.hpp"

namespace RadonFramework { namespace Drawing {

Color4f::Color4f(RF_Type::Float32 Red, RF_Type::Float32 Green,
                 RF_Type::Float32 Blue, RF_Type::Float32 Alpha)
{
    BGRA[0] = Red;
    BGRA[1] = Green;
    BGRA[2] = Blue;
    BGRA[3] = Alpha;
}

RF_Type::Float32& Color4f::operator[](RF_Type::Size Index)
{
    Assert(Index >= 4, "Index out of Bound!");
    return BGRA[Index];
}

} }