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

void connect(SOCKET &s, const char *ip, unsigned short port)
{
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to create socket (Error %d)\n", WSAGetLastError());
		WSACleanup(), exit(0);
	}
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	if(connect(s, (sockaddr*)(&addr), sizeof(addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to connect (Error %d)\n", WSAGetLastError());
		closesocket(s), WSACleanup(), exit(0);
	}
}

void setup_server(SOCKET &listenSocket, unsigned short port)
{
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	addr.sin_port = htons(port);

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenSocket == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to create socket (Error %d)\n", WSAGetLastError());
		WSACleanup(), exit(0);
	}

	if(bind(listenSocket, (sockaddr*)(&addr), sizeof(addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to bind socket (Error %d)\n", WSAGetLastError());
		closesocket(listenSocket), WSACleanup(), exit(0);
	}
	if(listen(listenSocket, 2) == SOCKET_ERROR)
	{
		fprintf(stderr, "Failed to listen to socket (Error %d)\n", WSAGetLastError());
		closesocket(listenSocket), WSACleanup(), exit(0);
	}
}