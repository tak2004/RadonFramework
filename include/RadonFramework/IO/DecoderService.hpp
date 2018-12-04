#ifndef RF_IO_DECODERSERVICE_HPP
#define RF_IO_DECODERSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/IO/Decoders/Interface.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework::IO {

class Decoder;

class DecoderService:public RF_Pattern::Service
{
public:
    DecoderService(const RF_Type::String &Name);

    virtual RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC)const;
    virtual RF_Type::Bool IsDecoderInterface(const RF_Type::UInt32 FourCC, 
                                             RF_Decoders::Interface Target)const;
    virtual RF_Mem::AutoPointer<Decoder> CreateDecoder(const RF_Type::UInt32 FourCC,
                                                       RF_Decoders::Interface Target) = 0;
    RF_Type::Bool IsAvailable()const;
protected:
    RF_Type::Bool m_IsAvailable;
};

template<class T>
class GenericDecoderService:public DecoderService
{
public:
    GenericDecoderService(const RF_Type::String &Name)
    :DecoderService(Name)
    {
        m_IsAvailable = true;
    }

    virtual RF_Mem::AutoPointer<Decoder> CreateDecoder(const RF_Type::UInt32 FourCC,
                                                       RF_Decoders::Interface Target)
    { 
        RF_Mem::AutoPointer<Decoder> result;
        if(IsDecoderInterface(FourCC, Target))
            result = RF_Mem::AutoPointer<Decoder>(new T());
        return result;
    }

    virtual RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC)const
    {
        return T::IsFourCCSupported(FourCC);
    }

    virtual RF_Type::Bool IsDecoderInterface(const RF_Type::UInt32 FourCC,
                                             RF_Decoders::Interface Target)const
    {
        return T::IsFourCCSupported(FourCC) && T::IsInterfaceSupported(FourCC, Target);
    }
};
  
}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_DECODERSERVICE_HPP
