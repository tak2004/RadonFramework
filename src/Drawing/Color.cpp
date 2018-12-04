#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Color.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"

namespace RadonFramework::Drawing {

Color4f::Color4f(RF_Type::Float32 Red, RF_Type::Float32 Green,
                 RF_Type::Float32 Blue, RF_Type::Float32 Alpha)
{
    BGRA[0] = Red;
    BGRA[1] = Green;
    BGRA[2] = Blue;
    BGRA[3] = Alpha;
}

Color4f::Color4f()
{
    BGRA[0] = 1.0f;
    BGRA[1] = 1.0f;
    BGRA[2] = 1.0f;
    BGRA[3] = 1.0f;
}

Color4f::Color4f(const Color4f& CopyFrom)
{
    *this = CopyFrom;
}

Color4f& Color4f::operator=(const Color4f& AssignThis)
{
    RF_SysMem::Copy(BGRA, AssignThis.BGRA, sizeof(BGRA));
    return *this;
}

const Color4f& Color4f::Black()
{
    static Color4f black = {0,0,0,1};
    return black;
}

const Color4f& Color4f::White()
{
    static Color4f white = {1,1,1,1};
    return white;
}

const Color4f& Color4f::Gray()
{
    static Color4f gray = {0.5,0.5,0.5,1};
    return gray;
}

RF_Type::Float32& Color4f::operator[](RF_Type::Size Index)
{
    Assert(Index >= 4, "Index out of Bound!");
    return BGRA[Index];
}

}