#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Network/OSSocketError.hpp"
#include <stdlib.h>

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Network;

Error* OSSocketError::LookupTable = 0;

#if defined(RF_WINDOWS)
/** Define WINVER and NT Version to WIN_VERSION_XP.
  * GetAdaptersInfo is available since windows xp(NT Kernel 501).
  * To be sure that all the cool features of windows API are available it's
  * necessary to define windows xp as minimum API.
  **/
static const int WIN_VERSION_XP=0x501;
#define WINVER 0x501
#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#endif

#if defined(RF_UNIX)
#include <sys/errno.h>
#endif

Error OSSocketError::ConvertOSError()
{
    #if defined(RF_WINDOWS)
        int code=WSAGetLastError();
    #endif
    #if defined(RF_UNIX)
        int code=errno;
    #endif
    Assert(code >= OSSocketError::First && code < OSSocketError::Last, "No valid error code!");
    return OSSocketError::LookupTable[code-OSSocketError::First];
}

Error OSSocketError::ConvertOSError(const Int32 Code)
{
    Assert(Code >= OSSocketError::First && Code < OSSocketError::Last, "No valid error code!");
    return OSSocketError::LookupTable[Code-OSSocketError::First];
}

void CleanupOSSocketError()
{
    delete[] OSSocketError::LookupTable;
    OSSocketError::LookupTable = 0;
}

void OSSocketError::InitializeLookupTable()
{
    OSSocketError::LookupTable = new Net::Error[Range];
    atexit(CleanupOSSocketError);
    #if defined(RF_WINDOWS)
        OSSocketError::LookupTable[WSAEINTR-OSSocketError::First]=Error::Interrupted;
        OSSocketError::LookupTable[WSAEACCES-OSSocketError::First]=Error::PermissionDenied;
        OSSocketError::LookupTable[WSAEFAULT-OSSocketError::First]=Error::BadAddress;
        OSSocketError::LookupTable[WSAEINVAL-OSSocketError::First]=Error::InvalidArgument;
        OSSocketError::LookupTable[WSAEMFILE-OSSocketError::First]=Error::TooManyOpenFiles;
        OSSocketError::LookupTable[WSAEWOULDBLOCK-OSSocketError::First]=Error::WouldBlock;
        OSSocketError::LookupTable[WSAEINPROGRESS-OSSocketError::First]=Error::InProgress;
        OSSocketError::LookupTable[WSAEALREADY-OSSocketError::First]=Error::AlreadyInProgress;
        OSSocketError::LookupTable[WSAENOTSOCK-OSSocketError::First]=Error::NotASocket;
        OSSocketError::LookupTable[WSAEDESTADDRREQ-OSSocketError::First]=Error::DestinationAddressRequired;
        OSSocketError::LookupTable[WSAEMSGSIZE-OSSocketError::First]=Error::MessageTooLong;
        OSSocketError::LookupTable[WSAEPROTOTYPE-OSSocketError::First]=Error::InvalidProtocol;
        OSSocketError::LookupTable[WSAENOPROTOOPT-OSSocketError::First]=Error::BadProtocolOption;
        OSSocketError::LookupTable[WSAEPROTONOSUPPORT-OSSocketError::First]=Error::ProtocolNotSupported;
        OSSocketError::LookupTable[WSAESOCKTNOSUPPORT-OSSocketError::First]=Error::SocketTypeNotSupported;
        OSSocketError::LookupTable[WSAEOPNOTSUPP-OSSocketError::First]=Error::OperationNotSupported;
        OSSocketError::LookupTable[WSAEPFNOSUPPORT-OSSocketError::First]=Error::ProtocolFamilyNotSupported;
        OSSocketError::LookupTable[WSAEAFNOSUPPORT-OSSocketError::First]=Error::AddressFamilyNotSupported;
        OSSocketError::LookupTable[WSAEADDRINUSE-OSSocketError::First]=Error::AddressInUse;
        OSSocketError::LookupTable[WSAEADDRNOTAVAIL-OSSocketError::First]=Error::AddressNotAvailable;
        OSSocketError::LookupTable[WSAENETDOWN-OSSocketError::First]=Error::NetworkDown;      
        OSSocketError::LookupTable[WSAENETUNREACH-OSSocketError::First]=Error::NetworkUnreachable;
        OSSocketError::LookupTable[WSAENETRESET-OSSocketError::First]=Error::NetworkReset;
        OSSocketError::LookupTable[WSAECONNABORTED-OSSocketError::First]=Error::ConnectionAborted;
        OSSocketError::LookupTable[WSAECONNRESET-OSSocketError::First]=Error::ConnectionReset;
        OSSocketError::LookupTable[WSAENOBUFS-OSSocketError::First]=Error::NoBufferSpace;
        OSSocketError::LookupTable[WSAEISCONN-OSSocketError::First]=Error::IsConnected;
        OSSocketError::LookupTable[WSAENOTCONN-OSSocketError::First]=Error::NotConnected;
        OSSocketError::LookupTable[WSAESHUTDOWN-OSSocketError::First]=Error::IsShutdown;
        OSSocketError::LookupTable[WSAETIMEDOUT-OSSocketError::First]=Error::IsTimedOut;
        OSSocketError::LookupTable[WSAECONNREFUSED-OSSocketError::First]=Error::ConnectionRefused;
        OSSocketError::LookupTable[WSAEHOSTDOWN-OSSocketError::First]=Error::HostDown;    
        OSSocketError::LookupTable[WSAEHOSTUNREACH-OSSocketError::First]=Error::HostUnreachable;
        OSSocketError::LookupTable[WSAEPROCLIM-OSSocketError::First]=Error::TooManyProcesses;
        OSSocketError::LookupTable[WSASYSNOTREADY-OSSocketError::First]=Error::SystemNotReady;
        OSSocketError::LookupTable[WSAVERNOTSUPPORTED-OSSocketError::First]=Error::VersionNotSupported;
        OSSocketError::LookupTable[WSANOTINITIALISED-OSSocketError::First]=Error::NotInitialized;
        OSSocketError::LookupTable[WSAEDISCON-OSSocketError::First]=Error::Disconnecting;
        OSSocketError::LookupTable[WSATYPE_NOT_FOUND-OSSocketError::First]=Error::TypeNotFound;
        OSSocketError::LookupTable[WSAHOST_NOT_FOUND-OSSocketError::First]=Error::HostNotFound;
        OSSocketError::LookupTable[WSATRY_AGAIN-OSSocketError::First]=Error::TryAgain;
        OSSocketError::LookupTable[WSANO_RECOVERY-OSSocketError::First]=Error::NoRecovery;
        OSSocketError::LookupTable[WSANO_DATA-OSSocketError::First]=Error::NoData;
    #endif

    #if defined(RF_UNIX)
        OSSocketError::LookupTable[EINTR-OSSocketError::First]=Error::Interrupted;
        OSSocketError::LookupTable[EACCES-OSSocketError::First]=Error::PermissionDenied;
        OSSocketError::LookupTable[EFAULT-OSSocketError::First]=Error::BadAddress;
        OSSocketError::LookupTable[EINVAL-OSSocketError::First]=Error::InvalidArgument;
        OSSocketError::LookupTable[EMFILE-OSSocketError::First]=Error::TooManyOpenFiles;
        OSSocketError::LookupTable[EWOULDBLOCK-OSSocketError::First]=Error::WouldBlock;
        OSSocketError::LookupTable[EINPROGRESS-OSSocketError::First]=Error::InProgress;
        OSSocketError::LookupTable[EALREADY-OSSocketError::First]=Error::AlreadyInProgress;
        OSSocketError::LookupTable[ENOTSOCK-OSSocketError::First]=Error::NotASocket;
        OSSocketError::LookupTable[EDESTADDRREQ-OSSocketError::First]=Error::DestinationAddressRequired;
        OSSocketError::LookupTable[EMSGSIZE-OSSocketError::First]=Error::MessageTooLong;
        OSSocketError::LookupTable[EPROTOTYPE-OSSocketError::First]=Error::InvalidProtocol;
        OSSocketError::LookupTable[ENOPROTOOPT-OSSocketError::First]=Error::BadProtocolOption;
        OSSocketError::LookupTable[EPROTONOSUPPORT-OSSocketError::First]=Error::ProtocolNotSupported;
        OSSocketError::LookupTable[ESOCKTNOSUPPORT-OSSocketError::First]=Error::SocketTypeNotSupported;
        OSSocketError::LookupTable[EOPNOTSUPP-OSSocketError::First]=Error::OperationNotSupported;
        OSSocketError::LookupTable[EPFNOSUPPORT-OSSocketError::First]=Error::ProtocolFamilyNotSupported;
        OSSocketError::LookupTable[EAFNOSUPPORT-OSSocketError::First]=Error::AddressFamilyNotSupported;
        OSSocketError::LookupTable[EADDRINUSE-OSSocketError::First]=Error::AddressInUse;
        OSSocketError::LookupTable[EADDRNOTAVAIL-OSSocketError::First]=Error::AddressNotAvailable;
        OSSocketError::LookupTable[ENETDOWN-OSSocketError::First]=Error::NetworkDown;
        OSSocketError::LookupTable[ENETUNREACH-OSSocketError::First]=Error::NetworkUnreachable;
        OSSocketError::LookupTable[ENETRESET-OSSocketError::First]=Error::NetworkReset;
        OSSocketError::LookupTable[ECONNABORTED-OSSocketError::First]=Error::ConnectionAborted;
        OSSocketError::LookupTable[ECONNRESET-OSSocketError::First]=Error::ConnectionReset;
        OSSocketError::LookupTable[ENOBUFS-OSSocketError::First]=Error::NoBufferSpace;
        OSSocketError::LookupTable[EISCONN-OSSocketError::First]=Error::IsConnected;
        OSSocketError::LookupTable[ENOTCONN-OSSocketError::First]=Error::NotConnected;
        OSSocketError::LookupTable[ESHUTDOWN-OSSocketError::First]=Error::IsShutdown;
        OSSocketError::LookupTable[ETIMEDOUT-OSSocketError::First]=Error::IsTimedOut;
        OSSocketError::LookupTable[ECONNREFUSED-OSSocketError::First]=Error::ConnectionRefused;
        OSSocketError::LookupTable[EHOSTDOWN-OSSocketError::First]=Error::HostDown;
        OSSocketError::LookupTable[EHOSTUNREACH-OSSocketError::First]=Error::HostUnreachable;
    #endif
}