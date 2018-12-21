#ifndef RF_ENCODERSERVICELOCATOR_HPP
#define RF_ENCODERSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/EncoderService.hpp>

namespace RadonFramework::IO
{
class NullEncoderService : public EncoderService
{
public:
  NullEncoderService(const RF_Type::String& Name) : EncoderService(Name) {}

  RF_Mem::AutoPointer<Encoder>
  CreateEncoder(const RF_Type::UInt32 FourCC,
                RF_Encoders::Interface Target) final
  {
    return RF_Mem::AutoPointer<Encoder>();
  }
};

struct EncoderServiceLocator
: public RF_Pattern::Locator<EncoderService, NullEncoderService>
{
  EncoderServiceLocator() = delete;

  static EncoderServiceLocator::Iterator
  FindCodec(const RF_Type::UInt32 FCC, RF_Encoders::Interface Target);

  static EncoderServiceLocator::Iterator
  FindByNameOrFourCC(const RF_Type::String& Name, const RF_Type::UInt32 FCC);
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif
