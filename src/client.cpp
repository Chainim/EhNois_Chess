#include <stdio.h>
#include "network.h"

int main()
{
	network_init();
	SOCKET servidor;
	connect(servidor, "127.0.0.1", 7777);

	network_shutdown();
}