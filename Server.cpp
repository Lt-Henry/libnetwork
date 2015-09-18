

#include "Server.hpp"

#include <stdexcept>

using namespace std;
using namespace com::toxiclabs::network;


Server::Server()
{

}

Server::~Server()
{

}


void Server::Listen(int port,int connections)
{
	this->port=port;
	this->connections=connections;
	
	thread_run=thread(&Server::Run,this);
}

void Server::OnAccept(int fd)
{

}

void Server::OnDataAvailable(Child * child)
{

}

void Server::Run()
{
	int socket_fd,client_fd;
	socklen_t cli_len;
	struct sockaddr_in server, client;

	socket_fd = socket(AF_INET , SOCK_STREAM , 0);
	if(socket_fd==-1)
		throw runtime_error("Could not create socket");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	if(bind(socket_fd,(struct sockaddr *)&server,sizeof(server)) < 0)
		throw runtime_error("Bind failed");
		
	listen(socket_fd , connections);
	cli_len=sizeof(client);
		
	while(!quit_request)
	{
		client_fd=accept(socket_fd,(struct sockaddr *) &client,&cli_len);
		OnAccept(client_fd);
		
		fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK);
		
		children[client_fd]=new Child(this);
		children[client_fd]->Run(client_fd);
		
	}
}


/* CHILD */

Child::Child(Server * server)
{
	this->server=server;
}

void Child::OnDataAvailable()
{
	server->OnDataAvailable(this);
}
