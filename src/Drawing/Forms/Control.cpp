#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/IO/Log.hpp>

using namespace RadonFramework::Collections;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

void ControlCollection::Add(Control *Obj)
{
  Obj->Parent(m_Parent);
  m_List.AddLast(Obj);
}

Control* ControlCollection::Get(const Size Index)
{
    Assert(Index < m_List.Size(), "Index out of bounds.");

    List<Control*>::Iterator it=m_List.Begin();
    for (Size i=0; i<Index; i++)
        ++it;

    return *it;
}

Size ControlCollection::Count()
{
  return m_List.Size();
}

List<Control*>::Iterator ControlCollection::Begin()
{
  return m_List.Begin();
}

List<Control*>::Iterator ControlCollection::End()
{
  return m_List.End();
}

Control::Control()
:m_ClientRectangle(Point2D<>(0,0)
,Point2D<>(1,1))
,m_Parent(0)
{
  Controls.m_Parent=this;
}

Control::~Control()
{
}

void Control::Resize(const RF_Geo::Size2D<>& Value)
{
    for (List<Control*>::Iterator it=Controls.Begin(); it!=Controls.End(); ++it)
        (*it)->Resize(Value);
    OnResize(Value);
}

void Control::Reposition(const RF_Geo::Point2D<>& Value)
{
    for (List<Control*>::Iterator it = Controls.Begin(); it != Controls.End(); ++it)
        (*it)->Reposition(Value);
    OnReposition(Value);
}

Bool Control::HasChildren()
{
    return Controls.Count()>0 ? true:false;
}

Control* Control::Parent()
{
  return m_Parent;
}

void Control::Parent(const Control* Value)
{
  m_Parent=const_cast<Control*>(Value);
}

Control* Control::Root()
{
  Control* ctrl=this;
  while (ctrl->Parent())
    ctrl=ctrl->Parent();
  return ctrl;
}

Int32 Control::Top()
{
    return m_ClientRectangle.Top();
}

void Control::Top(const Int32 &Value)
{
    m_ClientRectangle.SetPosition(Point2D<>(m_ClientRectangle.Left(),Value));
}

Int32 Control::Left()
{
    return m_ClientRectangle.Left();
}

void Control::Left(const Int32 &Value)
{
    m_ClientRectangle.SetPosition(Point2D<>(Value,m_ClientRectangle.Top()));
}

UInt32 Control::Width()
{
    return m_ClientRectangle.Width();
}

void Control::Width(const UInt32 &Value)
{
    m_ClientRectangle.Width(Value);
}

UInt32 Control::Height()
{
    return m_ClientRectangle.Height();
}

void Control::Height(const UInt32 &Value)
{
    m_ClientRectangle.Height(Value);
}

Size2D<> Control::GetSize()
{
    return m_ClientRectangle.GetSize();
}

void Control::SetSize(const Size2D<>& Value)
{
    return m_ClientRectangle.SetSize(Value);
}

Bool Control::Visible()
{
    return m_Visible;
}

void Control::Vibisle(const Bool &Value)
{
    m_Visible=Value;
}
