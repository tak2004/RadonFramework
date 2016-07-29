#ifndef RF_NET_PACKETSTREAM_HPP
#define RF_NET_PACKETSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>

class PIMPL;

namespace RadonFramework { namespace IO { class MemoryCollectionStream; } }

namespace RadonFramework { namespace Net { 

template<typename T>
class NetworkStream;

enum class StreamStatus
{
    ThrowAway,// will be discard the whole packet from the stream
    Dispatch// remove the packet from the stream and dispatch it
};

class PacketStream
{
public:
    PacketStream();

    void Enqueue(RF_Mem::AutoPointerArray<RF_Type::UInt8>& packet);
    RF_Mem::AutoPointerArray<RF_Type::UInt8> DequeueResponse();

    void MaxDataSize(const RF_Type::UInt32 NewSize);
    RF_Type::UInt32 MaxDataSize()const;

    /** Every incoming message will be processed by this method and depending on 
    * the outcome Dispatch will be called or the packet will be discarded.
    * If the protocol allows early validation you can run a short validation and
    * do the heavy work in Dispatch.
    **/
    virtual StreamStatus Process(NetworkStream<IO::MemoryCollectionStream>& Stream);
    /// This method will be called if the Process method requested dispatching.
    virtual void Dispatch(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Packet);

    RF_Pattern::Signal OnResponse;
protected:
    void SendResponse(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Packet);
private:                
    RF_Mem::AutoPointer<PIMPL> m_Data;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_PACKETSTREAM_HPP