#ifndef RF_IO_ENCODERSERVICE_HPP
#define RF_IO_ENCODERSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/IO/Encoders/Interface.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework::IO
{
class Encoder;

class EncoderService : public RF_Pattern::Service
{
public:
  EncoderService(const RF_Type::String& Name);

  virtual RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC) const;
  virtual RF_Type::Bool IsEncoderInterface(const RF_Type::UInt32 FourCC,
                                           RF_Encoders::Interface Target) const;
  virtual RF_Mem::AutoPointer<Encoder>
  CreateEncoder(const RF_Type::UInt32 FourCC,
                RF_Encoders::Interface Target) = 0;
  RF_Type::Bool IsAvailable() const;

protected:
  RF_Type::Bool m_IsAvailable;
};

template <class T>
class GenericEncoderService : public EncoderService
{
public:
  GenericEncoderService(const RF_Type::String& Name) : EncoderService(Name)
  {
    m_IsAvailable = true;
  }

  RF_Mem::AutoPointer<Encoder>
  CreateEncoder(const RF_Type::UInt32 FourCC,
                RF_Encoders::Interface Target) override
  {
    RF_Mem::AutoPointer<Encoder> result;
    if(IsEncoderInterface(FourCC, Target))
      result = RF_Mem::AutoPointer<Encoder>(new T());
    return result;
  }

  RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC) const override
  {
    return T::IsFourCCSupported(FourCC);
  }

  RF_Type::Bool IsEncoderInterface(const RF_Type::UInt32 FourCC,
                                   RF_Encoders::Interface Target) const override
  {
    return T::IsFourCCSupported(FourCC) &&
           T::IsInterfaceSupported(FourCC, Target);
  }
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_IO_ENCODERSERVICE_HPP
