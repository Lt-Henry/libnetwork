
#include "Server.hpp"
#include <signal.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace com::toxiclabs::network;


bool quit_request=false;

void handler(int s){
	quit_request=true;
}



class TestServer: public Server
{
	public:



	void OnAccept(int fd)
	{
		cout<<"Incoming client from fd:"<<fd<<endl;
	}

	void OnDataAvailable(Child * child)
	{
		Buffer buffer = child->Read();

		cout<<"Data: "<<buffer.Data()<<endl;

		buffer.Free();

	}
};

int main()
{
	cout<<"server test"<<endl;

	TestServer server;

	server.Listen(9009,4);

	while(!quit_request)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	server.Disconnect();

	return 0;
}
