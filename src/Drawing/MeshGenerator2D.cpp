#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/MeshGenerator2D.hpp"
#include "RadonFramework/Drawing/NativeShape.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"

namespace RadonFramework { namespace Drawing {

RF_Mem::AutoPointer<NativeShape> MeshGenerator2D::Generate(const Path2D& Path) const
{
    RF_Mem::AutoPointer<NativeShape> result;

    if(Path.Data().Count())
    {
        RF_Type::UInt8* cursor = Path.Data().Get();
        RF_Type::UInt8* lastByte = Path.Data().Get() + Path.Data().Count() - 1;

        do
        {
            switch(*cursor)
            {
            case Path2D::Command::LineTo:
            case Path2D::Command::MoveTo:
                ++cursor;

                cursor += sizeof(RF_Geo::Point2Df);
                break;
            default:
                return result;
            }
        } while(cursor != lastByte);
    }
    return result;
}

}
}