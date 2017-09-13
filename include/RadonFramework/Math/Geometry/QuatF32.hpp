/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.hxx !!!
*
*/
#ifndef RF_MATH_GEOMETRY_QUATF32_HPP
#define RF_MATH_GEOMETRY_QUATF32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework::Math::Geometry {

class QuatF32
{
public:
    static const QuatF32 Identity;

    QuatF32();
    QuatF32(const QuatF32& Copy);
    QuatF32(const RF_Type::Float32 Alpha,const Vector<RF_Type::Float32,3>& Direction);
    QuatF32(const RF_Type::Float32 w,const RF_Type::Float32 X,const RF_Type::Float32 Y,const RF_Type::Float32 Z);
    QuatF32(const Vector<RF_Type::Float32,3>& Direction);
    QuatF32(const Matrix<RF_Type::Float32,3,3>& RotationMatrix);
    QuatF32(const RF_Type::Float32 Roll, const RF_Type::Float32 Pitch, const RF_Type::Float32 Yaw);

    /** @brief Addition of two QuatF32.
    *
    */
    QuatF32 operator+(const QuatF32& Other);

    /** @brief Subtraction of two QuatF32.
    *
    */
    QuatF32 operator-(const QuatF32& Other);

    /** @brief Multiply two QuatF32.
    *
    */
    QuatF32 operator*(const QuatF32& Other);

    QuatF32& SetIdentity();
    QuatF32& Invert();

    /** @brief Conjugate of QuatF32.
    *
    */
    QuatF32& Conjugate();

    /** @brief Normalize the QuatF32.
    *
    * This method will calculate the norm and divide every element by it.
    */
    QuatF32& Normalize();

    QuatF32 CrossProduct(const QuatF32& Other);
    QuatF32 Slerp(const QuatF32& Other, RF_Type::Float32 t);

    /** @brief Inverse of QuatF32.
    *
    */
    QuatF32 Inverse()const;

    QuatF32 Exponential();
    RF_Type::Bool IsInfinite();
    RF_Type::Bool IsNaN();
    QuatF32 LengthAsQuat();
    QuatF32 SquareLengthAsQuat();
    void ToAxisAngle(Vector<RF_Type::Float32,3>& Axis, RF_Type::Float32& Angle);
    RF_Type::Float32 SquareLength();
    Vector<RF_Type::Float32,3> GetAxis();
    RF_Type::Float32 GetAngle();
    RF_Type::Float32 Length();
    RF_Type::Float32 DotProduct(const QuatF32& Other);

    Matrix<RF_Type::Float32,3,3> AsRotationMatrix();
    Matrix<RF_Type::Float32,4,4> AsMatrix()const;

    /** @brief Division two QuatF32.
    *
    */    
    QuatF32 operator/(const QuatF32& Other);

    QuatF32& operator+=(const QuatF32& Other);
    QuatF32& operator-=(const QuatF32& Other);
    
    /** @brief Apply the rotation on a vector.
    *
    */
    Vector<RF_Type::Float32, 4> operator*(const Vector<RF_Type::Float32, 4>& Vec);

    Vector<RF_Type::Float32, 3> operator*(const Vector<RF_Type::Float32, 3>& Vec);
    RF_Type::Bool operator==(const QuatF32& Other);
    RF_Type::Bool operator!=(const QuatF32& Other);
    RF_Type::Float32& operator[](const RF_Type::UInt32 Index);
    const RF_Type::Float32 operator[](const RF_Type::UInt32 Index)const;
    QuatF32& operator*=(const QuatF32& Other);
    QuatF32& operator/=(const QuatF32& Other);
    QuatF32& operator=(const QuatF32& Copy);
protected:
    Vector<RF_Type::Float32,4> m_Vec;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_QUATF32_HPP
