#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Control.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Math/Geometry/Size2D.hpp"
#include "RadonFramework/Drawing/Forms/Form.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"
#include "RadonFramework/Drawing/Forms/Layouter.hpp"

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
    RF_ASSERT(Index < m_List.Count(), "Index out of bounds.");

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

ControlCollection::ControlCollection()
:m_Parent(nullptr)
{
}

RF_Type::Int32 ControlCollection::IndexOfChild(const Control& Obj) const
{
    auto result = -1;
    RF_Type::Size index = 0;
    List<Control*>::Iterator it = m_List.Begin();
    for(; it != m_List.End(); ++it, ++index)
    {
        if(*it == &Obj)
        {
            result = index;
            break;
        }
    }
    return result;
}

void ControlCollection::RemoveChild(Control& Obj)
{
    List<Control*>::Iterator it = m_List.Begin();
    for(; it != m_List.End(); ++it)
    {
        if(*it == &Obj)
        {
            m_List.Remove(it);
            break;
        }
    }    
}

Control::Control(Control* Parent /*= nullptr*/)
:m_ClientRectangle(Point2D<>(0,0) ,Point2D<>(1,1))
,m_VisualId(0)
,m_Layouter(nullptr)
{
    if(Parent)
    {
        Parent->AddChild(*this);
    }
}

Control::~Control()
{
}

RF_Type::Float32 Control::Top()const
{
    return m_ClientRectangle.Top();
}

void Control::Top(const RF_Type::Float32 &Value)
{
    Rectanglef contentRectangle(m_ClientRectangle);
    contentRectangle.Top(Value);
    ChangeContentRectangle(contentRectangle, m_ClientRectangle);
}

RF_Type::Float32 Control::Left()const
{
    return m_ClientRectangle.Left();
}

void Control::Left(const RF_Type::Float32 &Value)
{
    Rectanglef contentRectangle(m_ClientRectangle);
    contentRectangle.Left(Value);
    ChangeContentRectangle(contentRectangle, m_ClientRectangle);
}

RF_Type::Float32 Control::Width()const
{
    return m_ClientRectangle.Width();
}

void Control::Width(const RF_Type::Float32 &Value)
{
    Rectanglef contentRectangle(m_ClientRectangle);
    contentRectangle.Width(Value);
    ChangeContentRectangle(contentRectangle,m_ClientRectangle);
}

RF_Type::Float32 Control::Height()const
{
    return m_ClientRectangle.Height();
}

void Control::Height(const RF_Type::Float32 &Value)
{
    Rectanglef contentRectangle(m_ClientRectangle);
    contentRectangle.Height(Value);
    ChangeContentRectangle(contentRectangle,m_ClientRectangle);
}

Size2Df Control::GetSize()const
{
    return m_ClientRectangle.GetSize();
}

void Control::SetSize(const Size2Df& Value)
{
    Rectanglef contentRectangle(m_ClientRectangle);
    contentRectangle.SetSize(Value);
    ChangeContentRectangle(contentRectangle,m_ClientRectangle);
}

Bool Control::Visible()const
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
    Obj.ChangeContentRectangle(m_ClientRectangle, m_ClientRectangle);
}

const RF_Draw::Path2D& Control::GetPath() const
{
    return m_Path;
}

void Control::Animate(const RF_Type::UInt64 Now)
{
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
        (*it)->Animate(Now);
}

RF_Type::UInt32 Control::GetVisualId() const
{
    return m_VisualId;
}

void Control::SetVisualId(RF_Type::UInt32 NewId)
{
    m_VisualId = NewId;
}

RF_Type::Bool Control::IsMouseOver()
{
    Form& window = static_cast<Form&>(GetRoot());
    auto cursorPosition = window.GetCursorPosition();
    return m_ClientRectangle.IsIntersect(cursorPosition);
}

RF_Type::Float32 Control::ScaleHorizontal(RF_Type::Float32 Pixels)
{
    Form& window = static_cast<Form&>(GetRoot());
    return window.GetHorizontalScale() * Pixels;
}

RF_Type::Float32 Control::ScaleVertical(RF_Type::Float32 Pixels)
{
    Form& window = static_cast<Form&>(GetRoot());
    return window.GetVerticalScale() * Pixels;
}

void Control::MouseMoved(const RF_IO::MouseEvent& Value)
{
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
    {
        if((*it)->IsMouseOver())
        {
            (*it)->MouseMoved(Value);
        }
    }
    OnMouseMove(Value);
}

void Control::SetCursor(const Cursor& NewCursor)
{
    Form& window = static_cast<Form&>(GetRoot());
    window.ChangeCursor(NewCursor);
}

void Control::RebuildVisuals()
{
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
    {
        (*it)->RebuildVisuals();
    }
}

void Control::MouseButtonPressed(const RF_IO::MouseEvent& Value)
{
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
    {
        if((*it)->IsMouseOver())
        {
            (*it)->MouseButtonPressed(Value);
        }
    }
    OnMouseButtonPressed(Value);
}

void Control::MouseButtonReleased(const RF_IO::MouseEvent& Value)
{
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
    {
        if((*it)->IsMouseOver())
        {
            (*it)->MouseButtonReleased(Value);
        }
    }    
    OnMouseButtonReleased(Value);
}

RF_Geo::Point2Df Control::GetPosition() const
{
    return m_ClientRectangle.GetPosition();
}

void Control::SetLayouter(const Layouter& Layout)
{
    m_Layouter = &Layout;
}

void Control::ChangeContentRectangle(const RF_Geo::Rectanglef& NewContent,
                                     const RF_Geo::Rectanglef& OldContent)
{
    // Take the size and position from the parent by default.
    Rectanglef newContentRectangle(NewContent);
    if(m_Layouter)
    {// This Control have to ask the parent for the content rectangle.
        newContentRectangle = m_Layouter->GetContentRect(*this);
    }
    m_ClientRectangle = newContentRectangle;
    Rectanglef oldContentRectangle(m_ClientRectangle);
    // Inform the child's of the new content rectangle.
    // Update the content rectangle after to allow the child look for the current one.
    for(List<Control*>::Iterator it = Begin(); it != End(); ++it)
    {
        (*it)->ChangeContentRectangle(newContentRectangle, oldContentRectangle);
    }
    OnChangeContentRectangle(newContentRectangle);
}

const RF_Geo::Rectanglef& Control::GetClientRectangle() const
{
    return m_ClientRectangle;
}
