export module rf.core.net:socket;
import rf.core.types;
import rf.core.memory;
import rf.core.cpu;
import rf.core.collections;

export namespace rf {
using SocketHandler = void *;

enum class AddressFamily : u8 { Unknown, IPv4, IPv6, ProcessPath };

struct IPAddress {
  union {
    u8 v4[4];
    u8 v6[16];
  };
  AddressFamily family;
  u8 cidr;
};

struct EndPoint {
  IPAddress address;
  u16 port;
};

struct SocketError {
  enum class Error : u8 {
    InternalError = 0,
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
  } code;
  operator bool() { return this->code == Error::Ok; }
};

class TCPSocket {
public:
  SocketError Accept();
  SocketError Bind();
  SocketError Connect();
  SocketError Disconnect();
  SocketError Listen();

  SocketError Receive();
  SocketError Send();

  SocketError AttachToPool();
  SocketError DetachFromPool();

  SocketHandler handler;
  EndPoint endPoint;
  bool blocking;
};

class UDPSocket {
public:
  SocketError Listen();
  SocketError ReceiveFrom();
  SocketError SendTo();

  SocketHandler handler;
  EndPoint endPoint;
};

class ProcessSocket {
public:
  SocketHandler handler;
  u8 path[108];
};

enum class MACTypes:u8 {
    NotSet=0,
    EUI48,
    EUI64
};

enum class InterfaceTypes :u8 {
    NotSet=0,
    WirelessLAN,
    Loopback,
    Ethernet
};

struct NetworkInterface {
    constexpr static u8 MAX_NAME_LENGTH = 49;

    utf8 name[MAX_NAME_LENGTH];
    u8 nameBytesLeft= MAX_NAME_LENGTH;
    InterfaceTypes type;
    MACTypes MACType;
    u8 MAC[8];
    u32 MTU;

    u8 nameLegth() const { return MAX_NAME_LENGTH - nameBytesLeft; }
};

class NetworkAPIContext {
public:
    NetworkAPIContext(AllocatorAdapter LongLiving, StackAdapter Stack);
    ~NetworkAPIContext();
    SocketError start();
    SocketError stop();
    void updateInterfaces();
    Pool<NetworkInterface> interfaces;
    Pool<TCPSocket> tcpSockets;
    Pool<UDPSocket> udpSockets;
    Pool<ProcessSocket> processSockets;
protected:
    AllocatorAdapter allocator;
    StackAdapter stack;
    mem handle;// System specific handle
};
/*
struct AddressConverter {
  static bool GetBroadCastAddress(const IPAddress &IP, u8 NetMask,
    IPAddress &Out);
static bool GetNetworkIPAddress(const IPAddress &IP, u8 NetMask,
    IPAddress &Out);
static bool IsInSameSubnet(const IPAddress &IP1, const IPAddress &IP2,
u8 NetMask);
static bool IsPrivateNetworkIPAddress(const IPAddress &IP);
static IPAddress ip4Any;
static IPAddress ip4Loopback;
static IPAddress ip4None;
static IPAddress ip6Any;
static IPAddress ip6Loopback;
static IPAddress ip6None;

IPAddress &operator=(const IPAddress &Copy);
bool operator==(const IPAddress &Other);

  template <class T, int N>
  static bool IsValid(const basictypes::StringLiteral<T, N> Text,
                      const AddressFamily Type = AddressFamily::Unknown);
  template <class T, int N>
  static bool Resolve(const basictypes::StringLiteral<T, N> Text,
                      IPAddress &ResolvedAddress,
                      const AddressFamily Type = AddressFamily::Unknown);
  template <class T, int N>
  static bool ResolveIP6Hybrid(const basictypes::StringLiteral<T, N> Text,
                               IPAddress &ResolvedAddress);
};*/
} // namespace rf