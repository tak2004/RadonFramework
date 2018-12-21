#ifndef RF_PROTOCOLSERVICELOCATOR_HPP
#define RF_PROTOCOLSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/ProtocolService.hpp>
#include <RadonFramework/IO/Resource.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::IO
{
class NullProtocolService : public ProtocolService
{
public:
  NullProtocolService(const RF_Type::String& Name) : ProtocolService(Name) {}
  RF_Type::Bool Exists(const Uri& URI) override { return false; }
  Stream* GenerateInterface(const Uri& URI) override { return nullptr; }
  void FreeInterface(const Uri& URI) override {}
};

struct ProtocolServiceLocator
: public RF_Pattern::Locator<ProtocolService, NullProtocolService>
{
  ProtocolServiceLocator() = delete;
};

}  // namespace RadonFramework::IO

#endif  // RF_PROTOCOLSERVICELOCATOR_HPP
