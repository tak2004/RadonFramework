#ifndef RF_ADDRESSFAMILY_HPP
#define RF_ADDRESSFAMILY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Net
	{
		namespace AddressFamily
		{
			enum Type
			{
				InterNetwork,//IPv4
				InterNetwork6,//IPv6
				Unix,//unix domain socket(very fast, tcp base designed and for local process communication)
				None,
				MAX
			};
		}
	}
}

#endif
