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
				
				std::map<int,Child> children;
				
				public:
				
				Server();
				
				virtual ~Server();
				
				void Listen(int port,int connections);
			};
		
		}
	}
}
