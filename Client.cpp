
#include "Client.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace std;
using namespace com::toxiclabs::network;


Client::Client()
{

}

Client::~Client()
{

}

void Client::Connect(string address,int port)
{
	this->address=address;
	this->port=port;
	
	thread_init=thread(&Client::Init,this);
}

void Client::Init()
{
	struct sockaddr_in server;
	
	fd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(fd==-1)
	{
		OnError("Cannot create socket");
		
		return;
	}
	
	server.sin_addr.s_addr = inet_addr(address.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	
	if(connect(fd ,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		OnError("Failed to connect to server");
		
		return;
	}
	
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
	
	Run(fd);
}
