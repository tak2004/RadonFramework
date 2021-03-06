#ifndef RF_SOCKETOPTIONNAME_HPP
#define RF_SOCKETOPTIONNAME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net
{
enum class SocketOptionName
{
  Unset,
  Debug,
  AcceptConnection,
  ReuseAddress,
  KeepAlive,
  DontRoute,
  Broadcast,
  UseLoopback,
  Linger,
  OutOfBandInline,
  DontLinger,
  ExclusiveAddressUse,
  SendBuffer,
  ReceiveBuffer,
  SendLowWater,
  ReceiveLowWater,
  SendTimeout,
  ReceiveTimeout,
  Error,
  SocketType,
  MaxConnections,
  IPOptions,
  HeaderIncluded,
  TypeOfService,
  IPTimeToLive,
  MulticastInterface,
  MutlicastTimeToLive,
  MulticastLoopback,
  AddMembership,
  DropMembership,
  DontFragment,
  AddSourceMembership,
  DropSourceMembership,
  BlockSource,
  UnblockSource,
  PacketInformation,
  HopLimit,
  NoDelay,
  BsdUrgent,
  Expedited,
  NoChecksum,
  ChecksumCoverage,
  UpdateAcceptContext,
  UpdateConnectContext,
  ReusePort,
  MulticastHops,
  UnicastHops,
  MulticastLoopbackIPv6,
  MAX
};
}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
