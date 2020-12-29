#include <stdio.h>
#include "network.h"

int main()
{
	network_init();
	SOCKET listen_socket, client1, client2;
	setup_server(listen_socket, 7777);
	client1 = accept(listen_socket, nullptr, nullptr);
	client2 = accept(listen_socket, nullptr, nullptr);

	char decide_lado = '1';
	send_all(client1, &decide_lado, 1);
	decide_lado = '2';
	send_all(client2, &decide_lado, 1);

	network_shutdown();
}