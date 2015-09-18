
#ifndef _LIBNETWORK_BUFFER_
#define _LIBNETWORK_BUFFER_

#include <set>

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
				
				public:
				
				int id;
				int size;
				char * data;
				
				Buffer();
				Buffer(int size,char * data);
				~Buffer();
				
				void Free()
			};
		}
	}
}

#endif
