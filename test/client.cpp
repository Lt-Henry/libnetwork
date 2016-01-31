
#include "Client.hpp"
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


class TestClient: public Client
{
	public:


	void OnError(std::string message)
	{
		cout<<message<<endl;
	}
};

int main()
{
	int n=0;

	cout<<"client test"<<endl;

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, nullptr);

	TestClient client;

	client.Connect("127.0.0.1",9009);

	while(!quit_request)
	{
		string msg="Data packet ["+to_string(n)+"]";
		Buffer buffer(msg);
		client.Write(buffer);
		n++;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	client.Disconnect();


	return 0;
}
