
#ifndef _LIBNETWORK_BUFFER_
#define _LIBNETWORK_BUFFER_

namespace com
{
	namespace toxiclabs
	{
		namespace network
		{
			class Buffer
			{
				
				public:
				
				int id;
				int size;
				char * data;
				
				Buffer();
				Buffer(int id,int size,char * data);
				~Buffer();
			};
		}
	}
}

#endif
