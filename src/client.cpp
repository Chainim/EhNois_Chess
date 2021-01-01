#include <stdio.h>
#include "network.h"
#include "board_utils.h"
#include "window.h"
#include "user_interface.h"

int main()
{
	network_init();
	SOCKET servidor;
	connect(servidor, "127.0.0.1", 7777);

	char recebe_lado;
	recv_all(servidor, &recebe_lado, 1);

	printf("lado %c\n",recebe_lado);

	char board[8][8];
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j)
			board[i][j] = ' ';

	board_init(board);
	print_board(board);

	init_window();

	bool black_turn = false, match_running = true;
	while(match_running)
	{
		draw_interface();
		if(!window_loop())
			break;

		char move[4];
		if((black_turn && recebe_lado == '2') || (!black_turn && recebe_lado == '1'))
		{
			scanf(" %c%c%c%c", &move[0], &move[1], &move[2], &move[3]);
			send_all(servidor, move, 4);
		}
		recv_all(servidor, move, 4);
		printf("O movimento foi %c%c->%c%c\n", move[0], move[1], move[2], move[3]);
		int org_column = move[0] - 'A';
		int org_row = move[1] - '1';
		int dst_column = move[2] - 'A';
		int dst_row = move[3] - '1';
		board[dst_row][dst_column] = board[org_row][org_column];
		board[org_row][org_column] = ' ';
		print_board(board);


		black_turn = !black_turn;
	}

	network_shutdown();
}