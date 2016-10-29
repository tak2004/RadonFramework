#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Core/Pattern/Delegate.hpp"
#include "RadonFramework/Math/Geometry/Sphere32.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

class Sphere32Test:public RF_Test::TestSuite
{
public:
    Sphere32Test()
    :TestSuite("RadonFramework::Math::Geometry::Sphere32Test"_rfs)
    {
        AddTest(MakeDelegate(this,&Sphere32Test::Constructor),
            "Sphere32Test::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this, &Sphere32Test::AssignOperator),
                "Sphere32Test::AssignOperator"_rfs, "AssignOperator"_rfs);
        AddTest(MakeDelegate(this, &Sphere32Test::EqualOperator),
                "Sphere32Test::EqualOperator"_rfs, "EqualOperator"_rfs);
        AddTest(MakeDelegate(this, &Sphere32Test::GetPosition),
                "Sphere32Test::GetPosition"_rfs, "GetPosition"_rfs);
        AddTest(MakeDelegate(this, &Sphere32Test::GetRadius),
                "Sphere32Test::GetRadius"_rfs, "GetRadius"_rfs);
    }

    RF_Type::Bool Constructor()
    {
        Vec3f position;
        Sphere32 defaultSphere;
        Sphere32 specificSphere(position,1);
        return specificSphere == defaultSphere;
    }

    RF_Type::Bool AssignOperator()
    {
        Vec3f position;
        Sphere32 defaultSphere;
        Sphere32 specificSphere(position, 2);
        defaultSphere = specificSphere;
        return specificSphere == defaultSphere;
    }

    RF_Type::Bool EqualOperator()
    {
        Vec3f position;
        Sphere32 defaultSphere;
        Sphere32 specificSphere(position, 2);
        return defaultSphere == defaultSphere && !(defaultSphere == specificSphere);
    }

    RF_Type::Bool GetPosition()
    {
        Vec3f position(1,2,3);
        Sphere32 specificSphere(position, 1);
        return specificSphere.GetPosition() == position;
    }

    RF_Type::Bool GetRadius()
    {
        Vec3f position;
        Sphere32 specificSphere(position, 2);
        return specificSphere.GetRadius() == 2;
    }
};

Sphere32Test sphere32TestInstance;

} } }
