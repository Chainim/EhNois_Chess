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
	board_init(board);

	init_window();
	load_textures();

	bool black_turn = false, match_running = true;
	while(match_running)
	{
		draw_interface(board);
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
		execute_move(board, move);

		black_turn = !black_turn;
	}

	network_shutdown();
}