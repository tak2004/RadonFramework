#ifndef RF_PROTOCOLSERVICE_HPP
#define RF_PROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework::IO
{
class Uri;
class Stream;

class ProtocolService : public RF_Pattern::Service
{
public:
  ProtocolService(const RF_Type::String& Name);

  virtual RF_Type::Bool Exists(const Uri& URI) = 0;

  virtual Stream* GenerateInterface(const Uri& URI) = 0;

  virtual void FreeInterface(const Uri& URI) = 0;
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_PROTOCOLSERVICE_HPP
