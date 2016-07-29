#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/PacketStream.hpp"
#include "RadonFramework/IO/MemoryCollectionStream.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Net/NetworkStream.hpp"
#include "RadonFramework/Net/SessionServer.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;
using namespace RadonFramework::Threading;

class PIMPL
{
public:
    RF_Net::NetworkStream<RF_IO::MemoryCollectionStream> MemoryStream;
    RF_Collect::List<RF_Mem::AutoPointerArray<RF_Type::UInt8>> ResponseList;
    UInt32 MaxDataSize;
};

namespace RadonFramework { namespace Net {

PacketStream::PacketStream()
{
    m_Data=AutoPointer<PIMPL>(new PIMPL);
    m_Data->MaxDataSize=104857600;// 100MB
}

void PacketStream::Enqueue(AutoPointerArray<UInt8>& packet)
{
    m_Data->MemoryStream.AddLast(packet);

    RF_Type::UInt64 bytes = 0;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> buffer;

    StreamStatus status;
    do
    {
        status = Process(m_Data->MemoryStream);
        switch(status)
        {
        case StreamStatus::ThrowAway:
            m_Data->MemoryStream.RemoveFirst();
            break;
        case StreamStatus::Dispatch:
            bytes = m_Data->MemoryStream.Position();
            m_Data->MemoryStream.Seek(0, SeekOrigin::Begin);
            buffer = RF_Mem::AutoPointerArray<RF_Type::UInt8>(bytes);
            m_Data->MemoryStream.Read(buffer.Get(), 0, bytes);
            m_Data->MemoryStream.RemoveBefore();
            Dispatch(buffer);
            break;
        }
    } while(m_Data->MemoryStream.Count() > 0);

    while(m_Data->MemoryStream.Length() > m_Data->MaxDataSize)
        m_Data->MemoryStream.RemoveFirst();
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> PacketStream::DequeueResponse()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if(m_Data->ResponseList.IsEmpty() == false)
    {
        result = m_Data->ResponseList[0];
        m_Data->ResponseList.RemoveFirst();
    }
    return result;
}

StreamStatus PacketStream::Process(NetworkStream<IO::MemoryCollectionStream>& Stream)
{
    StreamStatus result = StreamStatus::ThrowAway;
    return result;
}

void PacketStream::Dispatch(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Packet)
{

}

void PacketStream::SendResponse(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Packet)
{
    m_Data->ResponseList.AddLast(Packet);
    OnResponse();
}

void PacketStream::MaxDataSize(const UInt32 NewSize)
{
    m_Data->MaxDataSize=NewSize;
}

UInt32 PacketStream::MaxDataSize()const
{
    return m_Data->MaxDataSize;
}

} }
