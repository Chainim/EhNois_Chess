#include <stdio.h>
#include "network.h"

int main()
{
	network_init();
	SOCKET servidor;
	connect(servidor, "127.0.0.1", 7777);

	char recebe_lado;
	recv_all(servidor, &recebe_lado, 1);

	printf("lado %c\n",recebe_lado);

	network_shutdown();
}