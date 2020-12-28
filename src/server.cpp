#include <stdio.h>
#include "network.h"

int main()
{
	network_init();
	SOCKET listen_socket, client1, client2;
	setup_server(listen_socket, 7777);
	client1 = accept(listen_socket, nullptr, nullptr);
	client2 = accept(listen_socket, nullptr, nullptr);

	network_shutdown();
}