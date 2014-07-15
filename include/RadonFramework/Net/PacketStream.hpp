#ifndef RF_NET_PACKETSTREAM_HPP
#define RF_NET_PACKETSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

class PIMPL;

namespace RadonFramework
{
    namespace IO
    {
        class MemoryCollectionStream;
    }

    namespace Net
    {
        class PacketStream
        {
            public:
                typedef Delegate1<IO::MemoryCollectionStream&,RF_Type::Bool> SplitFunctionType;
                typedef Delegate1<Memory::AutoPointerArray<RF_Type::UInt8>&,RF_Type::Bool> DispatcherFunctionType;
                PacketStream();

                void Enqueue(Memory::AutoPointerArray<RF_Type::UInt8>& packet);

                void MaxDataSize(const RF_Type::UInt32 NewSize);

                RF_Type::UInt32 MaxDataSize()const;

                void SetPacketSplitFunction(SplitFunctionType SplitFunction);

                void SetPacketDispatcherFunction(DispatcherFunctionType DispatcherFunction);
            private:                
                Memory::AutoPointer<PIMPL> m_Data;
        };
    }
}

#endif // RF_NET_PACKETSTREAM_HPP