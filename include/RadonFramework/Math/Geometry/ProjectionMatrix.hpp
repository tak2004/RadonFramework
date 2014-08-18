#ifndef RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
#define RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {
            
namespace Viewtype
{
    enum Type
    {
        View2D,
        View3D
    };
}

class ProjectionMatrix
{
public:
    ProjectionMatrix();
    void SetPosition(const Point2D<> &Position);
    void SetSize(const Size2D<> &size);
    Size2D<> GetSize();
    float FieldOfView();
    void FieldOfView(const float FOV);
    float Far();
    void Far(const float Far);
    float Near();
    void Near(const float Near);
    const Mat4f& GetMatrix(const Viewtype::Type Type);
protected:
    Mat4f m_ProjectionMatrix;
    Mat4f m_OrthoMatrix;
    float m_FieldOfView;
    float m_Far;
    float m_Near;
    float m_AspectRatio;
    void SetDefaultProjectionMatrix();
    void SetDefaultOrthoMatrix();
    unsigned int m_Width, m_Height;
    int m_Left, m_Top;
};
        
} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
