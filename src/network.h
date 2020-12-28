#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>

void network_init();

void network_shutdown();

void connect(SOCKET &server, const char *ip, unsigned short port);

void setup_server(SOCKET &listen_socket, unsigned short port);