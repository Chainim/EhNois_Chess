#include <stdio.h>
#include "network.h"

int main()
{
	network_init();
	SOCKET servidor;
	connect(servidor, "127.0.0.1", 7777);

	char recebe_lado;
	recebe_lado = '0';
	recv(servidor,&recebe_lado,1,0);

	printf("lado %c\n",recebe_lado);

	network_shutdown();
}