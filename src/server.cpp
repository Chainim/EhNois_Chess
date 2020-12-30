#include <stdio.h>
#include "network.h"
#include "board_utils.h"

int main()
{
	network_init();
	SOCKET listen_socket, client[2];
	setup_server(listen_socket, 7777);
	client[0] = accept(listen_socket, nullptr, nullptr);
	client[1] = accept(listen_socket, nullptr, nullptr);

	char decide_lado = '1';
	send_all(client[0], &decide_lado, 1);
	decide_lado = '2';
	send_all(client[1], &decide_lado, 1);

	char board[8][8];
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j)
			board[i][j] = ' ';

	board_init(board);

	bool black_turn = false, match_running = true;

	while(match_running)
	{
		char move[4];
		recv_all(client[black_turn], move, 4);

		//TODO: move validation
		int org_column = move[0] - 'A';
		int org_row = move[1] - '1';
		int dst_column = move[2] - 'A';
		int dst_row = move[3] - '1';

		board[dst_row][dst_column] = board[org_row][org_column];
		board[org_row][org_column] = ' ';

		send_all(client[0], move, 4);
		send_all(client[1], move, 4);

		black_turn = !black_turn;
	}

	network_shutdown();
}