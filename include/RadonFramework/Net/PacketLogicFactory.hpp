#ifndef RF_NET_PACKETLOGICFACTORY_HPP
#define RF_NET_PACKETLOGICFACTORY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net {

class PacketStream;

struct PacketLogicFactory
{
    virtual RF_Mem::AutoPointer<PacketStream> Generate() = 0;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif