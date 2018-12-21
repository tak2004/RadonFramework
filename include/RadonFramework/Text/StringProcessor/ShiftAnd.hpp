#ifndef RF_TEXT_STRINGPROCESSORS_SHIFTAND_HPP
#define RF_TEXT_STRINGPROCESSORS_SHIFTAND_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Text::StringProcessors
{
struct ShiftAnd
{
  struct StorageType
  {
    StorageType();
    ~StorageType();
    RF_Type::String Search;
    RF_Type::Int32 Position;
    RF_Type::UInt32 Lastbit;
    RF_Type::UInt32* Shift;
  };

  static RF_Type::Bool Init(RF_Type::String& Text,
                            const RF_Type::UInt32 Position,
                            StorageType* Storage);

  static void Reset(RF_Type::String& Text,
                    const RF_Type::UInt32 Position,
                    StorageType* Storage);

  static RF_Type::Int32 DoNext(RF_Type::String& Text, StorageType* Storage);

  static RF_Type::Int32 DoAll(RF_Type::String& Text, StorageType* Storage);
};

}  // namespace RadonFramework::Text::StringProcessors

#endif  // RF_TEXT_STRINGPROCESSORS_SHIFTAND_HPP