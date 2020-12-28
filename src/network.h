#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>

void network_init();

void network_shutdown();

void connect();

void setup_server(SOCKET &listenSocket, unsigned short port);