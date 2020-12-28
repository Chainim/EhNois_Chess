#include "network.h"
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>

void network_init()
{
	WSADATA wsaD;
	if(WSAStartup(MAKEWORD(2, 2), &wsaD))
	{
		fprintf(stderr, "WSAStartup failed\n");
		return 0;
	}
}

void network_shutdown()
{
	
}

void connect()
{

}