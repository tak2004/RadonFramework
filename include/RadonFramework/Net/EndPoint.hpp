#ifndef RF_ENDPOINT_HPP
#define RF_ENDPOINT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
	 namespace Net
	 {
		class EndPoint
		{
			public:
				EndPoint();
				EndPoint(const IPAddress &Addr, unsigned int Port=0);
				const RF_Type::String ToString()const;
				const IPAddress& Address()const;
				void Address(const IPAddress &Value);
				unsigned int Port()const;
				void Port(unsigned int Value);
				bool operator==(const EndPoint &Other);
			protected:
				IPAddress m_IP;
				unsigned short int m_Port;
		};
	 }
}

#endif
