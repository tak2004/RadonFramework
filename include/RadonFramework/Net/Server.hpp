#ifndef RF_NET_SERVER_HPP
#define RF_NET_SERVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
    namespace Net
    {
        class PIMPL;
        class ServerConfiguration;

        class Server
        {
            public:
                /// Error codes which can be returned by the public API.
                enum Error
                {
                    Ok,
                    TimedOut
                };

                /** Exchange the configuration of the server. If the server
                  * is allready running then the new configuration will be dropped.
                  **/
                static Memory::AutoPointer<Server> Create(const ServerConfiguration& Config);

                /// Setup and start the server.
                void Start();

                /// The server will be forced to stop and cancel all pending requests.
                void Stop();

                /** The server will be deny new incomming request, process
                  * all pending requests and shutdown after this. If the
                  * ReturnAfter parameter is greater 0 then the Shutdown
                  * method will return after waiting for the given time.
                  * If the method take longer as the ReturnAfter time then
                  * TimedOut will be returned else Ok.
                  **/
                Error Shutdown(const Time::TimeSpan& ReturnAfter);

                /// Return the configuration from the server.
                const ServerConfiguration& Configuration()const;
            protected:
                PIMPL* m_Data;
        };
    }
}

#endif // RF_NET_SERVER_HPP
