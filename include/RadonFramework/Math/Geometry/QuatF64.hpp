/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.hxx !!!
*
*/
#ifndef RF_MATH_GEOMETRY_QUATF64_HPP
#define RF_MATH_GEOMETRY_QUATF64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework::Math::Geometry {

class QuatF64
{
public:
    static const QuatF64 Identity;

    QuatF64();
    QuatF64(const QuatF64& Copy);
    QuatF64(const RF_Type::Float64 Alpha,const Vector<RF_Type::Float64,3>& Direction);
    QuatF64(const RF_Type::Float64 w,const RF_Type::Float64 X,const RF_Type::Float64 Y,const RF_Type::Float64 Z);
    QuatF64(const Vector<RF_Type::Float64,3>& Direction);
    QuatF64(const Matrix<RF_Type::Float64,3,3>& RotationMatrix);
    QuatF64(const RF_Type::Float64 Roll, const RF_Type::Float64 Pitch, const RF_Type::Float64 Yaw);

    /** @brief Addition of two QuatF64.
    *
    */
    QuatF64 operator+(const QuatF64& Other);

    /** @brief Subtraction of two QuatF64.
    *
    */
    QuatF64 operator-(const QuatF64& Other);

    /** @brief Multiply two QuatF64.
    *
    */
    QuatF64 operator*(const QuatF64& Other);

    QuatF64& SetIdentity();
    QuatF64& Invert();

    /** @brief Conjugate of QuatF64.
    *
    */
    QuatF64& Conjugate();

    /** @brief Normalize the QuatF64.
    *
    * This method will calculate the norm and divide every element by it.
    */
    QuatF64& Normalize();

    QuatF64 CrossProduct(const QuatF64& Other);
    QuatF64 Slerp(const QuatF64& Other, RF_Type::Float64 t);

    /** @brief Inverse of QuatF64.
    *
    */
    QuatF64 Inverse()const;

    QuatF64 Exponential();
    RF_Type::Bool IsInfinite();
    RF_Type::Bool IsNaN();
    QuatF64 LengthAsQuat();
    QuatF64 SquareLengthAsQuat();
    void ToAxisAngle(Vector<RF_Type::Float64,3>& Axis, RF_Type::Float64& Angle);
    RF_Type::Float64 SquareLength();
    Vector<RF_Type::Float64,3> GetAxis();
    RF_Type::Float64 GetAngle();
    RF_Type::Float64 Length();
    RF_Type::Float64 DotProduct(const QuatF64& Other);

    Matrix<RF_Type::Float64,3,3> AsRotationMatrix();
    Matrix<RF_Type::Float64,4,4> AsMatrix()const;

    /** @brief Division two QuatF64.
    *
    */    
    QuatF64 operator/(const QuatF64& Other);

    QuatF64& operator+=(const QuatF64& Other);
    QuatF64& operator-=(const QuatF64& Other);
    
    /** @brief Apply the rotation on a vector.
    *
    */
    Vector<RF_Type::Float64, 4> operator*(const Vector<RF_Type::Float64, 4>& Vec);

    Vector<RF_Type::Float64, 3> operator*(const Vector<RF_Type::Float64, 3>& Vec);
    RF_Type::Bool operator==(const QuatF64& Other);
    RF_Type::Bool operator!=(const QuatF64& Other);
    RF_Type::Float64& operator[](const RF_Type::UInt32 Index);
    const RF_Type::Float64 operator[](const RF_Type::UInt32 Index)const;
    QuatF64& operator*=(const QuatF64& Other);
    QuatF64& operator/=(const QuatF64& Other);
    QuatF64& operator=(const QuatF64& Copy);
protected:
    Vector<RF_Type::Float64,4> m_Vec;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_QUATF64_HPP
