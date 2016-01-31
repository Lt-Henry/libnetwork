
#include "IODispatcher.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;
using namespace com::toxiclabs::network;


IODispatcher::IODispatcher()
{

}

IODispatcher::~IODispatcher()
{

}


void IODispatcher::Run(int fd)
{
	this->fd=fd;

	quit_request=false;

	thread_rx = thread(&IODispatcher::Rx,this);
	thread_tx = thread(&IODispatcher::Tx,this);
}

void IODispatcher::Disconnect()
{

	close(fd);
	
	quit_request=true;

	thread_rx.join();
	thread_tx.join();
}

void IODispatcher::Write(Buffer buffer)
{
	mutex_tx.lock();
	
	queue_tx.push(buffer);
	
	mutex_tx.unlock();
}


Buffer IODispatcher::Read()
{

	Buffer buffer;
	
	mutex_rx.lock();

	buffer=queue_rx.front();
	queue_rx.pop();

	mutex_rx.unlock();
	
	return buffer;
}

void IODispatcher::OnWrite()
{

}

void IODispatcher::OnDataAvailable()
{

}

void IODispatcher::OnError(string message)
{

}


void IODispatcher::Rx()
{
	char data[2048];
	int size;

	while(!quit_request)
	{
		size=recv(fd,data,2048,0);

		if(size>0)
		{
			Buffer buffer(data,size);

			mutex_rx.lock();
			
			queue_rx.push(buffer);
			
			mutex_rx.unlock();
			
			OnDataAvailable();
		}
		else
		{
			OnError("Failed to read from fd");
		}
	}


}

void IODispatcher::Tx()
{
	int size;

	while(!quit_request)
	{

		Buffer buffer;
		bool is_tx = false;
		
		mutex_tx.lock();
		
		if(queue_tx.size()>0)
		{
			buffer = queue_tx.front();
			queue_tx.pop();
			is_tx=true;
		}
		
		mutex_tx.unlock();
		
		if(is_tx)
		{

			size=send(fd,buffer.Data(),buffer.Size(),0);

			if(size>0)
			{
				OnWrite();
				buffer.Free();
			}
			else
			{
				OnError("Failed to write on fd:"+to_string(errno));
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}
