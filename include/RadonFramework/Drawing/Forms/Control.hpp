#ifndef RF_DRAWING_FORMS_CONTROL_HPP
#define RF_DRAWING_FORMS_CONTROL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>

namespace RadonFramework { namespace Forms {

class Control;

class ControlCollection
{
friend class Control;
public:
    void Add(Control *Obj);
    Control* Get(const RF_Type::Size Index);
    RF_Type::Size Count();
    RF_Collect::List<Control*>::Iterator Begin();
    RF_Collect::List<Control*>::Iterator End();
protected:
    RF_Collect::List<Control*> m_List;
    Control* m_Parent;
};

class Control
{
public:
    Control();
    virtual ~Control();
    virtual RF_Type::Bool HasChildren();
    virtual Control* Parent();
    virtual void Parent(const Control* Value);
    virtual Control* Root();

    virtual RF_Type::Int32 Top();
    virtual void Top(const RF_Type::Int32 &Value);
    virtual RF_Type::Int32 Left();
    virtual void Left(const RF_Type::Int32 &Value);
    virtual RF_Type::UInt32 Width();
    virtual void Width(const RF_Type::UInt32 &Value);
    virtual RF_Type::UInt32 Height();
    virtual void Height(const RF_Type::UInt32 &Value);
    virtual RF_Geo::Size2D<> GetSize();
    virtual void SetSize(const RF_Geo::Size2D<> &Value);

    virtual void Resize(const RF_Geo::Size2D<>& Value);
    virtual void Reposition(const RF_Geo::Point2D<>& Value);

    virtual RF_Type::Bool Visible();
    virtual void Vibisle(const RF_Type::Bool &Value);

    RF_Pattern::Event<const RF_Geo::Size2D<>&> OnResize;
    RF_Pattern::Event<const RF_Geo::Point2D<>&> OnReposition;
    ControlCollection Controls;
protected:
    RF_Geo::Rectangle<> m_ClientRectangle;
    Control* m_Parent;
    RF_Type::Bool m_Visible;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif // RF_DRAWING_FORMS_CONTROL_HPP
