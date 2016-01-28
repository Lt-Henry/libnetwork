
#ifndef _LIBNETWORK_CLIENT_
#define _LIBNETWORK_CLIENT_

#include "Buffer.hpp"
#include "IODispatcher.hpp"

#include <string>
#include <thread>

namespace com
{
	namespace toxiclabs
	{
		namespace network
		{
			class Client : public IODispatcher
			{
			
				private:
				
				std::string address;
				int port;
				
				int fd;
				
				std::thread thread_init;
				
				void Init();
				
				public:
				
				Client();
				virtual ~Client();
				
				void Connect(std::string address,int port);
			
			};
		}
	}
}

#endif
