#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"

namespace RadonFramework::Forms {

Cursor::Cursor(RF_Type::Int32 Type)
:m_Type(Type)
{
}

RF_Mem::AutoPointer<Cursor> Cursor::GetSystemCustomCursor(const RF_Type::String& Name)
{
    RF_Mem::AutoPointer<Cursor> result;
    return result;
}

RF_Type::Int32 Cursor::GetType()const
{
    return m_Type;
}

}