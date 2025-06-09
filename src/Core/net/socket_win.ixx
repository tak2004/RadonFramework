module;
/** Define WINVER and NT Version to WIN_VERSION_XP.
  * GetAdaptersInfo is available since windows xp(NT Kernel 501).
  * To be sure that all the cool features of windows API are available it's
  * necessary to define windows xp as minimum API.
  **/
static const int WIN_VERSION_XP = 0x501;
#define WINVER 0x501
#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdlib.h>
export module rf.core.net:socket_win;
import :socket;
import rf.core.memory;

export namespace rf {

SocketError ConvertOSError(i32 Code) {
  switch (Code) {
  case WSAEINTR:
      return { SocketError::Error::Interrupted };
  case WSAEACCES:
      return { SocketError::Error::PermissionDenied };
  case WSAEFAULT:
      return { SocketError::Error::BadAddress };
  case WSAEINVAL:
      return { SocketError::Error::InvalidArgument };
  case WSAEMFILE:
      return { SocketError::Error::TooManyOpenFiles };
  case WSAEWOULDBLOCK:
      return { SocketError::Error::WouldBlock };
  case WSAEINPROGRESS:
      return { SocketError::Error::InProgress };
  case WSAEALREADY:
      return { SocketError::Error::AlreadyInProgress };
  case WSAENOTSOCK:
      return { SocketError::Error::NotASocket };
  case WSAEDESTADDRREQ:
      return { SocketError::Error::DestinationAddressRequired };
  case WSAEMSGSIZE:
      return { SocketError::Error::MessageTooLong };
  case WSAEPROTOTYPE:
      return { SocketError::Error::InvalidProtocol };
  case WSAENOPROTOOPT:
      return { SocketError::Error::BadProtocolOption };
  case WSAEPROTONOSUPPORT:
      return { SocketError::Error::ProtocolNotSupported };
  case WSAESOCKTNOSUPPORT:
      return { SocketError::Error::SocketTypeNotSupported };
  case WSAEOPNOTSUPP:
      return { SocketError::Error::OperationNotSupported };
  case WSAEPFNOSUPPORT:
      return { SocketError::Error::ProtocolFamilyNotSupported };
  case WSAEAFNOSUPPORT:
      return { SocketError::Error::AddressFamilyNotSupported };
  case WSAEADDRINUSE:
      return { SocketError::Error::AddressInUse };
  case WSAEADDRNOTAVAIL:
      return { SocketError::Error::AddressNotAvailable };
  case WSAENETDOWN:
      return { SocketError::Error::NetworkDown };
  case WSAENETUNREACH:
      return { SocketError::Error::NetworkUnreachable };
  case WSAENETRESET:
      return { SocketError::Error::NetworkReset };
  case WSAECONNABORTED:
      return { SocketError::Error::ConnectionAborted };
  case WSAECONNRESET:
      return { SocketError::Error::ConnectionReset };
  case WSAENOBUFS:
      return { SocketError::Error::NoBufferSpace };
  case WSAEISCONN:
      return { SocketError::Error::IsConnected };
  case WSAENOTCONN:
      return { SocketError::Error::NotConnected };
  case WSAESHUTDOWN:
      return { SocketError::Error::IsShutdown };
  case WSAETIMEDOUT:
      return { SocketError::Error::IsTimedOut };
  case WSAECONNREFUSED:
      return { SocketError::Error::ConnectionRefused };
  case WSAEHOSTDOWN:
      return { SocketError::Error::HostDown };
  case WSAEHOSTUNREACH:
      return { SocketError::Error::HostUnreachable };
  case WSAEPROCLIM:
      return { SocketError::Error::TooManyProcesses };
  case WSASYSNOTREADY:
      return { SocketError::Error::SystemNotReady };
  case WSAVERNOTSUPPORTED:
      return { SocketError::Error::VersionNotSupported };
  case WSANOTINITIALISED:
      return { SocketError::Error::NotInitialized };
  case WSAEDISCON:
      return { SocketError::Error::Disconnecting };
  case WSATYPE_NOT_FOUND:
      return { SocketError::Error::TypeNotFound };
  case WSAHOST_NOT_FOUND:
      return { SocketError::Error::HostNotFound };
  case WSATRY_AGAIN:
      return { SocketError::Error::TryAgain };
  case WSANO_RECOVERY:
      return { SocketError::Error::NoRecovery };
  case WSANO_DATA:
      return { SocketError::Error::NoData };
  default:
      return { SocketError::Error::InternalError };
  }
}

NetworkAPIContext::NetworkAPIContext(AllocatorAdapter LongLiving, StackAdapter Stack)
:allocator(LongLiving), stack(Stack), interfaces(LongLiving), tcpSockets(LongLiving),
udpSockets(LongLiving), processSockets(LongLiving)
{
}

NetworkAPIContext::~NetworkAPIContext()
{
    this->stop();
}

SocketError NetworkAPIContext::start() {
  this->handle = this->allocator.allocate(sizeof(WSADATA));
  auto *winsock = reinterpret_cast<WSADATA *>(this->handle.address);
  i32 err = WSAStartup(MAKEWORD(2, 2), winsock);
  if (err == 0)
      return { SocketError::Error::Ok };
  else
    return ConvertOSError(err);
}

SocketError NetworkAPIContext::stop() {
    SocketError result = { SocketError::Error::Ok };
    if (this->handle.address) {
        i32 err = WSACleanup();
        this->allocator.deallocate(this->handle);
        if (err != 0)
            result = ConvertOSError(err);
    }
    return result;
}

void NetworkAPIContext::updateInterfaces() {
  u32 family = AF_UNSPEC;
  u32 flags = GAA_FLAG_INCLUDE_PREFIX;
  ULONG outBufferLength = 0;
  auto returnValue =
      GetAdaptersAddresses(family, flags, nullptr, nullptr, &outBufferLength);
  auto interfaces = this->stack.push(outBufferLength);
  returnValue = GetAdaptersAddresses(family, flags, nullptr, reinterpret_cast<PIP_ADAPTER_ADDRESSES>(interfaces.address),
                                     &outBufferLength);
  if (returnValue == NO_ERROR) {
    PIP_ADAPTER_UNICAST_ADDRESS pUnicastAddress = nullptr;
    auto pCurrAddresses =
        reinterpret_cast<PIP_ADAPTER_ADDRESSES>(interfaces.address);
    // get the number of the Ethernet adapters
    while (pCurrAddresses) {
      if (pCurrAddresses->OperStatus == IfOperStatusUp) {
          auto& interface = this->interfaces.add();
          interface.nameBytesLeft = NetworkInterface::MAX_NAME_LENGTH - wcstombs((char*)interface.name, pCurrAddresses->FriendlyName, NetworkInterface::MAX_NAME_LENGTH);
          interface.MTU = pCurrAddresses->Mtu;
          switch (pCurrAddresses->PhysicalAddressLength) {
          case 8: 
              interface.MACType = MACTypes::EUI64; 
              for (auto i = 0; i < 8; i++)
                  interface.MAC[i] = pCurrAddresses->PhysicalAddress[i];
              break;
          case 6: 
              interface.MACType = MACTypes::EUI48; 
              for (auto i = 0; i < 6; i++)
                  interface.MAC[i] = pCurrAddresses->PhysicalAddress[i];
              break;
          default: interface.MACType = MACTypes::NotSet; break;
          }
          switch (pCurrAddresses->IfType) {
          case IF_TYPE_ETHERNET_CSMACD:
              interface.type = InterfaceTypes::Ethernet;
              break;
          case IF_TYPE_SOFTWARE_LOOPBACK:
              interface.type = InterfaceTypes::Loopback;
              break;
          case IF_TYPE_IEEE80211:
              interface.type = InterfaceTypes::WirelessLAN;
              break;
          default:
              interface.type = InterfaceTypes::NotSet;
              break;
          }
        //pUnicastAddress = pCurrAddresses->FirstUnicastAddress;
      }
      pCurrAddresses = pCurrAddresses->Next;
    }  
  }
}
} // namespace rf