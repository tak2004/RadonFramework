#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Canvas3D.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceLocator.hpp"
#include "RadonFramework/Drawing/Forms/AbstractWindow.hpp"
#include "RadonFramework/Drawing/Forms/Form.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Math/Geometry/Size2D.hpp"
#include "RadonFramework/Math/Geometry/Rectangle.hpp"
#include "RadonFramework/Drawing/AbstractCanvas.hpp"
#include "RadonFramework/System/Threading/Mutex.hpp"

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Forms;
using namespace RadonFramework;

Canvas3D::Canvas3D(Control* Parent)
{
  Parent->Controls.Add(this);//add control as child
  m_Backend=Canvas3DServiceLocator::Default().CreateCanvas3D();
  AbstractWindow* window=static_cast<Form*>(Root())->Backend();
  m_Backend->SetWindowInfos(window);
  m_Backend->Generate();
  Draw2D.SetMeshGenerator(m_Backend->GetMeshGenerator2D());
}

void Canvas3D::Resize(const RF_Geo::Size2D<>& Value)
{
  Math::Geometry::Rectangle<> rec(Point2D<>(0,0),Point2D<>(Value.Width,Value.Height));
  m_Backend->UpdateRectangle(rec);
}

void Canvas3D::Clear()
{
  m_Backend->Clear();
}

void Canvas3D::SwapBuffer()
{
  m_Backend->SwapBuffer();
}

Mat4f& Canvas3D::TexturecoordMatrix()
{
  return m_Backend->TexturecoordMatrix();
}

const GraphicDriverInformation& Canvas3D::GetGraphicDriverInformation()
{
  return m_Backend->GetGraphicDriverInformation();
}

AbstractCanvas const* Canvas3D::Backend()const
{
    return m_Backend;
}

void Canvas3D::MakeCurrent()
{
    m_Backend->MakeCurrent();
}

System::Threading::Mutex& Canvas3D::GetRenderLock()
{
    return m_Backend->RenderLock();
}