/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.hxx !!!
*
*/
#ifndef RF_MATH_GEOMETRY_@GuardName@_HPP
#define RF_MATH_GEOMETRY_@GuardName@_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework::Math::Geometry {

class @ClassName@
{
public:
    static const @ClassName@ Identity;

    @ClassName@();
    @ClassName@(const @ClassName@& Copy);
    @ClassName@(const @ClassType@ Alpha,const Vector<@ClassType@,3>& Direction);
    @ClassName@(const @ClassType@ w,const @ClassType@ X,const @ClassType@ Y,const @ClassType@ Z);
    @ClassName@(const Vector<@ClassType@,3>& Direction);
    @ClassName@(const Matrix<@ClassType@,3,3>& RotationMatrix);
    @ClassName@(const @ClassType@ Roll, const @ClassType@ Pitch, const @ClassType@ Yaw);

    /** @brief Addition of two @ClassName@.
    *
    */
    @ClassName@ operator+(const @ClassName@& Other);

    /** @brief Subtraction of two @ClassName@.
    *
    */
    @ClassName@ operator-(const @ClassName@& Other);

    /** @brief Multiply two @ClassName@.
    *
    */
    @ClassName@ operator*(const @ClassName@& Other);

    @ClassName@& SetIdentity();
    @ClassName@& Invert();

    /** @brief Conjugate of @ClassName@.
    *
    */
    @ClassName@& Conjugate();

    /** @brief Normalize the @ClassName@.
    *
    * This method will calculate the norm and divide every element by it.
    */
    @ClassName@& Normalize();

    @ClassName@ CrossProduct(const @ClassName@& Other);
    @ClassName@ Slerp(const @ClassName@& Other, @ClassType@ t);

    /** @brief Inverse of @ClassName@.
    *
    */
    @ClassName@ Inverse()const;

    @ClassName@ Exponential();
    RF_Type::Bool IsInfinite();
    RF_Type::Bool IsNaN();
    @ClassName@ LengthAsQuat();
    @ClassName@ SquareLengthAsQuat();
    void ToAxisAngle(Vector<@ClassType@,3>& Axis, @ClassType@& Angle);
    @ClassType@ SquareLength();
    Vector<@ClassType@,3> GetAxis();
    @ClassType@ GetAngle();
    @ClassType@ Length();
    @ClassType@ DotProduct(const @ClassName@& Other);

    Matrix<@ClassType@,3,3> AsRotationMatrix();
    Matrix<@ClassType@,4,4> AsMatrix()const;

    /** @brief Division two @ClassName@.
    *
    */    
    @ClassName@ operator/(const @ClassName@& Other);

    @ClassName@& operator+=(const @ClassName@& Other);
    @ClassName@& operator-=(const @ClassName@& Other);
    
    /** @brief Apply the rotation on a vector.
    *
    */
    Vector<@ClassType@, 4> operator*(const Vector<@ClassType@, 4>& Vec);

    Vector<@ClassType@, 3> operator*(const Vector<@ClassType@, 3>& Vec);
    RF_Type::Bool operator==(const @ClassName@& Other);
    RF_Type::Bool operator!=(const @ClassName@& Other);
    @ClassType@& operator[](const RF_Type::UInt32 Index);
    const @ClassType@ operator[](const RF_Type::UInt32 Index)const;
    @ClassName@& operator*=(const @ClassName@& Other);
    @ClassName@& operator/=(const @ClassName@& Other);
    @ClassName@& operator=(const @ClassName@& Copy);
protected:
    Vector<@ClassType@,4> m_Vec;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_@GuardName@_HPP
