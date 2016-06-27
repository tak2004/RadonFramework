#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class GeometryMatrixTest:public TestSuite
{
public:
    GeometryMatrixTest()
    :TestSuite("RadonFramework::Math::Geometry::Matrix-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fDefaultConstructor),
            "GeometryMatrixTest::Matrix2fDefaultConstructor"_rfs, 
            "DefaultConstructor2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fDefaultConstructor),
            "GeometryMatrixTest::Matrix3fDefaultConstructor"_rfs, 
            "DefaultConstructor3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fDefaultConstructor),
            "GeometryMatrixTest::Matrix4fDefaultConstructor"_rfs, 
            "DefaultConstructor4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fCopyConstructor),
            "GeometryMatrixTest::Matrix2fCopyConstructor"_rfs, 
            "CopyConstructor2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fCopyConstructor),
            "GeometryMatrixTest::Matrix3fCopyConstructor"_rfs, 
            "CopyConstructor3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fCopyConstructor),
            "GeometryMatrixTest::Matrix4fCopyConstructor"_rfs, 
            "CopyConstructor4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fAssignOperator),
            "GeometryMatrixTest::Matrix2fAssignOperator"_rfs, 
            "AssignOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fAssignOperator),
            "GeometryMatrixTest::Matrix3fAssignOperator"_rfs, 
            "AssignOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fAssignOperator),
            "GeometryMatrixTest::Matrix4fAssignOperator"_rfs, 
            "AssignOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fGetRow),
            "GeometryMatrixTest::Matrix2fGetRow"_rfs, 
            "GetRow2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fGetRow),
            "GeometryMatrixTest::Matrix3fGetRow"_rfs, 
            "GetRow3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fGetRow),
            "GeometryMatrixTest::Matrix4fGetRow"_rfs, 
            "GetRow4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fGetColumn),
            "GeometryMatrixTest::Matrix2fGetColumn"_rfs, 
            "GetColumn2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fGetColumn),
            "GeometryMatrixTest::Matrix3fGetColumn"_rfs, 
            "GetColumn3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fGetColumn),
            "GeometryMatrixTest::Matrix4fGetColumn"_rfs, 
            "GetColumn4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fSetColumn),
            "GeometryMatrixTest::Matrix2fSetColumn"_rfs, 
            "SetColumn2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fSetColumn),
            "GeometryMatrixTest::Matrix3fSetColumn"_rfs, 
            "SetColumn3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fSetColumn),
            "GeometryMatrixTest::Matrix4fSetColumn"_rfs, 
            "SetColumn4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fTranspose),
            "GeometryMatrixTest::Matrix2fTranspose"_rfs, 
            "Transpose2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fTranspose),
            "GeometryMatrixTest::Matrix3fTranspose"_rfs, 
            "Transpose3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fTranspose),
            "GeometryMatrixTest::Matrix4fTranspose"_rfs, 
            "Transpose4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fScale),
            "GeometryMatrixTest::Matrix2fScale"_rfs, 
            "Scale2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fScale),
            "GeometryMatrixTest::Matrix3fScale"_rfs, 
            "Scale3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fScale),
            "GeometryMatrixTest::Matrix4fScale"_rfs, 
            "Scale4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fFunctionOperator),
            "GeometryMatrixTest::Matrix2fFunctionOperator"_rfs, 
            "FunctionOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fFunctionOperator),
            "GeometryMatrixTest::Matrix3fFunctionOperator"_rfs, 
            "FunctionOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fFunctionOperator),
            "GeometryMatrixTest::Matrix4fFunctionOperator"_rfs, 
            "FunctionOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fArrayOperator),
            "GeometryMatrixTest::Matrix2fArrayOperator"_rfs, 
            "ArrayOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fArrayOperator),
            "GeometryMatrixTest::Matrix3fArrayOperator"_rfs, 
            "ArrayOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fArrayOperator),
            "GeometryMatrixTest::Matrix4fArrayOperator"_rfs, 
            "ArrayOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fMultiplicationOperator),
            "GeometryMatrixTest::Matrix2fMultiplicationOperator"_rfs, 
            "MultiplicationOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fMultiplicationOperator),
            "GeometryMatrixTest::Matrix3fMultiplicationOperator"_rfs, 
            "MultiplicationOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fMultiplicationOperator),
            "GeometryMatrixTest::Matrix4fMultiplicationOperator"_rfs, 
            "MultiplicationOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fDivisionOperator),
            "GeometryMatrixTest::Matrix2fDivisionOperator"_rfs, 
            "DivisionOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fDivisionOperator),
            "GeometryMatrixTest::Matrix3fDivisionOperator"_rfs, 
            "DivisionOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fDivisionOperator),
            "GeometryMatrixTest::Matrix4fDivisionOperator"_rfs, 
            "DivisionOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fMultiplicationOperatorVector),
            "GeometryMatrixTest::Matrix2fMultiplicationOperatorVector"_rfs, 
            "MultiplicationOperatorVector2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fMultiplicationOperatorVector),
            "GeometryMatrixTest::Matrix3fMultiplicationOperatorVector"_rfs, 
            "MultiplicationOperatorVector3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fMultiplicationOperatorVector),
            "GeometryMatrixTest::Matrix4fMultiplicationOperatorVector"_rfs, 
            "MultiplicationOperatorVector4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fMultiplicationAssignOperator),
            "GeometryMatrixTest::Matrix2fMultiplicationAssignOperator"_rfs, 
            "MultiplicationAssignOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fMultiplicationAssignOperator),
            "GeometryMatrixTest::Matrix3fMultiplicationAssignOperator"_rfs, 
            "MultiplicationAssignOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fMultiplicationAssignOperator),
            "GeometryMatrixTest::Matrix4fMultiplicationAssignOperator"_rfs, 
            "MultiplicationAssignOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fDivisionAssignOperator),
            "GeometryMatrixTest::Matrix2fDivisionAssignOperator"_rfs, 
            "DivisionAssignOperator2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fDivisionAssignOperator),
            "GeometryMatrixTest::Matrix3fDivisionAssignOperator"_rfs, 
            "DivisionAssignOperator3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fDivisionAssignOperator),
            "GeometryMatrixTest::Matrix4fDivisionAssignOperator"_rfs, 
            "DivisionAssignOperator4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fScale),
            "GeometryMatrixTest::Matrix2fScale"_rfs, 
            "Scale2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fScale),
            "GeometryMatrixTest::Matrix3fScale"_rfs, 
            "Scale3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fScale),
            "&GeometryMatrixTest::Matrix4fScale"_rfs, 
            "Scale4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fDeterminants),
            "GeometryMatrixTest::Matrix2fDeterminants"_rfs, 
            "Determinants2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fDeterminants),
            "GeometryMatrixTest::Matrix3fDeterminants"_rfs, 
            "Determinants3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fDeterminants),
            "GeometryMatrixTest::Matrix4fDeterminants"_rfs, 
            "Determinants4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fInverse),
            "GeometryMatrixTest::Matrix2fInverse"_rfs, 
            "Inverse2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fInverse),
            "GeometryMatrixTest::Matrix3fInverse"_rfs, 
            "Inverse3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fInverse),
            "GeometryMatrixTest::Matrix4fInverse"_rfs, 
            "Inverse4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fLoadIdentity),
            "GeometryMatrixTest::Matrix2fLoadIdentity"_rfs, 
            "LoadIdentity2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fLoadIdentity),
            "GeometryMatrixTest::Matrix3fLoadIdentity"_rfs, 
            "LoadIdentity3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fLoadIdentity),
            "GeometryMatrixTest::Matrix4fLoadIdentity"_rfs,  
            "LoadIdentity4f"_rfs);

        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix2fLoadZero),
            "GeometryMatrixTest::Matrix2fLoadZero"_rfs,  "LoadZero2f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix3fLoadZero),
            "GeometryMatrixTest::Matrix3fLoadZero"_rfs,  "LoadZero3f"_rfs);
        AddTest(MakeDelegate(this,&GeometryMatrixTest::Matrix4fLoadZero),
            "GeometryMatrixTest::Matrix4fLoadZero"_rfs,  "LoadZero4f"_rfs);
    }

    Bool Matrix2fDefaultConstructor()
    {
        Matrix2f m2;
        return (m2.Value[0]==1.0 && m2.Value[2]==0.0 &&
                m2.Value[1]==0.0 && m2.Value[3]==1.0);
    }

    Bool Matrix3fDefaultConstructor()
    {
        Matrix3f m3;
        return (m3.Value[0]==1.0 && m3.Value[3]==0.0 && m3.Value[6]==0.0 &&
                m3.Value[1]==0.0 && m3.Value[4]==1.0 && m3.Value[7]==0.0 &&
                m3.Value[2]==0.0 && m3.Value[5]==0.0 && m3.Value[8]==1.0);
    }

    Bool Matrix4fDefaultConstructor()
    {
        Mat4f m4;
        return (m4.Value[0]==1.0 && m4.Value[4]==0.0 && m4.Value[8]==0.0 &&
                m4.Value[12]==0.0 && m4.Value[1]==0.0 && m4.Value[5]==1.0 &&
                m4.Value[9]==0.0 && m4.Value[13]==0.0 && m4.Value[2]==0.0 &&
                m4.Value[6]==0.0 && m4.Value[10]==1.0 && m4.Value[14]==0.0 &&
                m4.Value[3]==0.0 && m4.Value[7]==0.0 && m4.Value[11]==0.0 &&
                m4.Value[15]==1.0);
    }

    Bool Matrix2fCopyConstructor()
    {
        Matrix2f m2b;
        m2b.Value[0]=2.0; m2b.Value[2]=3.0;
        m2b.Value[1]=1.0; m2b.Value[3]=2.0;
        Matrix2f m2(m2b);
        return (m2.Value[0]==2.0 && m2.Value[2]==3.0 &&
                m2.Value[1]==1.0 && m2.Value[3]==2.0);
    }

    Bool Matrix3fCopyConstructor()
    {
        Matrix3f m3b;
        m3b.Value[0]=2.0; m3b.Value[3]=3.0; m3b.Value[6]=1.0;
        m3b.Value[1]=1.0; m3b.Value[4]=2.0; m3b.Value[7]=3.0;
        m3b.Value[2]=3.0; m3b.Value[5]=1.0; m3b.Value[8]=2.0;
        Matrix3f m3(m3b);
        return (m3.Value[0]==2.0 && m3.Value[3]==3.0 && m3.Value[6]==1.0 &&
                m3.Value[1]==1.0 && m3.Value[4]==2.0 && m3.Value[7]==3.0 &&
                m3.Value[2]==3.0 && m3.Value[5]==1.0 && m3.Value[8]==2.0);
    }

    Bool Matrix4fCopyConstructor()
    {
        Mat4f m4b;
        m4b.Value[0]=2.0; m4b.Value[4]=3.0; m4b.Value[ 8]=1.0; m4b.Value[12]=4.0;
        m4b.Value[1]=1.0; m4b.Value[5]=2.0; m4b.Value[ 9]=3.0; m4b.Value[13]=3.0;
        m4b.Value[2]=3.0; m4b.Value[6]=4.0; m4b.Value[10]=2.0; m4b.Value[14]=2.0;
        m4b.Value[3]=4.0; m4b.Value[7]=1.0; m4b.Value[11]=4.0; m4b.Value[15]=1.0;
        Mat4f m4(m4b);
        return (m4.Value[0]==2.0 && m4.Value[4]==3.0 && m4.Value[ 8]==1.0 &&
                m4.Value[12]==4.0 && m4.Value[1]==1.0 && m4.Value[5]==2.0 &&
                m4.Value[ 9]==3.0 && m4.Value[13]==3.0 && m4.Value[2]==3.0 &&
                m4.Value[6]==4.0 && m4.Value[10]==2.0 && m4.Value[14]==2.0 &&
                m4.Value[3]==4.0 && m4.Value[7]==1.0 && m4.Value[11]==4.0 &&
                m4.Value[15]==1.0);
    }

    Bool Matrix2fAssignOperator()
    {
        Matrix2f m2,m2b;
        m2b.Value[0]=2.0; m2b.Value[2]=3.0;
        m2b.Value[1]=1.0; m2b.Value[3]=2.0;
        m2=m2b;
        return (m2.Value[0]==2.0 && m2.Value[2]==3.0 &&
                m2.Value[1]==1.0 && m2.Value[3]==2.0);
    }

    Bool Matrix3fAssignOperator()
    {
        Matrix3f m3,m3b;
        m3b.Value[0]=2.0; m3b.Value[3]=3.0; m3b.Value[6]=1.0;
        m3b.Value[1]=1.0; m3b.Value[4]=2.0; m3b.Value[7]=3.0;
        m3b.Value[2]=3.0; m3b.Value[5]=1.0; m3b.Value[8]=2.0;
        m3=m3b;
        return (m3.Value[0]==2.0 && m3.Value[3]==3.0 && m3.Value[6]==1.0 &&
                m3.Value[1]==1.0 && m3.Value[4]==2.0 && m3.Value[7]==3.0 &&
                m3.Value[2]==3.0 && m3.Value[5]==1.0 && m3.Value[8]==2.0);
    }

    Bool Matrix4fAssignOperator()
    {
        Mat4f m4, m4b;
        m4b.Value[0]=2.0; m4b.Value[4]=3.0; m4b.Value[ 8]=1.0; m4b.Value[12]=4.0;
        m4b.Value[1]=1.0; m4b.Value[5]=2.0; m4b.Value[ 9]=3.0; m4b.Value[13]=3.0;
        m4b.Value[2]=3.0; m4b.Value[6]=4.0; m4b.Value[10]=2.0; m4b.Value[14]=2.0;
        m4b.Value[3]=4.0; m4b.Value[7]=1.0; m4b.Value[11]=4.0; m4b.Value[15]=1.0;
        m4=m4b;

        RF_Type::Bool result = (m4.Value[0] == 2.0 && m4.Value[4] == 3.0 && m4.Value[8] == 1.0 &&
            m4.Value[12] == 4.0 && m4.Value[1] == 1.0 && m4.Value[5] == 2.0 &&
            m4.Value[9] == 3.0 && m4.Value[13] == 3.0 && m4.Value[2] == 3.0 &&
            m4.Value[6] == 4.0 && m4.Value[10] == 2.0 && m4.Value[14] == 2.0 &&
            m4.Value[3] == 4.0 && m4.Value[7] == 1.0 && m4.Value[11] == 4.0 &&
            m4.Value[15] == 1.0);
        return result;
    }

    Bool Matrix2fGetRow()
    {
        Matrix2f m2;
        m2.Value[1]=2.0; m2.Value[2]=2.0;
        return (m2.GetRow(0)[0]==1.0 && m2.GetRow(0)[1]==2.0) &&
                (m2.GetRow(1)[0]==2.0 && m2.GetRow(1)[1]==1.0);
    }

    Bool Matrix3fGetRow()
    {
        Matrix3f m3;
        m3.Value[3]=2.0; m3.Value[1]=2.0; m3.Value[5]=2.0;
        return (m3.GetRow(0)[0]==1.0 && m3.GetRow(0)[1]==2.0 && m3.GetRow(0)[2]==0.0) &&
                (m3.GetRow(1)[0]==2.0 && m3.GetRow(1)[1]==1.0 && m3.GetRow(1)[2]==0.0) &&
                (m3.GetRow(2)[0]==0.0 && m3.GetRow(2)[1]==2.0 && m3.GetRow(2)[2]==1.0);
    }

    Bool Matrix4fGetRow()
    {
        Mat4f m4;
        m4.Value[11]=2.0; m4.Value[1]=2.0; m4.Value[6]=2.0; m4.Value[12]=2.0;
        return (m4.GetRow(0)[0]==1.0 && m4.GetRow(0)[1]==0.0 && m4.GetRow(0)[2]==0.0 && m4.GetRow(0)[3]==2.0) &&
                (m4.GetRow(1)[0]==2.0 && m4.GetRow(1)[1]==1.0 && m4.GetRow(1)[2]==0.0 && m4.GetRow(1)[3]==0.0) &&
                (m4.GetRow(2)[0]==0.0 && m4.GetRow(2)[1]==2.0 && m4.GetRow(2)[2]==1.0 && m4.GetRow(2)[3]==0.0) &&
                (m4.GetRow(3)[0]==0.0 && m4.GetRow(3)[1]==0.0 && m4.GetRow(3)[2]==2.0 && m4.GetRow(3)[3]==1.0);
    }

    Bool Matrix2fGetColumn()
    {
        Matrix2f m2;
        m2.Value[1]=2.0; m2.Value[2]=2.0;
        return (m2.GetColumn(0)[0]==1.0 && m2.GetColumn(0)[1]==2.0) &&
                (m2.GetColumn(1)[0]==2.0 && m2.GetColumn(1)[1]==1.0);
    }

    Bool Matrix3fGetColumn()
    {
        Matrix3f m3;
        m3.Value[3]=2.0; m3.Value[1]=2.0; m3.Value[5]=2.0;
        return (m3.GetColumn(0)[0]==1.0 && m3.GetColumn(0)[1]==2.0 && m3.GetColumn(0)[2]==0.0) &&
                (m3.GetColumn(1)[0]==2.0 && m3.GetColumn(1)[1]==1.0 && m3.GetColumn(1)[2]==2.0) &&
                (m3.GetColumn(2)[0]==0.0 && m3.GetColumn(2)[1]==0.0 && m3.GetColumn(2)[2]==1.0);
    }

    Bool Matrix4fGetColumn()
    {
        Mat4f m4;
        m4.Value[11]=2.0; m4.Value[1]=2.0; m4.Value[6]=2.0; m4.Value[12]=2.0;
        return (m4.GetColumn(0)[0]==1.0 && m4.GetColumn(0)[1]==2.0 && m4.GetColumn(0)[2]==0.0 && m4.GetColumn(0)[3]==0.0) &&
                (m4.GetColumn(1)[0]==0.0 && m4.GetColumn(1)[1]==1.0 && m4.GetColumn(1)[2]==2.0 && m4.GetColumn(1)[3]==0.0) &&
                (m4.GetColumn(2)[0]==0.0 && m4.GetColumn(2)[1]==0.0 && m4.GetColumn(2)[2]==1.0 && m4.GetColumn(2)[3]==2.0) &&
                (m4.GetColumn(3)[0]==2.0 && m4.GetColumn(3)[1]==0.0 && m4.GetColumn(3)[2]==0.0 && m4.GetColumn(3)[3]==1.0);
    }

    Bool Matrix2fSetColumn()
    {
        Matrix2f m2;
        m2.SetColumn(0,Vec2f(2.0,1.0));
        m2.SetColumn(1,Vec2f(3.0,2.0));
        return (m2.Value[0]==2.0 && m2.Value[2]==3.0 &&
                m2.Value[1]==1.0 && m2.Value[3]==2.0);
    }

    Bool Matrix3fSetColumn()
    {
        Matrix3f m3;
        m3.SetColumn(0,Vec3f(2.0,1.0,3.0));
        m3.SetColumn(1,Vec3f(3.0,2.0,1.0));
        m3.SetColumn(2,Vec3f(1.0,3.0,2.0));
        return (m3.Value[0]==2.0 && m3.Value[3]==3.0 && m3.Value[6]==1.0 &&
                m3.Value[1]==1.0 && m3.Value[4]==2.0 && m3.Value[7]==3.0 &&
                m3.Value[2]==3.0 && m3.Value[5]==1.0 && m3.Value[8]==2.0);
    }

    Bool Matrix4fSetColumn()
    {
        Mat4f m4;
        m4.SetColumn(0,Vec4f(2.0,1.0,3.0,4.0));
        m4.SetColumn(1,Vec4f(3.0,2.0,4.0,1.0));
        m4.SetColumn(2,Vec4f(1.0,3.0,2.0,4.0));
        m4.SetColumn(3,Vec4f(4.0,3.0,2.0,1.0));
        return (m4.Value[0]==2.0 && m4.Value[4]==3.0 && m4.Value[ 8]==1.0 &&
                m4.Value[12]==4.0 && m4.Value[1]==1.0 && m4.Value[5]==2.0 &&
                m4.Value[9]==3.0 && m4.Value[13]==3.0 && m4.Value[2]==3.0 &&
                m4.Value[6]==4.0 && m4.Value[10]==2.0 && m4.Value[14]==2.0 &&
                m4.Value[3]==4.0 && m4.Value[7]==1.0 && m4.Value[11]==4.0 &&
                m4.Value[15]==1.0);
    }

    Bool Matrix2fTranspose()
    {
        Matrix2f m2,m2b;
        m2.SetColumn(0,Vec2f(2.0,1.0));
        m2.SetColumn(1,Vec2f(3.0,2.0));
        Bool ret;
        ret=(m2.Value[0]==2.0 && m2.Value[2]==3.0 &&
                m2.Value[1]==1.0 && m2.Value[3]==2.0);
        m2b=m2.Transpose();
        return (m2b.Value[0]==2.0 && m2b.Value[2]==1.0 &&
                m2b.Value[1]==3.0 && m2b.Value[3]==2.0) && ret;
    }

    Bool Matrix3fTranspose()
    {
        Matrix3f m3,m3b;
        m3.SetColumn(0,Vec3f(2.0,1.0,3.0));
        m3.SetColumn(1,Vec3f(3.0,2.0,1.0));
        m3.SetColumn(2,Vec3f(1.0,3.0,2.0));
        Bool ret;
        ret=(m3.Value[0]==2.0 && m3.Value[3]==3.0 && m3.Value[6]==1.0 &&
                m3.Value[1]==1.0 && m3.Value[4]==2.0 && m3.Value[7]==3.0 &&
                m3.Value[2]==3.0 && m3.Value[5]==1.0 && m3.Value[8]==2.0);
        m3b=m3.Transpose();
        return (m3b.Value[0]==2.0 && m3b.Value[3]==1.0 && m3b.Value[6]==3.0 &&
                m3b.Value[1]==3.0 && m3b.Value[4]==2.0 && m3b.Value[7]==1.0 &&
                m3b.Value[2]==1.0 && m3b.Value[5]==3.0 && m3b.Value[8]==2.0) && ret;
    }

    Bool Matrix4fTranspose()
    {
        Mat4f m4, m4b;
        m4.SetColumn(0,Vec4f(2.0,1.0,3.0,4.0));
        m4.SetColumn(1,Vec4f(3.0,2.0,4.0,1.0));
        m4.SetColumn(2,Vec4f(1.0,3.0,2.0,4.0));
        m4.SetColumn(3,Vec4f(4.0,3.0,2.0,1.0));
        Bool ret;
        ret=(m4.Value[0]==2.0 && m4.Value[4]==3.0 && m4.Value[ 8]==1.0 &&
                m4.Value[12]==4.0 && m4.Value[1]==1.0 && m4.Value[5]==2.0 &&
                m4.Value[ 9]==3.0 && m4.Value[13]==3.0 && m4.Value[2]==3.0 &&
                m4.Value[6]==4.0 && m4.Value[10]==2.0 && m4.Value[14]==2.0 &&
                m4.Value[3]==4.0 && m4.Value[7]==1.0 && m4.Value[11]==4.0 &&
                m4.Value[15]==1.0);
        m4b=m4.Transpose();
        return (m4b.Value[0]==2.0 && m4b.Value[4]==1.0 && m4b.Value[ 8]==3.0 &&
                m4b.Value[12]==4.0 && m4b.Value[1]==3.0 && m4b.Value[5]==2.0 &&
                m4b.Value[ 9]==4.0 && m4b.Value[13]==1.0 && m4b.Value[2]==1.0 &&
                m4b.Value[6]==3.0 && m4b.Value[10]==2.0 && m4b.Value[14]==4.0 &&
                m4b.Value[3]==4.0 && m4b.Value[7]==3.0 && m4b.Value[11]==2.0 &&
                m4b.Value[15]==1.0) && ret;
    }

    Bool Matrix2fScale()
    {
        Matrix2f m2;
        m2.Scale(Vec2f(2.0,1.0));
        return (m2.Value[0]==2.0 && m2.Value[2]==0.0 &&
                m2.Value[1]==0.0 && m2.Value[3]==1.0);
    }

    Bool Matrix3fScale()
    {
        Matrix3f m3;
        m3.Scale(Vec3f(2.0,1.0,3.0));
        return (m3.Value[0]==2.0 && m3.Value[3]==0.0 && m3.Value[6]==0.0 &&
                m3.Value[1]==0.0 && m3.Value[4]==1.0 && m3.Value[7]==0.0 &&
                m3.Value[2]==0.0 && m3.Value[5]==0.0 && m3.Value[8]==3.0);
    }

    Bool Matrix4fScale()
    {
        Mat4f m4;
        m4.Scale(Vec4f(2.0,1.0,3.0,4.0));
        return (m4.Value[0]==2.0 && m4.Value[4]==0.0 && m4.Value[ 8]==0.0 &&
                m4.Value[12]==0.0 && m4.Value[1]==0.0 && m4.Value[5]==1.0 &&
                m4.Value[ 9]==0.0 && m4.Value[13]==0.0 && m4.Value[2]==0.0 &&
                m4.Value[6]==0.0 && m4.Value[10]==3.0 && m4.Value[14]==0.0 &&
                m4.Value[3]==0.0 && m4.Value[7]==0.0 && m4.Value[11]==0.0 &&
                m4.Value[15]==4.0);
    }

    Bool Matrix2fFunctionOperator()
    {
        Matrix2f m2;
        return (m2(0,0)==1.0 && m2(1,0)==0.0 &&
                m2(0,1)==0.0 && m2(1,1)==1.0);
    }

    Bool Matrix3fFunctionOperator()
    {
        Matrix3f m3;
        return (m3(0,0)==1.0 && m3(1,0)==0.0 && m3(2,0)==0.0 &&
                m3(0,1)==0.0 && m3(1,1)==1.0 && m3(2,1)==0.0 &&
                m3(0,2)==0.0 && m3(1,2)==0.0 && m3(2,2)==1.0);
    }

    Bool Matrix4fFunctionOperator()
    {
        Mat4f m4;
        return (m4(0,0)==1.0 && m4(1,0)==0.0 && m4(2,0)==0.0 && m4(3,0)==0.0 &&
                m4(0,1)==0.0 && m4(1,1)==1.0 && m4(2,1)==0.0 && m4(3,1)==0.0 &&
                m4(0,2)==0.0 && m4(1,2)==0.0 && m4(2,2)==1.0 && m4(3,2)==0.0 &&
                m4(0,3)==0.0 && m4(1,3)==0.0 && m4(2,3)==0.0 && m4(3,3)==1.0);
    }

    Bool Matrix2fArrayOperator()
    {
        Matrix2f m2;
        return (m2[0]==1.0 && m2[2]==0.0 &&
                m2[1]==0.0 && m2[3]==1.0);
    }

    Bool Matrix3fArrayOperator()
    {
        Matrix3f m3;
        return (m3[0]==1.0 && m3[3]==0.0 && m3[6]==0.0 &&
                m3[1]==0.0 && m3[4]==1.0 && m3[7]==0.0 &&
                m3[2]==0.0 && m3[5]==0.0 && m3[8]==1.0);
    }

    Bool Matrix4fArrayOperator()
    {
        Mat4f m4;
        return (m4[0]==1.0 && m4[4]==0.0 && m4[ 8]==0.0 && m4[12]==0.0 &&
                m4[1]==0.0 && m4[5]==1.0 && m4[ 9]==0.0 && m4[13]==0.0 &&
                m4[2]==0.0 && m4[6]==0.0 && m4[10]==1.0 && m4[14]==0.0 &&
                m4[3]==0.0 && m4[7]==0.0 && m4[11]==0.0 && m4[15]==1.0);
    }

    Bool Matrix2fMultiplicationOperator()
    {
        Matrix2f m2,m2b;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        m2b=m2;
        m2=m2*m2b;
        return (m2.Value[0]==7.0 && m2.Value[2]==4.0 &&
                m2.Value[1]==12.0 && m2.Value[3]==7.0);
    }

    Bool Matrix3fMultiplicationOperator()
    {
        Matrix3f m3,m3b;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,1.0,2.0));
        m3b=m3;
        m3=m3*m3b;

        RF_Type::Bool result = (m3.Value[0] == 10.0 && m3.Value[3] == 13.0 && m3.Value[6] == 13.0 &&
            m3.Value[1] == 13.0 && m3.Value[4] == 10.0 && m3.Value[7] == 13.0 &&
            m3.Value[2] == 13.0 && m3.Value[5] == 13.0 && m3.Value[8] == 10.0);
        return result;
    }

    Bool Matrix4fMultiplicationOperator()
    {
        Mat4f m4, m4b;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        m4b=m4;
        m4=m4*m4b;
        return (m4.Value[0]==26.0 && m4.Value[4]==25.0 && m4.Value[ 8]==24.0 &&
                m4.Value[12]==25.0 && m4.Value[1]==20.0 && m4.Value[5]==22.0 &&
                m4.Value[ 9]==27.0 && m4.Value[13]==31.0 && m4.Value[2]==29.0 &&
                m4.Value[6]==25.0 && m4.Value[10]==27.0 && m4.Value[14]==19.0 &&
                m4.Value[3]==23.0 && m4.Value[7]==19.0 && m4.Value[11]==30.0 &&
                m4.Value[15]==28.0);
    }

    Bool Matrix2fDivisionOperator()
    {
        Matrix2f m2;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        m2=m2/0.5;
        return (m2.Value[0]==4.0 && m2.Value[2]==2.0 &&
                m2.Value[1]==6.0 && m2.Value[3]==4.0);
    }

    Bool Matrix3fDivisionOperator()
    {
        Matrix3f m3;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,1.0,2.0));
        m3=m3/0.5;
        return (m3.Value[0]==4.0 && m3.Value[3]==2.0 && m3.Value[6]==6.0 &&
                m3.Value[1]==6.0 && m3.Value[4]==4.0 && m3.Value[7]==2.0 &&
                m3.Value[2]==2.0 && m3.Value[5]==6.0 && m3.Value[8]==4.0);
    }

    Bool Matrix4fDivisionOperator()
    {
        Mat4f m4;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        m4=m4/0.5;
        return (m4.Value[0]==4.0 && m4.Value[4]==2.0 && m4.Value[8]==6.0 &&
                m4.Value[12]==8.0 && m4.Value[1]==6.0 && m4.Value[5]==4.0 &&
                m4.Value[9]==8.0 && m4.Value[13]==2.0 && m4.Value[2]==2.0 &&
                m4.Value[6]==6.0 && m4.Value[10]==4.0 && m4.Value[14]==8.0 &&
                m4.Value[3]==8.0 && m4.Value[7]==6.0 && m4.Value[11]==4.0 &&
                m4.Value[15]==2.0);
    }

    Bool Matrix2fMultiplicationOperatorVector()
    {
        Matrix2f m2;
        Vec2f v;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        v=m2*Vec2f(0.5,0.25);
        return (v.Value[0]==1.25 && v.Value[1]==2.0);
    }

    Bool Matrix3fMultiplicationOperatorVector()
    {
        Matrix3f m3;
        Vec3f v;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,1.0,2.0));
        v=m3*Vec3f(0.5,0.25,0.125);
        return (v.Value[0]==1.625 && v.Value[1]==2.125 && v.Value[2]==1.5);
    }

    Bool Matrix4fMultiplicationOperatorVector()
    {
        Mat4f m4;
        Vec4f v;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        v=m4*Vec4f(0.5,0.25,0.125,0.0625);
        return (v.Value[0]==1.875 && v.Value[1]==2.5625 &&
                v.Value[2]==1.75 &&	v.Value[3]==3.0625);
    }

    Bool Matrix2fMultiplicationAssignOperator()
    {
        Matrix2f m2,m2b;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        m2b=m2;
        m2*=m2b;
        return (m2.Value[0]==7.0 && m2.Value[2]==4.0 &&
                m2.Value[1]==12.0 && m2.Value[3]==7.0);
    }

    Bool Matrix3fMultiplicationAssignOperator()
    {
        Matrix3f m3,m3b;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,1.0,2.0));
        m3b=m3;
        m3*=m3b;
        return (m3.Value[0]==10.0 && m3.Value[3]==13.0 && m3.Value[6]==13.0 &&
                m3.Value[1]==13.0 && m3.Value[4]==10.0 && m3.Value[7]==13.0 &&
                m3.Value[2]==13.0 && m3.Value[5]==13.0 && m3.Value[8]==10.0);
    }

    Bool Matrix4fMultiplicationAssignOperator()
    {
        Mat4f m4, m4b;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        m4b=m4;
        m4*=m4b;
        return (m4.Value[0]==26.0 && m4.Value[4]==25.0 && m4.Value[ 8]==24.0 &&
                m4.Value[12]==25.0 && m4.Value[1]==20.0 && m4.Value[5]==22.0 &&
                m4.Value[ 9]==27.0 && m4.Value[13]==31.0 && m4.Value[2]==29.0 &&
                m4.Value[6]==25.0 && m4.Value[10]==27.0 && m4.Value[14]==19.0 &&
                m4.Value[3]==23.0 && m4.Value[7]==19.0 && m4.Value[11]==30.0 &&
                m4.Value[15]==28.0);
    }

    Bool Matrix2fDivisionAssignOperator()
    {
        Matrix2f m2;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        m2/=0.5;
        return (m2.Value[0]==4.0 && m2.Value[2]==2.0 &&
                m2.Value[1]==6.0 && m2.Value[3]==4.0);
    }

    Bool Matrix3fDivisionAssignOperator()
    {
        Matrix3f m3;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,1.0,2.0));
        m3/=0.5;
        return (m3.Value[0]==4.0 && m3.Value[3]==2.0 && m3.Value[6]==6.0 &&
                m3.Value[1]==6.0 && m3.Value[4]==4.0 && m3.Value[7]==2.0 &&
                m3.Value[2]==2.0 && m3.Value[5]==6.0 && m3.Value[8]==4.0);
    }

    Bool Matrix4fDivisionAssignOperator()
    {
        Mat4f m4;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        m4/=0.5;
        return (m4.Value[0]==4.0 && m4.Value[4]==2.0 && m4.Value[8]==6.0 &&
                m4.Value[12]==8.0 && m4.Value[1]==6.0 && m4.Value[5]==4.0 &&
                m4.Value[9]==8.0 && m4.Value[13]==2.0 && m4.Value[2]==2.0 &&
                m4.Value[6]==6.0 && m4.Value[10]==4.0 && m4.Value[14]==8.0 &&
                m4.Value[3]==8.0 && m4.Value[7]==6.0 && m4.Value[11]==4.0 &&
                m4.Value[15]==2.0);
    }

    Bool Matrix2fDeterminants()
    {
        Matrix2f m2;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        return m2.Determinants()==1.0;
    }

    Bool Matrix3fDeterminants()
    {
        Matrix3f m3;
        m3.SetColumn(0,Vec3f(2.0,3.0,1.0));
        m3.SetColumn(1,Vec3f(1.0,2.0,3.0));
        m3.SetColumn(2,Vec3f(3.0,4.0,2.0));
        return m3.Determinants()==3.0;
    }

    Bool Matrix4fDeterminants()
    {
        Mat4f m4;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        return m4.Determinants()==90.0;
    }

    Bool Matrix2fInverse()
    {
        Matrix2f m2;
        m2.SetColumn(0,Vec2f(2.0,3.0));
        m2.SetColumn(1,Vec2f(1.0,2.0));
        Matrix2f m2inv;
        m2inv=m2.Inverse();
        return m2*m2inv==Matrix2f();
    }

    Bool Matrix3fInverse()
    {
        Matrix3f m3;
        m3.SetColumn(0,Vec3f(3.0,2.0,1.0));
        m3.SetColumn(1,Vec3f(5.0,4.0,2.0));
        m3.SetColumn(2,Vec3f(1.0,5.0,2.0));
        Matrix3f m3inv;
        m3inv=m3.Inverse();
        return m3*m3inv==Matrix3f();
    }

    Bool Matrix4fInverse()
    {
        Mat4f m4;
        m4.SetColumn(0,Vec4f(2.0,3.0,1.0,4.0));
        m4.SetColumn(1,Vec4f(1.0,2.0,3.0,3.0));
        m4.SetColumn(2,Vec4f(3.0,4.0,2.0,2.0));
        m4.SetColumn(3,Vec4f(4.0,1.0,4.0,1.0));
        Mat4f m4inv;
        m4inv=m4.Inverse();
        return m4*m4inv == Mat4f();
    }

    Bool Matrix2fLoadIdentity()
    {
        Matrix2f m2;
        return (m2.Value[0]==1.0 && m2.Value[2]==0.0 &&
            m2.Value[1]==0.0 && m2.Value[3]==1.0);
    }

    Bool Matrix3fLoadIdentity()
    {
        Matrix3f m3;
        return (m3.Value[0]==1.0 && m3.Value[3]==0.0 && m3.Value[6]==0.0 &&
            m3.Value[1]==0.0 && m3.Value[4]==1.0 && m3.Value[7]==0.0 &&
            m3.Value[2]==0.0 && m3.Value[5]==0.0 && m3.Value[8]==1.0);
    }

    Bool Matrix4fLoadIdentity()
    {
        Mat4f m4;
        return (m4.Value[0]==1.0 && m4.Value[4]==0.0 && m4.Value[8]==0.0 &&
            m4.Value[12]==0.0 && m4.Value[1]==0.0 && m4.Value[5]==1.0 &&
            m4.Value[9]==0.0 && m4.Value[13]==0.0 && m4.Value[2]==0.0 &&
            m4.Value[6]==0.0 && m4.Value[10]==1.0 && m4.Value[14]==0.0 &&
            m4.Value[3]==0.0 && m4.Value[7]==0.0 && m4.Value[11]==0.0 &&
            m4.Value[15]==1.0);
    }

    Bool Matrix2fLoadZero()
    {
        Matrix2f m2;
        m2.LoadZero();
        return (m2.Value[0]==0.0 && m2.Value[2]==0.0 &&
                m2.Value[1]==0.0 && m2.Value[3]==0.0);
    }

    Bool Matrix3fLoadZero()
    {
        Matrix3f m3;
        m3.LoadZero();
        return (m3.Value[0]==0.0 && m3.Value[3]==0.0 && m3.Value[6]==0.0 &&
                m3.Value[1]==0.0 && m3.Value[4]==0.0 && m3.Value[7]==0.0 &&
                m3.Value[2]==0.0 && m3.Value[5]==0.0 && m3.Value[8]==0.0);
    }

    Bool Matrix4fLoadZero()
    {
        Mat4f m4;
        m4.LoadZero();
        return (m4.Value[0]==0.0 && m4.Value[4]==0.0 && m4.Value[8]==0.0 &&
                m4.Value[12]==0.0 && m4.Value[1]==0.0 && m4.Value[5]==0.0 &&
                m4.Value[9]==0.0 && m4.Value[13]==0.0 && m4.Value[2]==0.0 &&
                m4.Value[6]==0.0 && m4.Value[10]==0.0 && m4.Value[14]==0.0 &&
                m4.Value[3]==0.0 && m4.Value[7]==0.0 && m4.Value[11]==0.0 &&
                m4.Value[15]==0.0);
    }
};

GeometryMatrixTest MatrixTest;