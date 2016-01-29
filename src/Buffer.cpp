
#include "Buffer.hpp"

#include <cstring>

using namespace std;
using namespace com::toxiclabs::network;

Buffer::Buffer()
{
}

Buffer::Buffer(const char * data,int size)
{
	this->size=size;
	this->data=data;
	
	char * ptr = new char[size];
	
	std::memcpy(ptr,data,size);
	
	Buffer::ptrs.insert(ptr);
	
}

Buffer::Buffer(string & str)
{
	Buffer(str.c_str(),str.size());
}

Buffer::~Buffer()
{
}

void Buffer::Free()
{
	Buffer::ptrs.erase(Buffer::ptrs.find(this->data));
	delete this->data;
}

int Buffer::Size()
{
	return size;
}

const char * Buffer::Data()
{
	return data;
}
