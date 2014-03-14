#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Math/Geometry/Quaternion.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class GeometryQuaternionTest:public TestSuite
{
    public:
        GeometryQuaternionTest()
        :TestSuite("RadonFramework::Math::Geometry::Quaternion-Test")
        {
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::DefaultConstructor),"DefaultConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::CopyConstructor),"CopyConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::AssignOperator),"AssignOperator");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::AxisAngleConstructor),"AxisAngleConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::SeperateElementsConstructor),"SeperateElementsConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::DirectionConstructor),"DirectionConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::RotationMatrixConstructor),"RotationMatrixConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::EulerConstructor),"EulerConstructor");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Addition),"Addition");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Subtraction),"Subtraction");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Multiplication),"Multiplication");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Division),"Division");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::AdditionAssign),"AdditionAssign");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::SubtractionAssign),"SubtractionAssign");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::MultiplicationAssign),"MultiplicationAssign");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::DivisionAssign),"DivisionAssign");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::SetIdentity),"SetIdentity");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Invert),"Invert");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Conjugate),"Conjugate");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Normalize),"Normalize");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::DotProduct),"DotProduct");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::CrossProduct),"CrossProduct");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Inverse),"Inverse");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::MultiplyPosition),"MultiplyPosition");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Equal),"Equal");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Unequal),"Unequal");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::IsInfinity),"IsInfinity");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::IsNaN),"IsNaN");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::LengthAsQuat),"LengthAsQuat");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Length),"Length");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::SquareLengthAsQuat),"SquareLengthAsQuat");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::SquareLength),"SquareLength");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::Slerp),"Slerp");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::ToAxisAngle),"ToAxisAngle");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::GetAxis),"GetAxis");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::GetAngle),"GetAngle");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::AsRotationMatrix),"AsRotationMatrix");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::AsMatrix),"AsMatrix");
            AddTest(MakeDelegate(this,&GeometryQuaternionTest::ArrayOperator),"ArrayOperator");
        }

        Bool DefaultConstructor()
        {
            Quaternion<Float32> q;
            return q[0]==(Float32)1 && q[1]==(Float32)0 &&
                   q[2]==(Float32)0 && q[3]==(Float32)0;
        }

        Bool CopyConstructor()
        {
            Quaternion<Float32> q1;
            q1[2]=(Float32)2;
            Quaternion<Float32> q(q1);
            return q[0]==(Float32)1 && q[1]==(Float32)0 &&
                   q[2]==(Float32)2 && q[3]==(Float32)0;
        }

        Bool AssignOperator()
        {
            Quaternion<Float32> q;
            Quaternion<Float32> q1;
            q1[2]=(Float32)2;
            q=q1;
            return q[0]==(Float32)1 && q[1]==(Float32)0 &&
                   q[2]==(Float32)2 && q[3]==(Float32)0;
        }

        Bool AxisAngleConstructor()
        {
            Quaternion<Float32> q(180.0f,Vector<Float32,3>(1,0,0));
            Vector<Float32,4> v(0,1,0,0);
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&v[0],4);
        }

        Bool SeperateElementsConstructor()
        {
            Quaternion<Float32> q(45,0,1,0);
            return q[0]==(Float32)45 && q[1]==(Float32)0 &&
                   q[2]==(Float32)1 && q[3]==(Float32)0;
        }

        Bool DirectionConstructor()
        {
            Quaternion<Float32> q(Vector<Float32,3>(0,0,1));
            Vector<Float32,4> v(1,0,0,0);
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&v[0],4);
        }

        Bool RotationMatrixConstructor()
        {
            Float32 a[]={-1,0,0, 0,-1,0, 0,0,1};
            Matrix<Float32,3,3> mat;
            RFMEM::Copy(mat.Value,a,sizeof(Float32)*9);
            Quaternion<Float32> q(mat);
            Vector<Float32,4> v(0,0,0,1);
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&v[0],4);
        }

        Bool EulerConstructor()
        {
            Quaternion<Float32> q(0,180,0);
            Vector<Float32,4> v(0,0,0,1);
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&v[0],4);
        }

        Bool Addition()
        {
            Quaternion<Float32> q(45,45,45,45);
            Quaternion<Float32> q1(45,46,47,48);
            q=q+q1;
            return q[0]==(Float32)90 && q[1]==(Float32)91 &&
                   q[2]==(Float32)92 && q[3]==(Float32)93;
        }

        Bool Subtraction()
        {
            Quaternion<Float32> q(45,45,45,45);
            Quaternion<Float32> q1(45,44,43,42);
            q=q-q1;
            return q[0]==(Float32)0 && q[1]==(Float32)1 &&
                   q[2]==(Float32)2 && q[3]==(Float32)3;
        }

        Bool Multiplication()
        {
            Quaternion<Float32> q(1,2,3,4);
            Quaternion<Float32> q1(5,6,7,8);
            q=q*q1;
            return q[0]==(Float32)-60 && q[1]==(Float32)12 &&
                   q[2]==(Float32)30 && q[3]==(Float32)24;
        }

        Bool Division()
        {
            Quaternion<Float32> q(0,0,0,1);
            Quaternion<Float32> q1;
            q=q/q;
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&q1[0],4);
        }

        Bool AdditionAssign()
        {
            Quaternion<Float32> q(45,45,45,45);
            Quaternion<Float32> q1(45,46,47,48);
            q+=q1;
            return q[0]==(Float32)90 && q[1]==(Float32)91 &&
                   q[2]==(Float32)92 && q[3]==(Float32)93;
        }

        Bool SubtractionAssign()
        {
            Quaternion<Float32> q(45,45,45,45);
            Quaternion<Float32> q1(45,44,43,42);
            q-=q1;
            return q[0]==(Float32)0 && q[1]==(Float32)1 &&
                   q[2]==(Float32)2 && q[3]==(Float32)3;
        }

        Bool MultiplicationAssign()
        {
            Quaternion<Float32> q(1,2,3,4);
            Quaternion<Float32> q1(5,6,7,8);
            q*=q1;
            return q[0]==(Float32)-60 && q[1]==(Float32)12 &&
                   q[2]==(Float32)30 && q[3]==(Float32)24;
        }

        Bool DivisionAssign()
        {
            Quaternion<Float32> q(0,0,0,1);
            Quaternion<Float32> q1;
            q/=q;
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&q1[0],4);
        }

        Bool SetIdentity()
        {
            Quaternion<Float32> q(Vector<Float32,3>(0,1,0));
            q.SetIdentity();
            return q[0]==(Float32)1 && q[1]==(Float32)0 &&
                   q[2]==(Float32)0 && q[3]==(Float32)0;
        }

        Bool Invert()
        {
            Quaternion<Float32> q(1,5,8,-3);
            Quaternion<Float32> q2;
            q.Normalize();
            q.Invert();
            q*=Quaternion<Float32>(1,5,8,-3).Normalize();
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&q2[0],4);
        }

        Bool Conjugate()
        {
            Quaternion<Float32> q(-1,2,-3,4);
            q.Conjugate();
            return q[0]==(Float32)-1 && q[1]==(Float32)-2 &&
                   q[2]==(Float32)3 && q[3]==(Float32)-4;
        }

        Bool Normalize()
        {
            Quaternion<Float32> q(7,7,7,7);
            q.Normalize();
            return q[0]==0.5f && q[1]==0.5f &&
                   q[2]==0.5f && q[3]==0.5f;
        }

        Bool DotProduct()
        {
            Quaternion<Float32> q(1,2,3,4);
            Quaternion<Float32> q1(5,6,7,8);
            return q.DotProduct(q1)==(Float32)70;
        }

        Bool CrossProduct()
        {
            Quaternion<Float32> q(1,2,3,4);
            Quaternion<Float32> q1(5,6,7,8);
            Quaternion<Float32> q2(0,-4,8,-4);
            return q.CrossProduct(q1)==q2;
        }

        Bool Inverse()
        {
            Quaternion<Float32> q(1,5,8,-3);
            Quaternion<Float32> q2;
            q.Normalize();
            q=q.Inverse();
            q*=Quaternion<Float32>(1,5,8,-3).Normalize();
            return Math::Math<Float32>::IsAlmostEqual(&q[0],&q2[0],4);
        }

        Bool MultiplyPosition()
        {
            Quaternion<Float32> q(0,0,0,1);
            Vector<Float32,4> v1(1,0,0,0);
            Vector<Float32,4> v2;
            Vector<Float32,4> v3(-1,0,0,0);
            v2=q*v1;
            return Math::Math<Float32>::IsAlmostEqual(&v3[0],&v2[0],4);
        }

        Bool Equal()
        {
            Quaternion<Float32> q(0,0,1,0);
            Quaternion<Float32> q1(0,0,1,0);
            return q==q1;
        }

        Bool Unequal()
        {
            Quaternion<Float32> q(0,0,1,0);
            Quaternion<Float32> q1(0,0,1,0);
            return !(q!=q1);
        }

        Bool IsInfinity()
        {
            Quaternion<Float32> q(0,Math::Math<Float32>::INFINITY,1,0);
            return q.IsInfinite();
        }

        Bool IsNaN()
        {
            Quaternion<Float32> q(0,0,Math::Math<Float32>::QUITE_NAN,0);
            return q.IsNaN();
        }

        Bool LengthAsQuat()
        {
            Quaternion<Float32> q(1,1,1,1);
            Quaternion<Float32> q1(1,1,1,1);
            q1=q.LengthAsQuat();
            return q1[0]==(Float32)2 && q1[1]==(Float32)2 &&
                   q1[2]==(Float32)2 && q1[3]==(Float32)2;
        }

        Bool Length()
        {
            Quaternion<Float32> q(1,1,1,1);
            return q.Length()==(Float32)2;
        }

        Bool SquareLengthAsQuat()
        {
            Quaternion<Float32> q(1,1,1,1);
            Quaternion<Float32> q1(1,1,1,1);
            q1=q.SquareLengthAsQuat();
            return q1[0]==(Float32)4 && q1[1]==(Float32)4 &&
                   q1[2]==(Float32)4 && q1[3]==(Float32)4;
        }

        Bool SquareLength()
        {
            Quaternion<Float32> q(1,1,1,1);
            return q.SquareLength()==4;
        }

        Bool Slerp()
        {
            Quaternion<Float32> q(1,0,0,0);
            Quaternion<Float32> q1(0,0,0,1);
            Quaternion<Float32> q2(0.7071067811865475f,0,0,0.7071067811865475f);
            Quaternion<Float32> q3;
            q3=q.Slerp(q1,0.5);
            return Math::Math<Float32>::IsAlmostEqual(&q3[0],&q2[0],4);
        }

        Bool ToAxisAngle()
        {
            Quaternion<Float32> q(0,1,0,0);
            Vector<Float32,3> v1;
            Vector<Float32,3> v2(1,0,0);
            Float32 angle;
            q.ToAxisAngle(v1,angle);
            return angle==180 && v1==v2;
        }

        Bool GetAxis()
        {
            Quaternion<Float32> q(1,2,3,4);
            Vector<Float32,3> v1(2,3,4);
            return q.GetAxis()==v1;
        }

        Bool GetAngle()
        {
            Quaternion<Float32> q(1,2,3,4);
            return q.GetAngle()==1;
        }

        Bool AsRotationMatrix()
        {
            Quaternion<Float32> q(0,0,0,1);
            Matrix<Float32,3,3> rot;
            Matrix<Float32,3,3> rot1;
            Float32 v[]={-1,0,0, 0,-1,0, 0,0,1};
            RFMEM::Copy(rot1.Value,v,sizeof(Float32)*9);
            rot=q.AsRotationMatrix();
            return rot==rot1;
        }

        Bool AsMatrix()
        {
            Quaternion<Float32> q(0,0,0,1);
            Matrix<Float32,4,4> rot;
            Matrix<Float32,4,4> rot1;
            Float32 v[]={-1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,0,0,1};
            RFMEM::Copy(rot1.Value,v,sizeof(Float32)*12);
            rot=q.AsMatrix();
            return rot==rot1;
        }

        Bool ArrayOperator()
        {
            Quaternion<Float32> q(1,2,3,4);
            return q[0]==(Float32)1 && q[1]==(Float32)2 &&
                   q[2]==(Float32)3 && q[3]==(Float32)4;
        }
};

GeometryQuaternionTest QuaternionTest;
