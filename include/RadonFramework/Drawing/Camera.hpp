#ifndef RF_DRAWING_CAMERA_HPP
#define RF_DRAWING_CAMERA_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/QuatF32.hpp>

namespace RadonFramework::Drawing
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
  RF_Geo::Mat4f GetMatrix() const;

protected:
  RF_Geo::QuatF32 m_Quat;
  RF_Geo::Vec4f m_Position;
  RF_Geo::Vec3f m_Up;
  RF_Geo::Vec3f m_Front;
  RF_Geo::Vec3f m_Right;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_CAMERA_HPP
