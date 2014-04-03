#ifndef RF_NET_ERROR_HPP
#define RF_NET_ERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Net
    {
        namespace Error
        {
            enum Type
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
        };   
    }
}

#endif // RF_NET_ERROR_HPP