#ifndef RF_SOCKETSHUTDOWN_HPP
#define RF_SOCKETSHUTDOWN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Net
	{
		namespace SocketShutdown
		{
			enum Type
			{
				Send,
				Receive,
				Both,
				MAX
			};
		}
	}
}

#endif
