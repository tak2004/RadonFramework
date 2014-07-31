#ifndef RF_SOCKETTYPE_HPP
#define RF_SOCKETTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Net {

enum class SocketType
{
	Datagram,//UDP
	Stream,//TCP
	Raw,
	None,
	MAX
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
