#ifndef RF_DRAWING_FORMS_CONTROL_HPP
#define RF_DRAWING_FORMS_CONTROL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Drawing/Path2D.hpp>

namespace RadonFramework { namespace Forms {

class Control;

class ControlCollection
{
public:
    virtual void AddChild(Control& Obj);
    Control* GetChild(const RF_Type::Size Index);
    RF_Type::Size GetChildCount()const;
    RF_Collect::List<Control*>::Iterator Begin()const;
    RF_Collect::List<Control*>::Iterator End()const;
    RF_Collect::List<Control*>::ConstIterator ConstBegin()const;
    RF_Collect::List<Control*>::ConstIterator ConstEnd()const;
    
    RF_Type::Bool HasChildren()const;
    const Control* GetParent()const;
    Control* GetParent();
    void SetParent(Control& Value);
private:
    RF_Collect::List<Control*> m_List;
    Control* m_Parent;
};

class Control: public ControlCollection
{
public:
    Control(Control* Parent = nullptr);
    virtual ~Control();

    virtual void AddChild(Control& Obj)override;
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
    virtual void Visible(const RF_Type::Bool &Value);

    virtual const Drawing::Path2D& GetPath()const;
    virtual const Control& GetRoot()const;
    virtual Control& GetRoot();

    RF_Pattern::Event<const RF_Geo::Size2D<>&> OnResize;
    RF_Pattern::Event<const RF_Geo::Point2D<>&> OnReposition;
protected:
    RF_Geo::Rectangle<> m_ClientRectangle;
    RF_Draw::Path2D m_Path;
private:
    RF_Type::Bool m_Visible;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif // RF_DRAWING_FORMS_CONTROL_HPP
