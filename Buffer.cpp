
#include "Buffer.hpp"

#include <cstring>

using namespace std;
using namespace com::toxiclabs::network;

Buffer::Buffer()
{
}

Buffer::Buffer(int size,char * data)
{
	this->size=size;
	this->data=data;
	
	char * ptr = new char[size];
	
	std::memcpy(ptr,data,size);
	
	Buffer::ptrs.insert(ptr);
	
}

Buffer::Buffer(string & str)
{
	Buffer(str.size(),str.c_str());
}

Buffer::~Buffer()
{
}

void Buffer::Free()
{
	Buffer::ptrs.erase(Buffer::ptrs.find(this->data));
	delete this->data;
}
