#ifndef RF_SOCKETTYPE_HPP
#define RF_SOCKETTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Net
	{
		namespace SocketType
		{
			enum Type
			{
				Datagram,//UDP
				Stream,//TCP
				Raw,
				None,
				MAX
			};
		}
	}
}

#endif
