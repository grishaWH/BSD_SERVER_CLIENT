#include "../includes/includes.h"
#include "../includes/profiler.h"

int main()
{
	//-----------TEST-FILE-------------
	uint8_t file[SIZE_FILE + 1];
	uint8_t id[NUM_BYTE_ID + 1];
	file[SIZE_FILE] = 0;
	id[NUM_BYTE_ID] = 0;
	memset(file, '8', SIZE_FILE);
	memset(id, '1', NUM_BYTE_ID);
	//----------------------------------

	{LOG_DURATION("TEST_1")
		Client client(AF_INET, IP, PORT);
		client.start(id, file);
	}
	return 0;
}