

#include "Server.hpp"

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
}


void Server::Run()
{

}
