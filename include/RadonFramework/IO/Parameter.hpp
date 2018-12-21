#ifndef RF_IO_PARAMETER_HPP
#define RF_IO_PARAMETER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/IO/OptionRule.hpp>
#include <RadonFramework/IO/OptionValue.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::IO
{
class Parameter
{
public:
  /// Parse standard C application parameter.
  RF_Type::Bool
  ParsingWithErrorOutput(const char* argv[],
                         int argc,
                         const Memory::AutoPointerArray<OptionRule>& Rules,
                         RF_Type::String& ErrorMessage);

  /// Parse standard C application parameter.
  RF_Type::Bool
  ParsingWithLogging(const char* argv[],
                     int argc,
                     const Memory::AutoPointerArray<OptionRule>& Rules);

  /// Parse a string array and write to ErrorMessage if an error occur.
  RF_Type::Bool SafeParsingWithErrorOutput(
      const Memory::AutoPointerArray<RF_Type::String>& Parameters,
      const Memory::AutoPointerArray<OptionRule>& Rules,
      RF_Type::String& ErrorMessage);

  /// Parse a string array.
  RF_Type::Bool SafeParsingWithLogging(
      const Memory::AutoPointerArray<RF_Type::String>& Parameters,
      const Memory::AutoPointerArray<OptionRule>& Rules);

  const Memory::AutoPointerArray<OptionValue>& Values();

private:
  Memory::AutoPointerArray<OptionValue> m_Values;
};

}  // namespace RadonFramework::IO

#endif  // RF_IO_PARAMETER_HPP