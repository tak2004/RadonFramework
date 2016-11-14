#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Core/Pattern/Delegate.hpp"
#include "RadonFramework/Math/Geometry/Ray32.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

class Ray32Test:public RF_UnitTest::TestSuite
{
public:
    Ray32Test()
    :TestSuite("RadonFramework::Math::Geometry::Ray32Test"_rfs)
    {
        AddTest(MakeDelegate(this,&Ray32Test::Constructor),
            "Ray32Test::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this,&Ray32Test::CopyConstructor),
            "Ray32Test::CopyConstructor"_rfs, "CopyConstructor"_rfs);
        AddTest(MakeDelegate(this, &Ray32Test::Equal),
            "Ray32Test::Equal"_rfs, "Equal"_rfs);
        AddTest(MakeDelegate(this, &Ray32Test::GetPoint),
                "Ray32Test::GetPoint"_rfs, "GetPoint"_rfs);
        AddTest(MakeDelegate(this, &Ray32Test::GetOrigin),
                "Ray32Test::GetOrigin"_rfs, "GetOrigin"_rfs);
        AddTest(MakeDelegate(this, &Ray32Test::GetDirection),
                "Ray32Test::GetDirection"_rfs, "GetDirection"_rfs);
        AddTest(MakeDelegate(this, &Ray32Test::Assign),
                "Ray32Test::Assign"_rfs, "Assign"_rfs);
    }

    RF_Type::Bool Constructor()
    {
        Vec3f position;
        Norm3f direction;
        Ray32 defaultRay;
        Ray32 specificRay(position, direction);
        return defaultRay.Equals(specificRay);
    }

    RF_Type::Bool CopyConstructor()
    {
        Vec3f position;
        Norm3f direction;
        Ray32 specificRay(position, direction);
        Ray32 copyRay(specificRay);
        return copyRay.Equals(specificRay);
    }

    RF_Type::Bool Equal()
    {
        Vec3f position;
        Norm3f direction;
        Ray32 specificRay(position, direction);
        Ray32 defaultRay;
        return defaultRay.Equals(specificRay);
    }

    RF_Type::Bool GetPoint()
    {
        Vec3f position(0,0,5);
        Ray32 defaultRay;
        return defaultRay.GetPoint(5.0f) == position;
    }

    RF_Type::Bool GetOrigin()
    {
        Vec3f position;
        Ray32 defaultRay;
        return defaultRay.GetOrigin() == position;
    }

    RF_Type::Bool GetDirection()
    {
        Norm3f direction;
        Ray32 defaultRay;
        return defaultRay.GetDirection() == direction;
    }

    RF_Type::Bool Assign()
    {
        Vec3f position(0,0,5);
        Norm3f direction;
        Ray32 defaultRay;
        Ray32 specificRay(position, direction);
        defaultRay = specificRay;
        return defaultRay.Equals(specificRay);
    }
};

Ray32Test ray32TestInstance;

} } }
