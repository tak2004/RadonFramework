#ifndef RF_DRAWING_CAMERA_HPP
#define RF_DRAWING_CAMERA_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/Quaternion.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        class Camera
        {
            public:
                Camera();
                ~Camera();
                void MoveVertical(RF_Type::Float32 Value);
                void MoveHorizontal(RF_Type::Float32 Value);
                void RotateX(RF_Type::Float32 Value);
                void RotateY(RF_Type::Float32 Value);
                void Move(RF_Type::Float32 Value);
                Math::Geometry::Matrix4f GetMatrix();
            protected:
                Math::Geometry::Quaternion<RF_Type::Float32> m_Quat;
                Math::Geometry::Vec4f m_Position;
                Math::Geometry::Vec3f m_Up;
                Math::Geometry::Vec3f m_Front;
                Math::Geometry::Vec3f m_Right;
        };
    }
}

#endif // RF_DRAWING_CAMERA_HPP
