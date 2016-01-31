
#ifndef _LIBNETWORK_IODISPATCHER_
#define _LIBNETWORK_IODISPATCHER_

#include <string>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>

#include "Buffer.hpp"

namespace com
{
	namespace toxiclabs
	{
		namespace network
		{
			class IODispatcher
			{
			
				private:
				
				int fd;
				
				bool quit_request;
				
				std::thread thread_rx;
				std::thread thread_tx;
				
				std::mutex mutex_rx;
				std::mutex mutex_tx;
				
				std::queue<Buffer> queue_rx;
				std::queue<Buffer> queue_tx;
				
				void Rx();
				void Tx();
				
				
			
				public:
				
				IODispatcher();
				virtual ~IODispatcher();
				
				void Run(int fd);
				void Disconnect();
				
				void Write(Buffer buffer);
				Buffer Read();
				
				virtual void OnWrite();
				virtual void OnDataAvailable();
				
				virtual void OnError(std::string message);
			};
		}
	}
}

#endif
