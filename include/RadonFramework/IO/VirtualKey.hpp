#ifndef RF_RF_VIRTUALKEY_HPP_HPP
#define RF_RF_VIRTUALKEY_HPP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>

namespace RadonFramework::IO
{
enum class VirtualKey : RF_Type::UInt8
{
  NotSet,
  Escape,
  Left,
  Up,
  Right,
  Down,
  ShiftLeft,
  ShiftRight,
  ControlLeft,
  ControlRight,
  AltLeft,
  AltRight,
  Enter,
  Tab,
  Backspace,
  Insert,
  Delete,
  Home,
  End,
  PageUp,
  PageDown,
  Keypad0,
  Keypad1,
  Keypad2,
  Keypad3,
  Keypad4,
  Keypad5,
  Keypad6,
  Keypad7,
  Keypad8,
  Keypad9,
  KeypadDivide,
  KeypadMultiply,
  KeypadSubtract,
  KeypadAdd,
  KeypadDecimal,
  KeypadEnter,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
};
}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_RF_VIRTUALKEY_HPP_HPP
