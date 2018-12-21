#ifndef RF_MEMORYPROTOCOLSERVICE_HPP
#define RF_MEMORYPROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/IO/ProtocolService.hpp>

namespace RadonFramework::IO
{
class MemoryProtocolService : public ProtocolService
{
public:
  MemoryProtocolService(const RF_Type::String& Name);

  RF_Type::Bool Exists(const Uri& URI) override;

  Stream* GenerateInterface(const Uri& URI) override;

  void FreeInterface(const Uri& URI) override;

private:
  RF_Idiom::PImpl<MemoryProtocolService> m_PImpl;
  RF_Type::UInt8 Padding[24];
};

}  // namespace RadonFramework::IO

#endif  // RF_MEMORYPROTOCOLSERVICE_HPP
