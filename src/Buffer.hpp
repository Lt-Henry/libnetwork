
#ifndef _LIBNETWORK_BUFFER_
#define _LIBNETWORK_BUFFER_

#include <set>
#include <string>

namespace com
{
	namespace toxiclabs
	{
		namespace network
		{
			class Buffer
			{
				private:
				
				static std::set<char *> ptrs;
				
				int size;
				char * data;
				
				public:
				
				/*!
				 Creates an empty Buffer.
				*/
				Buffer();
				
				/*!
				 Creates a Buffer and copy data.
				 Data can be freed after that.
				*/
				Buffer(char * data,int size);
				
				/*!
				 Creates a Buffer and stores a string.
				*/
				Buffer(std::string & str);
				
				/*!
				 Destroys Buffer, but data is only freed if Free() is called.
				*/
				~Buffer();
				
				/*!
					Free Buffer data.
				*/
				void Free();
				
				/*!
				 Gets data size.
				*/
				int Size();
				
				/*!
				 Gets data pointer.
				*/
				char * Data();
			};
		}
	}
}

#endif
