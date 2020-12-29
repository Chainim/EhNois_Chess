#include "network.h"
#include <stdio.h>

void network_init()
{
	WSADATA wsaD;
	if(WSAStartup(MAKEWORD(2, 2), &wsaD))
	{
		fprintf(stderr, "WSAStartup failed\n");
		exit(0);
	}
}

void network_shutdown()
{
	WSACleanup();	
}

void connect(SOCKET &server, const char *ip, unsigned short port)
{
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to create socket (Error %d)\n", WSAGetLastError());
		WSACleanup(), exit(0);
	}
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	if(connect(server, (sockaddr*)(&addr), sizeof(addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to connect (Error %d)\n", WSAGetLastError());
		closesocket(server), WSACleanup(), exit(0);
	}
}

void setup_server(SOCKET &listen_socket, unsigned short port)
{
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	addr.sin_port = htons(port);

	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listen_socket == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to create socket (Error %d)\n", WSAGetLastError());
		WSACleanup(), exit(0);
	}

	if(bind(listen_socket, (sockaddr*)(&addr), sizeof(addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to bind socket (Error %d)\n", WSAGetLastError());
		closesocket(listen_socket), WSACleanup(), exit(0);
	}
	if(listen(listen_socket, 2) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to listen (Error %d)\n", WSAGetLastError());
		closesocket(listen_socket), WSACleanup(), exit(0);
	}
}

void recv_all(SOCKET &socket, char *buff, int len)
{
	int total_read = 0, read;
	while(total_read < len)
	{
		read = recv(socket, buff + total_read, len - total_read, 0);
		if(read == SOCKET_ERROR)
		{
			fprintf(stderr, "Error ocurred while receiving (Error %d)\n", WSAGetLastError());
			return;
		}
		total_read += read;
	}
}

void send_all(SOCKET &socket, const char *buff, int len)
{
	int total_sent = 0, sent = 0;
	while(total_sent < len)
	{
		sent = send(socket, buff + total_sent, len - total_sent, 0);
		if(sent == SOCKET_ERROR)
		{
			fprintf(stderr, "Error ocurred while sending (Error %d)\n", WSAGetLastError());
			return;
		}
		total_sent += sent;
	}
}