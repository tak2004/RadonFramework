#include "RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp"
#include "RadonFramework/Core/Pattern/Delegate.hpp"
#include "RadonFramework/Math/Geometry/PackRectangle.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

class PackRectangleTest:public RF_UnitTest::TestSuite
{
public:
    PackRectangleTest()
    :TestSuite("RadonFramework::Math::Geometry::PackRectangleTest"_rfs)
    {
        AddTest(MakeDelegate(this,&PackRectangleTest::Constructor),
            "PackRectangleTest::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this, &PackRectangleTest::SetDimension),
            "PackRectangleTest::SetDimension"_rfs, "SetDimension"_rfs);
        AddTest(MakeDelegate(this, &PackRectangleTest::GetDimension),
            "PackRectangleTest::GetDimension"_rfs, "GetDimension"_rfs);
        AddTest(MakeDelegate(this, &PackRectangleTest::AddRectangle),
            "PackRectangleTest::AddRectangle"_rfs, "AddRectangle"_rfs);
        AddTest(MakeDelegate(this, &PackRectangleTest::Pack),
            "PackRectangleTest::Pack"_rfs, "Pack"_rfs);
        AddTest(MakeDelegate(this, &PackRectangleTest::Clear),
            "PackRectangleTest::Clear"_rfs, "Clear"_rfs);

    }

    RF_Type::Bool Constructor()
    {
        Size2D<> size512(512, 512);
        PackRectangle edge(512);
        PackRectangle rect(512, 1024);
        PackRectangle size(Size2D<>(512, 1024));
        return edge.GetDimension() == size.GetDimension() && 
            edge.GetDimension() == size512;
    }

    RF_Type::Bool SetDimension()
    {
        Size2D<> size512(512, 512);
        PackRectangle edge(1);
        edge.SetDimension(512);
        PackRectangle rect(1);
        rect.SetDimension(512, 512);
        PackRectangle size(1);
        size.SetDimension(size512);
        return edge.GetDimension() == size512 && 
            size.GetDimension() == size512 &&
            rect.GetDimension() == size512;
    }

    RF_Type::Bool GetDimension()
    {
        Size2D<> size512(512, 512);
        PackRectangle edge(512);
        return edge.GetDimension() == size512;
    }

    RF_Type::Bool AddRectangle()
    {
        Size2D<> size512(512, 512);
        PackRectangle edge(512);
        auto before = edge.NeedProcessing();
        edge.AddRectangle(size512, nullptr);
        auto after = edge.NeedProcessing();
        return before != after;
    }

    RF_Type::Bool Pack()
    {
        Size2D<> size32(32, 32);
        Size2D<> size64(64, 32);
        Size2D<> size128(128, 32);
        PackRectangle edge(128);
        edge.AddRectangle(size32, &size32);
        edge.AddRectangle(size64, &size64);
        edge.AddRectangle(size128, &size128);
        return edge.Pack();
    }

    RF_Type::Bool Clear()
    {
        Size2D<> size512(512, 512);
        PackRectangle edge(512);
        edge.AddRectangle(size512, nullptr);
        auto before = edge.NeedProcessing();
        edge.Clear();
        auto after = edge.NeedProcessing();
        return before != after;
    }
};

PackRectangleTest packRectangleTestInstance;

} } }
