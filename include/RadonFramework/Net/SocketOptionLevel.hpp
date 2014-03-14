#ifndef RF_SOCKETOPTIONLEVEL_HPP
#define RF_SOCKETOPTIONLEVEL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Net
	{
		namespace SocketOptionLevel
		{
			enum Type
			{
				Unset,
				Socket,
				IPv4,
				IPv6,
				TCP,
				UDP,
				MAX
			};
		}
	}
}

#endif
