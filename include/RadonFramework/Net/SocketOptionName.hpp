#ifndef RF_SOCKETOPTIONNAME_HPP
#define RF_SOCKETOPTIONNAME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Net
	{
		namespace SocketOptionName
		{
			enum Type
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
				MAX
			};
		}
	}
}

#endif
