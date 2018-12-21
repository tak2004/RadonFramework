#ifndef RF_KEYBOARDEVENT_HPP
#define RF_KEYBOARDEVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/VirtualKey.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO
{
class KeyboardEvent
{
public:
  KeyboardEvent() = default;
  RF_Type::String PrintableCharacter;
  VirtualKey Key = VirtualKey::NotSet;
  RF_Type::Bool Ctrl = false;
  RF_Type::Bool Alt = false;
  RF_Type::Bool Shift = false;

private:
  RF_Type::UInt8 Padding[28];
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_KEYBOARDEVENT_HPP