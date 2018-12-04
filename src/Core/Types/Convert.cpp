#include "RadonFramework/Core/Types/Convert.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/String.hpp"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Core::Types;

Bool Convert::ToBool(const bool Value)
{
  Bool result = {Value};
  return result;
}

Bool Convert::ToBool(const String& In, Bool& Out)
{
  Bool result = false;
  String tmp(In);
  tmp.ToLower();
  if(tmp == "true")
  {
    Out = true;
    result = true;
  }
  if(tmp == "false")
  {
    Out = false;
    result = true;
  }
  return result;
}

Bool Convert::ToInt8(const String& In, Int8& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Int64 n;
    if(RF_SysStr::ToInt64(In, 10, n) && n >= Int8Min && n <= Int8Max)
    {
      Out = static_cast<UInt8>(n);
      result = true;
    }
  }
  return result;
}

Bool Convert::ToInt16(const String& In, Int16& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Int64 n;
    if(RF_SysStr::ToInt64(In, 10, n) && n >= Int16Min && n <= Int16Max)
    {
      Out = static_cast<UInt16>(n);
      result = true;
    }
  }
  return result;
}

Bool Convert::ToInt32(const String& In, Int32& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Int64 n;
    ;
    if(RF_SysStr::ToInt64(In, 10, n) && n >= Int32Min && n <= Int32Max)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

Bool Convert::ToInt64(const String& In, Int64& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Int64 n;
    if(RF_SysStr::ToInt64(In, 10, n) && n >= Int64Min && n <= Int64Max)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

Bool Convert::ToUInt8(const String& In, UInt8& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    UInt64 n;
    if(RF_SysStr::ToUInt64(In, 10, n) && n >= UInt8Min && n <= UInt8Max)
    {
      Out = static_cast<UInt8>(n);
      result = true;
    }
  }
  return result;
}

Bool Convert::ToUInt16(const String& In, UInt16& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    UInt64 n;
    if(RF_SysStr::ToUInt64(In, 10, n) && n >= UInt16Min && n <= UInt16Max)
    {
      Out = static_cast<UInt16>(n);
      result = true;
    }
  }
  return result;
}

Bool Convert::ToUInt32(const String& In, UInt32& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    UInt64 n;
    if(RF_SysStr::ToUInt64(In, 10, n) && n >= UInt32Min && n <= UInt32Max)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

Bool Convert::ToUInt64(const String& In, UInt64& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    UInt64 n;
    if(RF_SysStr::ToUInt64(In, 10, n) && n >= UInt64Min && n <= UInt64Max)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

Bool Convert::ToFloat32(const String& In, Float32& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Float64 n;
    if(RF_SysStr::ToFloat64(In, n) && n >= Float32Min && n <= Float32Max)
    {
      Out = static_cast<Float32>(n);
      result = true;
    }
  }
  return result;
}

Bool Convert::ToFloat64(const String& In, Float64& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    Float64 n;
    if(RF_SysStr::ToFloat64(In, n) && n >= Float64Min && n <= Float64Max)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

Bool Convert::ToSize(const String& In, Size& Out)
{
  Bool result = false;
  if(In.Length() > 0)
  {
    UInt64 n;
    if(RF_SysStr::ToUInt64(In, 10, n) && n >= SizeMin && n <= SizeMax)
    {
      Out = n;
      result = true;
    }
  }
  return result;
}

String Convert::ToString(const Bool Value)
{
  static const String TRUE("true");
  static const String FALSE("false");
  String result(Value ? TRUE : FALSE);
  return result;
}

String Convert::ToString(const Int8 Value)
{
  return String::Format(String("%i"), Value);
}

String Convert::ToString(const Int16 Value)
{
  return String::Format(String("%i"), Value);
}

String Convert::ToString(const Int32 Value)
{
  return String::Format(String("%i"), Value);
}

String Convert::ToString(const Int64 Value)
{
  return String::Format(String("%lld"), Value);
}

String Convert::ToString(const UInt8 Value)
{
  return String::Format(String("%u"), Value);
}

String Convert::ToString(const UInt16 Value)
{
  return String::Format(String("%u"), Value);
}

String Convert::ToString(const UInt32 Value)
{
  return String::Format(String("%u"), Value);
}

String Convert::ToString(const UInt64 Value)
{
  return String::Format(String("%llu"), Value);
}

String Convert::ToString(const Float32 Value)
{
  return String::Format(String("%f"), Value);
}

String Convert::ToString(const Float64 Value)
{
  return String::Format(String("%f"), Value);
}