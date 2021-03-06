#pragma once

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Utils/StringOperators.hpp>

namespace RadonFramework::Core::Common
{
template <typename Parent, typename ErrorEnum, RF_Type::UInt32 ErrorCount>
struct Error
{
  // computer readable
  ErrorEnum ErrorCode;
  // human readable
  RF_Type::UInt32 InternalErrorText;  // default:0
  RF_Type::UInt32 InternalDebugData;  // default:0

  static RF_Type::String ErrorText[ErrorCount];

  static Parent Generate(ErrorEnum AError)
  {
    Parent err;
    err.ErrorCode = AError;
    err.InternalErrorText = 0;
    err.InternalDebugData = 0;
    return err;
  }

  static Parent
  Generate(ErrorEnum AError, const RF_Type::String& AInternalErrorText)
  {
    Parent err;
    err.ErrorCode = AError;
    err.InternalErrorText << AInternalErrorText;
    err.InternalDebugData = 0;
    return err;
  }

  static Parent Generate(ErrorEnum AError,
                         const RF_Type::String& AInternalErrorText,
                         void* AInternalDebugData)
  {
    Parent err;
    err.ErrorCode = AError;
    err.InternalErrorText = AInternalErrorText;
    err.InternalDebugData = AInternalDebugData;
    return err;
  }
};
}  // namespace RadonFramework::Core::Common

namespace RF_Common = RadonFramework::Core::Common;