#ifndef RF_CONTROL_HPP
#define RF_CONTROL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>

namespace RadonFramework
{
    namespace Geometry
    {
        class Size;
    }
    namespace Forms
    {
        class Control;

        class ControlCollection
        {
            friend class Control;
            public:
                void Add(Control *Obj);
                Control* Get(const RFTYPE::Size Index);
                RFTYPE::Size Count();
                Collections::List<Control*>::Iterator Begin();
                Collections::List<Control*>::Iterator End();
            protected:
                Collections::List<Control*> m_List;
                Control* m_Parent;
         };

        class Control
        {
            public:
                Control();
                virtual ~Control();
                virtual RFTYPE::Bool HasChildren();
                virtual Control* Parent();
                virtual void Parent(const Control* Value);
                virtual Control* Root();

                virtual RFTYPE::Int32 Top();
                virtual void Top(const RFTYPE::Int32 &Value);
                virtual RFTYPE::Int32 Left();
                virtual void Left(const RFTYPE::Int32 &Value);
                virtual RFTYPE::UInt32 Width();
                virtual void Width(const RFTYPE::UInt32 &Value);
                virtual RFTYPE::UInt32 Height();
                virtual void Height(const RFTYPE::UInt32 &Value);
                virtual Math::Geometry::Size2D<> GetSize();
                virtual void SetSize(const Math::Geometry::Size2D<> &Value);

                virtual void Resize(const Math::Geometry::Size2D<>& Value);
                virtual void Reposition(const Math::Geometry::Point2D<>& Value);

                virtual RFTYPE::Bool Visible();
                virtual void Vibisle(const RFTYPE::Bool &Value);

                Event<const Math::Geometry::Size2D<>&> OnResize;
                Event<const Math::Geometry::Point2D<>&> OnReposition;
                ControlCollection Controls;
            protected:
                Math::Geometry::Rectangle<> m_ClientRectangle;
                Control* m_Parent;
                RFTYPE::Bool m_Visible;
        };
    }
}

#endif
