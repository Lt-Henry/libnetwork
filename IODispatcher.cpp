
#include "IODispatcher.hpp"

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


void IODispatcher::Run(int fd,int timeout)
{
	this->fd=fd;
	this->timeout=timeout;
	
	quit_request=false;
	
	thread_rx = thread(&IODispatcher::Rx,this);
	thread_tx = thread(&IODispatcher::Tx,this);
}

void IODispatcher::Stop()
{
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
	int data_length;
	int watchdog=0;
	
	while(!quit_request)
	{
		data_length = recv(fd,data,2048,0);
		
		if(data_length>0)
		{
			Buffer buffer(0,data_length,data);
			
			mutex_rx.lock();
			
			queue_rx.push(buffer);
			
			mutex_rx.unlock();
			
			watchdog=0;
			
			OnDataAvailable();
			
		}
		else
		{
			if(errno==EWOULDBLOCK)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				watchdog+=10;
			}
			else
			{
				OnError("Failed to read from fd");
			}
		}
		
		if(watchdog>timeout)
		{
			OnError("Connection timeout");
		}
	}
}

void IODispatcher::Tx()
{
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
			if(send(fd,buffer.data,buffer.size,0)<0)
			{
				OnError("Failed to write on fd");
			}
			else
			{
				OnWrite();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}
