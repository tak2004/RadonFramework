#ifndef RF_KEYBOARDEVENT_HPP
#define RF_KEYBOARDEVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/VirtualKey.hpp>

namespace RadonFramework { namespace IO {

class KeyboardEvent
{
public:
    KeyboardEvent():Key(VirtualKey::NotSet), Ctrl(false), Alt(false), Shift(false){}
    RF_Type::String PrintableCharacter;
    VirtualKey Key;
    RF_Type::Bool Ctrl;
    RF_Type::Bool Alt;
    RF_Type::Bool Shift;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_KEYBOARDEVENT_HPP