#ifndef RF_DRAWING_FORMS_CURSOR_HPP
#define RF_DRAWING_FORMS_CURSOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Forms {

class Cursor
{
public:
    enum Common : RF_Type::Int32
    {
        Default,
        Cross,
        EastResize,
        Hand,
        Move,
        NorthResize,
        NorthEastResize,
        NorthWestResize,
        SouthResize,
        SouthEastResize,
        SouthWestResize,
        Text,
        Wait,
        WestResize
    };
    Cursor(RF_Type::Int32 Type);
    static RF_Mem::AutoPointer<Cursor> GetSystemCustomCursor(const RF_Type::String& Name);

    RF_Type::Int32 GetType()const;
protected:
    RF_Type::Int32 m_Type;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif // RF_SHORTHAND_NAMESPACE_FORM

#endif // RF_DRAWING_FORMS_CURSOR_HPP