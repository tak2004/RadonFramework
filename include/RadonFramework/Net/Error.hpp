#ifndef RF_NET_ERROR_HPP
#define RF_NET_ERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Net {

enum class Error
{
    InternalError=0,
    Ok,
    Interrupted,
    PermissionDenied,
    BadAddress,
    InvalidArgument,
    TooManyOpenFiles,
    WouldBlock,
    InProgress,
    AlreadyInProgress,
    NotASocket,
    DestinationAddressRequired,
    MessageTooLong,
    InvalidProtocol,
    BadProtocolOption,
    ProtocolNotSupported,
    SocketTypeNotSupported,
    OperationNotSupported,
    ProtocolFamilyNotSupported,
    AddressFamilyNotSupported,
    AddressInUse,
    AddressNotAvailable,
    NetworkDown,
    NetworkUnreachable,
    NetworkReset,
    ConnectionAborted,
    ConnectionReset,
    NoBufferSpace,
    IsConnected,
    NotConnected,
    IsShutdown,
    IsTimedOut,
    ConnectionRefused,
    HostDown,
    HostUnreachable,
    TooManyProcesses,
    SystemNotReady,
    VersionNotSupported,
    NotInitialized,
    Disconnecting,
    TypeNotFound,
    HostNotFound,
    TryAgain,
    NoRecovery,
    NoData
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_ERROR_HPP