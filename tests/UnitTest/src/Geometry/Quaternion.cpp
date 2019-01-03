#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Math/Float32.hpp>
#include <RadonFramework/Math/Float64.hpp>
#include <RadonFramework/Math/Geometry/QuatF32.hpp>
#include <RadonFramework/Math/Geometry/QuatF64.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Test::UnitTest;

class GeometryQuatF32Test:public TestSuite
{
public:
    GeometryQuatF32Test()
    :TestSuite("RadonFramework::Math::Geometry::QuatF32-Test"_rfs)
    {
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::DefaultConstructor),
                "GeometryQuatF32Test::DefaultConstructor"_rfs,
                "DefaultConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::CopyConstructor),
                "GeometryQuatF32Test::CopyConstructor"_rfs,
                "CopyConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::AssignOperator),
                "GeometryQuatF32Test::AssignOperator"_rfs,
                "AssignOperator"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::AxisAngleConstructor),
                "GeometryQuatF32Test::AxisAngleConstructor"_rfs,
                "AxisAngleConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::SeperateElementsConstructor),
                "GeometryQuatF32Test::SeperateElementsConstructor"_rfs,
                "SeperateElementsConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::DirectionConstructor),
                "GeometryQuatF32Test::DirectionConstructor"_rfs,
                "DirectionConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::RotationMatrixConstructor),
                "GeometryQuatF32Test::RotationMatrixConstructor"_rfs,
                "RotationMatrixConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::EulerConstructor),
                "GeometryQuatF32Test::EulerConstructor"_rfs,
                "EulerConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Addition),
                "GeometryQuatF32Test::Addition"_rfs,
                "Addition"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Subtraction),
                "GeometryQuatF32Test::Subtraction"_rfs,
                "Subtraction"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Multiplication),
                "GeometryQuatF32Test::Multiplication"_rfs,
                "Multiplication"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Division),
                "GeometryQuatF32Test::Division"_rfs,
                "Division"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::AdditionAssign),
                "GeometryQuatF32Test::AdditionAssign"_rfs,
                "AdditionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::SubtractionAssign),
                "GeometryQuatF32Test::SubtractionAssign"_rfs,
                "SubtractionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::MultiplicationAssign),
                "GeometryQuatF32Test::MultiplicationAssign"_rfs,
                "MultiplicationAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::DivisionAssign),
                "GeometryQuatF32Test::DivisionAssign"_rfs,
                "DivisionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::SetIdentity),
                "GeometryQuatF32Test::SetIdentity"_rfs,
                "SetIdentity"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Invert),
                "GeometryQuatF32Test::Invert"_rfs,
                "Invert"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Conjugate),
                "GeometryQuatF32Test::Conjugate"_rfs,
                "Conjugate"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Normalize),
                "GeometryQuatF32Test::Normalize"_rfs,
                "Normalize"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::DotProduct),
                "GeometryQuatF32Test::DotProduct"_rfs,
                "DotProduct"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::CrossProduct),
                "GeometryQuatF32Test::CrossProduct"_rfs,
                "CrossProduct"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Inverse),
                "GeometryQuatF32Test::Inverse"_rfs,
                "Inverse"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::MultiplyPosition),
                "GeometryQuatF32Test::MultiplyPosition"_rfs,
                "MultiplyPosition"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Equal),
                "GeometryQuatF32Test::Equal"_rfs,
                "Equal"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Unequal),
                "GeometryQuatF32Test::Unequal"_rfs,
                "Unequal"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::IsInfinity),
                "GeometryQuatF32Test::IsInfinity"_rfs,
                "IsInfinity"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::IsNaN),
                "GeometryQuatF32Test::IsNaN"_rfs,
                "IsNaN"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::LengthAsQuat),
                "GeometryQuatF32Test::LengthAsQuat"_rfs,
                "LengthAsQuat"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Length),
                "GeometryQuatF32Test::Length"_rfs,
                "Length"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::SquareLengthAsQuat),
                "GeometryQuatF32Test::SquareLengthAsQuat"_rfs,
                "SquareLengthAsQuat"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::SquareLength),
                "GeometryQuatF32Test::SquareLength"_rfs,
                "SquareLength"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::Slerp),
                "GeometryQuatF32Test::Slerp"_rfs,
                "Slerp"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::ToAxisAngle),
                "GeometryQuatF32Test::ToAxisAngle"_rfs,
                "ToAxisAngle"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::GetAxis),
                "GeometryQuatF32Test::GetAxis"_rfs,
                "GetAxis"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::GetAngle),
                "GeometryQuatF32Test::GetAngle"_rfs,
                "GetAngle"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::AsRotationMatrix),
                "GeometryQuatF32Test::AsRotationMatrix"_rfs,
                "AsRotationMatrix"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::AsMatrix),
                "GeometryQuatF32Test::AsMatrix"_rfs,
                "AsMatrix"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF32Test::ArrayOperator),
                "GeometryQuatF32Test::ArrayOperator"_rfs,
                "ArrayOperator"_rfs);
    }

    Bool DefaultConstructor()
    {
        QuatF32 q;
        return q[0] == (Float32)1 && q[1] == (Float32)0 &&
            q[2] == (Float32)0 && q[3] == (Float32)0;
    }

    Bool CopyConstructor()
    {
        QuatF32 q1;
        q1[2] = (Float32)2;
        QuatF32 q(q1);
        return q[0] == (Float32)1 && q[1] == (Float32)0 &&
            q[2] == (Float32)2 && q[3] == (Float32)0;
    }

    Bool AssignOperator()
    {
        QuatF32 q;
        QuatF32 q1;
        q1[2] = (Float32)2;
        q = q1;
        return q[0] == (Float32)1 && q[1] == (Float32)0 &&
            q[2] == (Float32)2 && q[3] == (Float32)0;
    }

    Bool AxisAngleConstructor()
    {
        QuatF32 q(180.0f, Vector<Float32, 3>(1, 0, 0));
        Vector<Float32, 4> v(0, 1, 0, 0);
        return Math::Float32::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool SeperateElementsConstructor()
    {
        QuatF32 q(45, 0, 1, 0);
        return q[0] == (Float32)45 && q[1] == (Float32)0 &&
            q[2] == (Float32)1 && q[3] == (Float32)0;
    }

    Bool DirectionConstructor()
    {
        QuatF32 q(Vector<Float32, 3>(0, 0, 1));
        Vector<Float32, 4> v(1, 0, 0, 0);
        return Math::Float32::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool RotationMatrixConstructor()
    {
        Float32 a[] = {-1,0,0, 0,-1,0, 0,0,1};
        Matrix<Float32, 3, 3> mat;
        RF_SysMem::Copy(mat.Value, a, sizeof(Float32) * 9);
        QuatF32 q(mat);
        Vector<Float32, 4> v(0, 0, 0, 1);
        return Math::Float32::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool EulerConstructor()
    {
        QuatF32 q(0, 180, 0);
        Vector<Float32, 4> v(0, 0, 0, 1);
        return Math::Float32::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool Addition()
    {
        QuatF32 q(45, 45, 45, 45);
        QuatF32 q1(45, 46, 47, 48);
        q = q + q1;
        return q[0] == (Float32)90 && q[1] == (Float32)91 &&
            q[2] == (Float32)92 && q[3] == (Float32)93;
    }

    Bool Subtraction()
    {
        QuatF32 q(45, 45, 45, 45);
        QuatF32 q1(45, 44, 43, 42);
        q = q - q1;
        return q[0] == (Float32)0 && q[1] == (Float32)1 &&
            q[2] == (Float32)2 && q[3] == (Float32)3;
    }

    Bool Multiplication()
    {
        QuatF32 q(1, 2, 3, 4);
        QuatF32 q1(5, 6, 7, 8);
        q = q*q1;
        return q[0] == (Float32)-60 && q[1] == (Float32)12 &&
            q[2] == (Float32)30 && q[3] == (Float32)24;
    }

    Bool Division()
    {
        QuatF32 q(0, 0, 0, 1);
        QuatF32 q1;
        q = q / q;
        return Math::Float32::IsAlmostEqual(&q[0], &q1[0], 4);
    }

    Bool AdditionAssign()
    {
        QuatF32 q(45, 45, 45, 45);
        QuatF32 q1(45, 46, 47, 48);
        q += q1;
        return q[0] == (Float32)90 && q[1] == (Float32)91 &&
            q[2] == (Float32)92 && q[3] == (Float32)93;
    }

    Bool SubtractionAssign()
    {
        QuatF32 q(45, 45, 45, 45);
        QuatF32 q1(45, 44, 43, 42);
        q -= q1;
        return q[0] == (Float32)0 && q[1] == (Float32)1 &&
            q[2] == (Float32)2 && q[3] == (Float32)3;
    }

    Bool MultiplicationAssign()
    {
        QuatF32 q(1, 2, 3, 4);
        QuatF32 q1(5, 6, 7, 8);
        q *= q1;
        return q[0] == (Float32)-60 && q[1] == (Float32)12 &&
            q[2] == (Float32)30 && q[3] == (Float32)24;
    }

    Bool DivisionAssign()
    {
        QuatF32 q(0, 0, 0, 1);
        QuatF32 q1;
        q /= q;
        return Math::Float32::IsAlmostEqual(&q[0], &q1[0], 4);
    }

    Bool SetIdentity()
    {
        QuatF32 q(Vector<Float32, 3>(0, 1, 0));
        q.SetIdentity();
        return q[0] == (Float32)1 && q[1] == (Float32)0 &&
            q[2] == (Float32)0 && q[3] == (Float32)0;
    }

    Bool Invert()
    {
        QuatF32 q(1, 5, 8, -3);
        QuatF32 q2;
        q.Normalize();
        q.Invert();
        q *= QuatF32(1, 5, 8, -3).Normalize();
        return Math::Float32::IsAlmostEqual(&q[0], &q2[0], 4);
    }

    Bool Conjugate()
    {
        QuatF32 q(-1, 2, -3, 4);
        q.Conjugate();
        return q[0] == (Float32)-1 && q[1] == (Float32)-2 &&
            q[2] == (Float32)3 && q[3] == (Float32)-4;
    }

    Bool Normalize()
    {
        QuatF32 q(7, 7, 7, 7);
        q.Normalize();
        return q[0] == 0.5f && q[1] == 0.5f &&
            q[2] == 0.5f && q[3] == 0.5f;
    }

    Bool DotProduct()
    {
        QuatF32 q(1, 2, 3, 4);
        QuatF32 q1(5, 6, 7, 8);
        return q.DotProduct(q1) == (Float32)70;
    }

    Bool CrossProduct()
    {
        QuatF32 q(1, 2, 3, 4);
        QuatF32 q1(5, 6, 7, 8);
        QuatF32 q2(0, -4, 8, -4);
        return q.CrossProduct(q1) == q2;
    }

    Bool Inverse()
    {
        QuatF32 q(1, 5, 8, -3);
        QuatF32 q2;
        q.Normalize();
        q = q.Inverse();
        q *= QuatF32(1, 5, 8, -3).Normalize();
        return Math::Float32::IsAlmostEqual(&q[0], &q2[0], 4);
    }

    Bool MultiplyPosition()
    {
        QuatF32 q(0, 0, 0, 1);
        Vector<Float32, 4> v1(1, 0, 0, 0);
        Vector<Float32, 4> v2;
        Vector<Float32, 4> v3(-1, 0, 0, 0);
        v2 = q*v1;
        return Math::Float32::IsAlmostEqual(&v3[0], &v2[0], 4);
    }

    Bool Equal()
    {
        QuatF32 q(0, 0, 1, 0);
        QuatF32 q1(0, 0, 1, 0);
        return q == q1;
    }

    Bool Unequal()
    {
        QuatF32 q(0, 0, 1, 0);
        QuatF32 q1(0, 0, 1, 0);
        return !(q != q1);
    }

    Bool IsInfinity()
    {
        QuatF32 q(0, Math::Float32::POS_INFINITY, 1, 0);
        return q.IsInfinite();
    }

    Bool IsNaN()
    {
        QuatF32 q(0, 0, Math::Float32::QUITE_NAN, 0);
        return q.IsNaN();
    }

    Bool LengthAsQuat()
    {
        QuatF32 q(1, 1, 1, 1);
        QuatF32 q1(1, 1, 1, 1);
        q1 = q.LengthAsQuat();
        return q1[0] == (Float32)2 && q1[1] == (Float32)2 &&
            q1[2] == (Float32)2 && q1[3] == (Float32)2;
    }

    Bool Length()
    {
        QuatF32 q(1, 1, 1, 1);
        return q.Length() == (Float32)2;
    }

    Bool SquareLengthAsQuat()
    {
        QuatF32 q(1, 1, 1, 1);
        QuatF32 q1(1, 1, 1, 1);
        q1 = q.SquareLengthAsQuat();
        return q1[0] == (Float32)4 && q1[1] == (Float32)4 &&
            q1[2] == (Float32)4 && q1[3] == (Float32)4;
    }

    Bool SquareLength()
    {
        QuatF32 q(1, 1, 1, 1);
        return q.SquareLength() == 4;
    }

    Bool Slerp()
    {
        QuatF32 q(1, 0, 0, 0);
        QuatF32 q1(0, 0, 0, 1);
        QuatF32 q2(0.7071067811865475f, 0, 0, 0.7071067811865475f);
        QuatF32 q3;
        q3 = q.Slerp(q1, 0.5);
        return Math::Float32::IsAlmostEqual(&q3[0], &q2[0], 4);
    }

    Bool ToAxisAngle()
    {
        QuatF32 q(0, 1, 0, 0);
        Vector<Float32, 3> v1;
        Vector<Float32, 3> v2(1, 0, 0);
        Float32 angle;
        q.ToAxisAngle(v1, angle);
        return angle == 180 && v1 == v2;
    }

    Bool GetAxis()
    {
        QuatF32 q(1, 2, 3, 4);
        Vector<Float32, 3> v1(2, 3, 4);
        return q.GetAxis() == v1;
    }

    Bool GetAngle()
    {
        QuatF32 q(1, 2, 3, 4);
        return q.GetAngle() == 1;
    }

    Bool AsRotationMatrix()
    {
        QuatF32 q(0, 0, 0, 1);
        Matrix<Float32, 3, 3> rot;
        Matrix<Float32, 3, 3> rot1;
        Float32 v[] = {-1,0,0, 0,-1,0, 0,0,1};
        RF_SysMem::Copy(rot1.Value, v, sizeof(Float32) * 9);
        rot = q.AsRotationMatrix();
        return rot == rot1;
    }

    Bool AsMatrix()
    {
        QuatF32 q(0, 0, 0, 1);
        Matrix<Float32, 4, 4> rot;
        Matrix<Float32, 4, 4> rot1;
        Float32 v[] = {-1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,0,0,1};
        RF_SysMem::Copy(rot1.Value, v, sizeof(Float32) * 12);
        rot = q.AsMatrix();
        return rot == rot1;
    }

    Bool ArrayOperator()
    {
        QuatF32 q(1, 2, 3, 4);
        return q[0] == (Float32)1 && q[1] == (Float32)2 &&
            q[2] == (Float32)3 && q[3] == (Float32)4;
    }
};

class GeometryQuatF64Test:public TestSuite
{
public:
    GeometryQuatF64Test()
    :TestSuite("RadonFramework::Math::Geometry::QuatF64-Test"_rfs)
    {
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::DefaultConstructor),
                "GeometryQuatF64Test::DefaultConstructor"_rfs,
                "DefaultConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::CopyConstructor),
                "GeometryQuatF64Test::CopyConstructor"_rfs,
                "CopyConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::AssignOperator),
                "GeometryQuatF64Test::AssignOperator"_rfs,
                "AssignOperator"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::AxisAngleConstructor),
                "GeometryQuatF64Test::AxisAngleConstructor"_rfs,
                "AxisAngleConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::SeperateElementsConstructor),
                "GeometryQuatF64Test::SeperateElementsConstructor"_rfs,
                "SeperateElementsConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::DirectionConstructor),
                "GeometryQuatF64Test::DirectionConstructor"_rfs,
                "DirectionConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::RotationMatrixConstructor),
                "GeometryQuatF64Test::RotationMatrixConstructor"_rfs,
                "RotationMatrixConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::EulerConstructor),
                "GeometryQuatF64Test::EulerConstructor"_rfs,
                "EulerConstructor"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Addition),
                "GeometryQuatF64Test::Addition"_rfs,
                "Addition"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Subtraction),
                "GeometryQuatF64Test::Subtraction"_rfs,
                "Subtraction"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Multiplication),
                "GeometryQuatF64Test::Multiplication"_rfs,
                "Multiplication"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Division),
                "GeometryQuatF64Test::Division"_rfs,
                "Division"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::AdditionAssign),
                "GeometryQuatF64Test::AdditionAssign"_rfs,
                "AdditionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::SubtractionAssign),
                "GeometryQuatF64Test::SubtractionAssign"_rfs,
                "SubtractionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::MultiplicationAssign),
                "GeometryQuatF64Test::MultiplicationAssign"_rfs,
                "MultiplicationAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::DivisionAssign),
                "GeometryQuatF64Test::DivisionAssign"_rfs,
                "DivisionAssign"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::SetIdentity),
                "GeometryQuatF64Test::SetIdentity"_rfs,
                "SetIdentity"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Invert),
                "GeometryQuatF64Test::Invert"_rfs,
                "Invert"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Conjugate),
                "GeometryQuatF64Test::Conjugate"_rfs,
                "Conjugate"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Normalize),
                "GeometryQuatF64Test::Normalize"_rfs,
                "Normalize"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::DotProduct),
                "GeometryQuatF64Test::DotProduct"_rfs,
                "DotProduct"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::CrossProduct),
                "GeometryQuatF64Test::CrossProduct"_rfs,
                "CrossProduct"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Inverse),
                "GeometryQuatF64Test::Inverse"_rfs,
                "Inverse"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::MultiplyPosition),
                "GeometryQuatF64Test::MultiplyPosition"_rfs,
                "MultiplyPosition"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Equal),
                "GeometryQuatF64Test::Equal"_rfs,
                "Equal"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Unequal),
                "GeometryQuatF64Test::Unequal"_rfs,
                "Unequal"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::IsInfinity),
                "GeometryQuatF64Test::IsInfinity"_rfs,
                "IsInfinity"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::IsNaN),
                "GeometryQuatF64Test::IsNaN"_rfs,
                "IsNaN"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::LengthAsQuat),
                "GeometryQuatF64Test::LengthAsQuat"_rfs,
                "LengthAsQuat"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Length),
                "GeometryQuatF64Test::Length"_rfs,
                "Length"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::SquareLengthAsQuat),
                "GeometryQuatF64Test::SquareLengthAsQuat"_rfs,
                "SquareLengthAsQuat"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::SquareLength),
                "GeometryQuatF64Test::SquareLength"_rfs,
                "SquareLength"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::Slerp),
                "GeometryQuatF64Test::Slerp"_rfs,
                "Slerp"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::ToAxisAngle),
                "GeometryQuatF64Test::ToAxisAngle"_rfs,
                "ToAxisAngle"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::GetAxis),
                "GeometryQuatF64Test::GetAxis"_rfs,
                "GetAxis"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::GetAngle),
                "GeometryQuatF64Test::GetAngle"_rfs,
                "GetAngle"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::AsRotationMatrix),
                "GeometryQuatF64Test::AsRotationMatrix"_rfs,
                "AsRotationMatrix"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::AsMatrix),
                "GeometryQuatF64Test::AsMatrix"_rfs,
                "AsMatrix"_rfs);
        AddTest(MakeDelegate(this, &GeometryQuatF64Test::ArrayOperator),
                "GeometryQuatF64Test::ArrayOperator"_rfs,
                "ArrayOperator"_rfs);
    }

    Bool DefaultConstructor()
    {
        QuatF64 q;
        return q[0] == (Float64)1 && q[1] == (Float64)0 &&
            q[2] == (Float64)0 && q[3] == (Float64)0;
    }

    Bool CopyConstructor()
    {
        QuatF64 q1;
        q1[2] = (Float64)2;
        QuatF64 q(q1);
        return q[0] == (Float64)1 && q[1] == (Float64)0 &&
            q[2] == (Float64)2 && q[3] == (Float64)0;
    }

    Bool AssignOperator()
    {
        QuatF64 q;
        QuatF64 q1;
        q1[2] = (Float64)2;
        q = q1;
        return q[0] == (Float64)1 && q[1] == (Float64)0 &&
            q[2] == (Float64)2 && q[3] == (Float64)0;
    }

    Bool AxisAngleConstructor()
    {
        QuatF64 q(180.0, Vector<Float64, 3>(1, 0, 0));
        Vector<Float64, 4> v(0, 1, 0, 0);
        return Math::Float64::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool SeperateElementsConstructor()
    {
        QuatF64 q(45, 0, 1, 0);
        return q[0] == (Float64)45 && q[1] == (Float64)0 &&
            q[2] == (Float64)1 && q[3] == (Float64)0;
    }

    Bool DirectionConstructor()
    {
        QuatF64 q(Vector<Float64, 3>(0, 0, 1));
        Vector<Float64, 4> v(1, 0, 0, 0);
        return Math::Float64::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool RotationMatrixConstructor()
    {
        Float64 a[] = {-1,0,0, 0,-1,0, 0,0,1};
        Matrix<Float64, 3, 3> mat;
        RF_SysMem::Copy(mat.Value, a, sizeof(Float64) * 9);
        QuatF64 q(mat);
        Vector<Float64, 4> v(0, 0, 0, 1);
        return Math::Float64::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool EulerConstructor()
    {
        QuatF64 q(0, 180, 0);
        Vector<Float64, 4> v(0, 0, 0, 1);
        return Math::Float64::IsAlmostEqual(&q[0], &v[0], 4);
    }

    Bool Addition()
    {
        QuatF64 q(45, 45, 45, 45);
        QuatF64 q1(45, 46, 47, 48);
        q = q + q1;
        return q[0] == (Float64)90 && q[1] == (Float64)91 &&
            q[2] == (Float64)92 && q[3] == (Float64)93;
    }

    Bool Subtraction()
    {
        QuatF64 q(45, 45, 45, 45);
        QuatF64 q1(45, 44, 43, 42);
        q = q - q1;
        return q[0] == (Float64)0 && q[1] == (Float64)1 &&
            q[2] == (Float64)2 && q[3] == (Float64)3;
    }

    Bool Multiplication()
    {
        QuatF64 q(1, 2, 3, 4);
        QuatF64 q1(5, 6, 7, 8);
        q = q*q1;
        return q[0] == (Float64)-60 && q[1] == (Float64)12 &&
            q[2] == (Float64)30 && q[3] == (Float64)24;
    }

    Bool Division()
    {
        QuatF64 q(0, 0, 0, 1);
        QuatF64 q1;
        q = q / q;
        return Math::Float64::IsAlmostEqual(&q[0], &q1[0], 4);
    }

    Bool AdditionAssign()
    {
        QuatF64 q(45, 45, 45, 45);
        QuatF64 q1(45, 46, 47, 48);
        q += q1;
        return q[0] == (Float64)90 && q[1] == (Float64)91 &&
            q[2] == (Float64)92 && q[3] == (Float64)93;
    }

    Bool SubtractionAssign()
    {
        QuatF64 q(45, 45, 45, 45);
        QuatF64 q1(45, 44, 43, 42);
        q -= q1;
        return q[0] == (Float64)0 && q[1] == (Float64)1 &&
            q[2] == (Float64)2 && q[3] == (Float64)3;
    }

    Bool MultiplicationAssign()
    {
        QuatF64 q(1, 2, 3, 4);
        QuatF64 q1(5, 6, 7, 8);
        q *= q1;
        return q[0] == (Float64)-60 && q[1] == (Float64)12 &&
            q[2] == (Float64)30 && q[3] == (Float64)24;
    }

    Bool DivisionAssign()
    {
        QuatF64 q(0, 0, 0, 1);
        QuatF64 q1;
        q /= q;
        return Math::Float64::IsAlmostEqual(&q[0], &q1[0], 4);
    }

    Bool SetIdentity()
    {
        QuatF64 q(Vector<Float64, 3>(0, 1, 0));
        q.SetIdentity();
        return q[0] == (Float64)1 && q[1] == (Float64)0 &&
            q[2] == (Float64)0 && q[3] == (Float64)0;
    }

    Bool Invert()
    {
        QuatF64 q(1, 5, 8, -3);
        QuatF64 q2;
        q.Normalize();
        q.Invert();
        q *= QuatF64(1, 5, 8, -3).Normalize();
        return Math::Float64::IsAlmostEqual(&q[0], &q2[0], 4);
    }

    Bool Conjugate()
    {
        QuatF64 q(-1, 2, -3, 4);
        q.Conjugate();
        return q[0] == (Float64)-1 && q[1] == (Float64)-2 &&
            q[2] == (Float64)3 && q[3] == (Float64)-4;
    }

    Bool Normalize()
    {
        QuatF64 q(7, 7, 7, 7);
        q.Normalize();
        return q[0] == 0.5 && q[1] == 0.5 &&
            q[2] == 0.5 && q[3] == 0.5;
    }

    Bool DotProduct()
    {
        QuatF64 q(1, 2, 3, 4);
        QuatF64 q1(5, 6, 7, 8);
        return q.DotProduct(q1) == (Float64)70;
    }

    Bool CrossProduct()
    {
        QuatF64 q(1, 2, 3, 4);
        QuatF64 q1(5, 6, 7, 8);
        QuatF64 q2(0, -4, 8, -4);
        return q.CrossProduct(q1) == q2;
    }

    Bool Inverse()
    {
        QuatF64 q(1, 5, 8, -3);
        QuatF64 q2;
        q.Normalize();
        q = q.Inverse();
        q *= QuatF64(1, 5, 8, -3).Normalize();
        return Math::Float64::IsAlmostEqual(&q[0], &q2[0], 4);
    }

    Bool MultiplyPosition()
    {
        QuatF64 q(0, 0, 0, 1);
        Vector<Float64, 4> v1(1, 0, 0, 0);
        Vector<Float64, 4> v2;
        Vector<Float64, 4> v3(-1, 0, 0, 0);
        v2 = q*v1;
        return Math::Float64::IsAlmostEqual(&v3[0], &v2[0], 4);
    }

    Bool Equal()
    {
        QuatF64 q(0, 0, 1, 0);
        QuatF64 q1(0, 0, 1, 0);
        return q == q1;
    }

    Bool Unequal()
    {
        QuatF64 q(0, 0, 1, 0);
        QuatF64 q1(0, 0, 1, 0);
        return !(q != q1);
    }

    Bool IsInfinity()
    {
        QuatF64 q(0, Math::Float64::POS_INFINITY, 1, 0);
        return q.IsInfinite();
    }

    Bool IsNaN()
    {
        QuatF64 q(0, 0, Math::Float64::QUITE_NAN, 0);
        return q.IsNaN();
    }

    Bool LengthAsQuat()
    {
        QuatF64 q(1, 1, 1, 1);
        QuatF64 q1(1, 1, 1, 1);
        q1 = q.LengthAsQuat();
        return q1[0] == (Float64)2 && q1[1] == (Float64)2 &&
            q1[2] == (Float64)2 && q1[3] == (Float64)2;
    }

    Bool Length()
    {
        QuatF64 q(1, 1, 1, 1);
        return q.Length() == (Float64)2;
    }

    Bool SquareLengthAsQuat()
    {
        QuatF64 q(1, 1, 1, 1);
        QuatF64 q1(1, 1, 1, 1);
        q1 = q.SquareLengthAsQuat();
        return q1[0] == (Float64)4 && q1[1] == (Float64)4 &&
            q1[2] == (Float64)4 && q1[3] == (Float64)4;
    }

    Bool SquareLength()
    {
        QuatF64 q(1, 1, 1, 1);
        return q.SquareLength() == 4;
    }

    Bool Slerp()
    {
        QuatF64 q(1, 0, 0, 0);
        QuatF64 q1(0, 0, 0, 1);
        QuatF64 q2(0.7071067811865475, 0, 0, 0.7071067811865475);
        QuatF64 q3;
        q3 = q.Slerp(q1, 0.5);
        return Math::Float64::IsAlmostEqual(&q3[0], &q2[0], 4);
    }

    Bool ToAxisAngle()
    {
        QuatF64 q(0, 1, 0, 0);
        Vector<Float64, 3> v1;
        Vector<Float64, 3> v2(1, 0, 0);
        Float64 angle;
        q.ToAxisAngle(v1, angle);
        return angle == 180 && v1 == v2;
    }

    Bool GetAxis()
    {
        QuatF64 q(1, 2, 3, 4);
        Vector<Float64, 3> v1(2, 3, 4);
        return q.GetAxis() == v1;
    }

    Bool GetAngle()
    {
        QuatF64 q(1, 2, 3, 4);
        return q.GetAngle() == 1;
    }

    Bool AsRotationMatrix()
    {
        QuatF64 q(0, 0, 0, 1);
        Matrix<Float64, 3, 3> rot;
        Matrix<Float64, 3, 3> rot1;
        Float64 v[] = {-1,0,0, 0,-1,0, 0,0,1};
        RF_SysMem::Copy(rot1.Value, v, sizeof(Float64) * 9);
        rot = q.AsRotationMatrix();
        return rot == rot1;
    }

    Bool AsMatrix()
    {
        QuatF64 q(0, 0, 0, 1);
        Matrix<Float64, 4, 4> rot;
        Matrix<Float64, 4, 4> rot1;
        Float64 v[] = {-1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,0,0,1};
        RF_SysMem::Copy(rot1.Value, v, sizeof(Float64) * 12);
        rot = q.AsMatrix();
        return rot == rot1;
    }

    Bool ArrayOperator()
    {
        QuatF64 q(1, 2, 3, 4);
        return q[0] == (Float64)1 && q[1] == (Float64)2 &&
            q[2] == (Float64)3 && q[3] == (Float64)4;
    }
};

GeometryQuatF32Test Quaternion32Test;
GeometryQuatF64Test Quaternion64Test;
