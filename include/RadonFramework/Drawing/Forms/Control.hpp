#ifndef RF_DRAWING_FORMS_CONTROL_HPP
#define RF_DRAWING_FORMS_CONTROL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Drawing/Path2D.hpp>
#include <RadonFramework/IO/MouseEvent.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>

namespace RadonFramework::Forms
{
class Control;
class Cursor;
class Layouter;

class ControlCollection
{
public:
  using Iterator = RF_Collect::List<Control*>::Iterator;
  using ConstIterator = RF_Collect::List<Control*>::ConstIterator;
  ControlCollection();
  virtual void AddChild(Control& Obj);
  virtual void RemoveChild(Control& Obj);
  Control* GetChild(const RF_Type::Size Index);
  RF_Type::Size GetChildCount() const;
  RF_Type::Int32 IndexOfChild(const Control& Obj) const;

  Iterator Begin() const;
  Iterator End() const;
  ConstIterator ConstBegin() const;
  ConstIterator ConstEnd() const;

  RF_Type::Bool HasChildren() const;
  const Control* GetParent() const;
  Control* GetParent();
  void SetParent(Control& Value);

private:
  RF_Collect::List<Control*> m_List;
  Control* m_Parent;
};

class Control : public ControlCollection
{
public:
  Control(Control* Parent = nullptr);
  virtual ~Control();

  void AddChild(Control& Obj) override;
  virtual RF_Type::Float32 Top() const;
  virtual void Top(const RF_Type::Float32& Value);
  virtual RF_Type::Float32 Left() const;
  virtual void Left(const RF_Type::Float32& Value);
  virtual RF_Type::Float32 Width() const;
  virtual void Width(const RF_Type::Float32& Value);
  virtual RF_Type::Float32 Height() const;
  virtual void Height(const RF_Type::Float32& Value);
  virtual RF_Geo::Size2Df GetSize() const;
  virtual void SetSize(const RF_Geo::Size2Df& Value);
  virtual RF_Geo::Point2Df GetPosition() const;
  virtual const RF_Geo::Rectanglef& GetClientRectangle() const;

  /// The parent ask for reposition and resize the Control.
  virtual void ChangeContentRectangle(const RF_Geo::Rectanglef& NewContent,
                                      const RF_Geo::Rectanglef& OldContent);
  /// Mouse were moving over this control.
  virtual void MouseMoved(const RF_IO::MouseEvent& Value);
  /// Mouse was pressed on this Control.
  virtual void MouseButtonPressed(const RF_IO::MouseEvent& Value);
  /// Mouse was released on this Control.
  virtual void MouseButtonReleased(const RF_IO::MouseEvent& Value);

  virtual void RebuildVisuals();

  virtual RF_Type::Bool Visible() const;
  virtual void Visible(const RF_Type::Bool& Value);

  virtual const Drawing::Path2D& GetPath() const;
  virtual const Control& GetRoot() const;
  virtual Control& GetRoot();

  RF_Type::UInt32 GetVisualId() const;
  void SetVisualId(RF_Type::UInt32 NewId);

  virtual void Animate(const RF_Type::UInt64 Now);

  void SetLayouter(const Layouter& Layout);

  RF_Pattern::Event<const RF_Geo::Rectanglef&> OnChangeContentRectangle;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseButtonPressed;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseButtonReleased;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseMove;

protected:
  RF_Draw::Path2D m_Path;

  RF_Type::Bool IsMouseOver();
  RF_Type::Float32 ScaleHorizontal(RF_Type::Float32 Pixels);
  RF_Type::Float32 ScaleVertical(RF_Type::Float32 Pixels);
  void SetCursor(const Cursor& NewCursor);

private:
  RF_Geo::Rectanglef m_ClientRectangle;
  RF_Type::UInt32 m_VisualId;
  const Layouter* m_Layouter;
  RF_Type::Bool m_Visible;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif  // RF_DRAWING_FORMS_CONTROL_HPP
