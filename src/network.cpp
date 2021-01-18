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
			int err = WSAGetLastError();
			if(err != WSAEWOULDBLOCK)
			{
				fprintf(stderr, "Error ocurred while receiving (Error %d)\n", err);
				LPSTR err_str = NULL;
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, err, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&err_str, 0, NULL);
				fprintf(stderr, "Detailed error info: %s\n", err_str);
				LocalFree(err_str);
				return;
			}
		}
		else
		{
			total_read += read;
		}
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
			int err = WSAGetLastError();
			if(err != WSAEWOULDBLOCK)
			{
				fprintf(stderr, "Error ocurred while sending (Error %d)\n", err);
				LPSTR err_str = NULL;
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, err, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&err_str, 0, NULL);
				fprintf(stderr, "Detailed error info: %s\n", err_str);
				LocalFree(err_str);
				return;
			}
		}
		else
		{
			total_sent += sent;
		}
	}
}

//https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
void set_blocking(SOCKET &s, bool blocking)
{
	static unsigned long b = 0;
	static unsigned long n_b = 1;
	int ctlerror = ioctlsocket(s, FIONBIO, (blocking ? &b : &n_b));
	if(ctlerror != 0)
	{
		fprintf(stderr, "ioctlsocket (blocking) failed (Error %d)\n", ctlerror);
		closesocket(s);
	}	
}

//https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-setsockopt
//https://en.wikipedia.org/wiki/Nagle%27s_algorithm
void set_tcpnodelay(SOCKET &s, bool val)
{
	static BOOL opt_val = (val ? TRUE : FALSE);
	int sockopterror = setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char *)&opt_val, sizeof(opt_val));
	if(sockopterror != 0)
	{
		fprintf(stderr, "setsockopt (tcp_nodelay) failed (Error %d)\n", sockopterror);
		closesocket(s);
	}
}

bool send_nonblocking(SOCKET &s, const char *buff, int len, int &pos)
{
	int sent = send(s, buff + pos, len - pos, 0);
	if(sent == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if(error == WSAEWOULDBLOCK)
		{

		}
		else
		{
			fprintf(stderr, "Socket error (Error %d)\n", error);
		}
	}
	else
	{
		pos += sent;
	}
	return len == pos;
}

bool recv_nonblocking(SOCKET &s, char *buff, int len, int &pos)
{
	int read = recv(s, buff + pos, len - pos, 0);
	if(read == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if(error == WSAEWOULDBLOCK)
		{

		}
		else
		{
			fprintf(stderr, "Socket error (Error %d)\n", error);
		}
	}
	else
	{
		pos += read;
	}
	bool ret = (len == pos);
	if(ret)
		pos = 0;
	return ret;
}