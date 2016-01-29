#ifndef _LIBNETWORK_SERVER_
#define _LIBNETWORK_SERVER_

#include "Buffer.hpp"
#include "IODispatcher.hpp"

#include <string>
#include <thread>
#include <map>

namespace com
{
	namespace toxiclabs
	{
		namespace network
		{
			class Child;
			
			class Server
			{
				private:
				
				bool quit_request;
				int port;
				int connections;
				
				std::map<int,Child *> children;
				
				std::thread thread_run;
				
				void Run();
				
				public:
				
				Server();
				
				virtual ~Server();
				
				/*!
				 Listen for incoming connections.
				 Non-blocking function.
				*/
				void Listen(int port,int connections);
				
				/*!
				 Disconnect childs
				*/
				void Disconnect();
				
				/*!
				 Fired when a new connection is stablished
				*/
				virtual void OnAccept(int fd);
				
				/*!
				 Fired when new data is ready to read
				*/
				virtual void OnDataAvailable(Child * child);
			};
			
			class Child : public IODispatcher
			{
				private:
				

				Server * server;
				
				public:
				
				Child(Server * server);
				
				void OnDataAvailable();
			};
		
		}
	}
}

#endif
