#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>

void network_init();

void network_shutdown();

void connect(SOCKET &server, const char *ip, unsigned short port);

void setup_server(SOCKET &listen_socket, unsigned short port);

void recv_all(SOCKET &s, char *buff, int len);

void send_all(SOCKET &s, const char *buff, int len);

void set_blocking(SOCKET &s, bool blocking);

void set_tcpnodelay(SOCKET &s, bool val);

bool send_nonblocking(SOCKET &s, const char *buff, int len, int &pos);

bool recv_nonblocking(SOCKET &s, char *buff, int len, int &pos);