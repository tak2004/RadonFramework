#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/ProjectionMatrix.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Math/Geometry/Size2D.hpp"
#include "RadonFramework/Math/Math.hpp"
#include <math.h>

using namespace RadonFramework::Math::Geometry;

void ProjectionMatrix::SetDefaultProjectionMatrix()
{
  for (int i=0;i<16;i++)
    m_ProjectionMatrix[i]=0.0f;
  float f=1.0f/tan(m_FieldOfView/2.0f);
  float neg_depth=m_Near-m_Far;
  m_ProjectionMatrix[0]=f/m_AspectRatio;
  m_ProjectionMatrix[5]=f;
  m_ProjectionMatrix[10]=(m_Far+m_Near)/neg_depth;
  m_ProjectionMatrix[11]=-1.0f;
  m_ProjectionMatrix[14]=(2.0f*m_Far*m_Near)/neg_depth;
}

void ProjectionMatrix::SetDefaultOrthoMatrix()
{
  for (int i=0;i<16;i++)
    m_OrthoMatrix[i]=0.0f;
  float right=(float) m_Width-m_Left;
  float bottom=(float) m_Height-m_Top;
  float left=(float) m_Left;
  float top=(float) m_Top;
  m_OrthoMatrix[0]=2.0f/(right-left);
  m_OrthoMatrix[5]=2.0f/(top-bottom);
  m_OrthoMatrix[10]=-2.0f/(m_Far-m_Near);
  m_OrthoMatrix[12]=-(right+left)/(right-left);
  m_OrthoMatrix[13]=-(top+bottom)/(top-bottom);
  m_OrthoMatrix[14]=-(m_Far+m_Near)/(m_Far-m_Near);
  m_OrthoMatrix[15]=1.0f;
}

ProjectionMatrix::ProjectionMatrix()
{
  m_FieldOfView=45.0f;
  m_Width=640;
  m_Height=480;
  m_AspectRatio=(float)m_Width/(float)m_Height;
  m_Far=100.0f;
  m_Near=0.1f;
  m_Left=0;
  m_Top=0;
  SetDefaultProjectionMatrix();
  SetDefaultOrthoMatrix();
}

void ProjectionMatrix::SetPosition(const Point2D<> &Position)
{
  m_Left=Position.X;
  m_Top=Position.Y;

  float r=(float) m_Width-m_Left;
  float b=(float) m_Height-m_Top;
  float l=(float) m_Left;
  float t=(float) m_Top;
  m_OrthoMatrix[0]=2.0f/(r-l);
  m_OrthoMatrix[5]=2.0f/(t-b);
  m_OrthoMatrix[12]=-(r+l)/(r-l);
  m_OrthoMatrix[13]=-(t+b)/(t-b);
}

void ProjectionMatrix::SetSize(const Size2D<> &size)
{
  m_Width=size.Width;
  m_Height=size.Height;

  m_AspectRatio=(float)m_Width/(float)m_Height;
  float f=1.0f/tan(m_FieldOfView/2.0f);
  m_ProjectionMatrix[0]=f/m_AspectRatio;

  float r=(float) m_Width-m_Left;
  float b=(float) m_Height-m_Top;
  float l=(float) m_Left;
  float t=(float) m_Top;
  m_OrthoMatrix[0]=2.0f/(r-l);
  m_OrthoMatrix[5]=2.0f/(t-b);
  m_OrthoMatrix[12]=-(r+l)/(r-l);
  m_OrthoMatrix[13]=-(t+b)/(t-b);
}

Size2D<> ProjectionMatrix::GetSize()
{
  return Size2D<>(m_Width,m_Height);
}

float ProjectionMatrix::FieldOfView()
{
  return m_FieldOfView;
}

void ProjectionMatrix::FieldOfView(const float FOV)
{
  m_FieldOfView=FOV;

  float f=1.0f/tan(m_FieldOfView/2.0f);
  m_ProjectionMatrix[0]=f/m_AspectRatio;
  m_ProjectionMatrix[5]=f;
}

float ProjectionMatrix::Far()
{
  return m_Far;
}

void ProjectionMatrix::Far(const float Far)
{
  m_Far=Far;

  m_ProjectionMatrix[10]=(m_Far+m_Near)/(m_Near-m_Far);
  m_ProjectionMatrix[14]=(2*m_Far*m_Near)/(m_Near-m_Far);
  m_OrthoMatrix[10]=-2.0f/(m_Far-m_Near);
  m_OrthoMatrix[14]=-(m_Far+m_Near)/(m_Far-m_Near);
}

float ProjectionMatrix::Near()
{
  return m_Near;
}

void ProjectionMatrix::Near(const float Near)
{
  m_Near=Near;

  m_ProjectionMatrix[10]=(m_Far+m_Near)/(m_Near-m_Far);
  m_ProjectionMatrix[14]=(2*m_Far*m_Near)/(m_Near-m_Far);
  m_OrthoMatrix[10]=-2.0f/(m_Far-m_Near);
  m_OrthoMatrix[14]=-(m_Far+m_Near)/(m_Far-m_Near);
}

const Mat4f& ProjectionMatrix::GetMatrix(const Viewtype::Type Type)
{
  switch (Type)
  {
    case Viewtype::View2D:return m_OrthoMatrix;
    case Viewtype::View3D:return m_ProjectionMatrix;
    default:return m_ProjectionMatrix;
  }
}
