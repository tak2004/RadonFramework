#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

using namespace RadonFramework::Collections;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

void ControlCollection::AddChild(Control& Obj)
{
  m_List.AddLast(&Obj);
}

Control* ControlCollection::GetChild(const Size Index)
{
    Assert(Index < m_List.Count(), "Index out of bounds.");

    List<Control*>::Iterator it=m_List.Begin();
    for (Size i=0; i<Index; i++)
        ++it;

    return *it;
}

Size ControlCollection::GetChildCount()const
{
    return m_List.Count();
}

List<Control*>::ConstIterator ControlCollection::ConstBegin()const
{
    return m_List.ConstBegin();
}

List<Control*>::ConstIterator ControlCollection::ConstEnd()const
{
    return m_List.ConstEnd();
}

List<Control*>::Iterator ControlCollection::Begin()const
{
  return m_List.Begin();
}

List<Control*>::Iterator ControlCollection::End()const
{
  return m_List.End();
}

Bool ControlCollection::HasChildren()const
{
    return GetChildCount() > 0 ? true : false;
}

const Control* ControlCollection::GetParent()const
{
    return m_Parent;
}

Control* ControlCollection::GetParent()
{
    return m_Parent;
}

void ControlCollection::SetParent(Control& Value)
{
    m_Parent = &Value;
}

Control::Control(Control* Parent /*= nullptr*/)
:m_ClientRectangle(Point2D<>(0,0)
,Point2D<>(1,1))
{
    if(Parent)
    {
        Parent->AddChild(*this);
    }
}

Control::~Control()
{
}

void Control::Resize(const RF_Geo::Size2D<>& Value)
{
    m_ClientRectangle.Width(Value.Width);
    m_ClientRectangle.Height(Value.Height);
    for (List<Control*>::Iterator it=Begin(); it!=End(); ++it)
        (*it)->Resize(Value);
    OnResize(Value);
}

void Control::Reposition(const RF_Geo::Point2D<>& Value)
{
    for (List<Control*>::Iterator it = Begin(); it != End(); ++it)
        (*it)->Reposition(Value);
    OnReposition(Value);
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

void Control::Visible(const Bool &Value)
{
    m_Visible=Value;
}

const Control& Control::GetRoot()const
{
    const Control* ctrl = this;
    while(ctrl->GetParent())
        ctrl = ctrl->GetParent();
    return *ctrl;
}

Control& Control::GetRoot()
{
    Control* ctrl = this;
    while(ctrl->GetParent())
        ctrl = ctrl->GetParent();
    return *ctrl;
}

void Control::AddChild(Control& Obj)
{
    ControlCollection::AddChild(Obj);
    Obj.SetParent(*this);
}

const RF_Draw::Path2D& Control::GetPath() const
{
    return m_Path;
}
