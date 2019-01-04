#pragma once

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO
{
class Appender
{
public:
  virtual void WriteInfo(const RF_Type::String& Text) = 0;
  virtual void WriteError(const RF_Type::String& Text) = 0;
  virtual void WriteFatalError(const RF_Type::String& Text) = 0;
  virtual void WriteDebug(const RF_Type::String& Text) = 0;

protected:
};

}  // namespace RadonFramework::IO

namespace RF_IO = RadonFramework::IO;