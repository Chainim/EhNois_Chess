#include <stdio.h>
#include "network.h"
#include "board_utils.h"
#include "window.h"
#include "user_interface.h"

extern bool key_states[256];

extern char key_buff[256];
extern short key_buff_sz;

char recebe_lado;

int main()
{
	network_init();
	SOCKET servidor;
	connect(servidor, "127.0.0.1", 7777);

	recv_all(servidor, &recebe_lado, 1);
	set_blocking(servidor, false);
	set_tcpnodelay(servidor, true);

	printf("lado %c\n",recebe_lado);

	char board[8][8];
	board_init(board);

	init_window();
	load_textures();

	bool black_turn = false, match_running = true;
	char move[4], recvmove[4];
	int recvmovepos = 0;
	bool sent_play;
	while(match_running)
	{
		draw_interface(board);
		if(!window_loop())
			break;

		if(!sent_play)
		{
			if((black_turn && recebe_lado == '2') || (!black_turn && recebe_lado == '1'))
			{
				if(key_states['\r'])
				{
					send_all(servidor, key_buff, 4);
					sent_play = true;
					key_buff[key_buff_sz = 0] = 0;
				}
			}
		}
		if(recv_nonblocking(servidor, recvmove, 4, recvmovepos))
		{
			printf("O movimento foi %c%c->%c%c\n", recvmove[0], recvmove[1], recvmove[2], recvmove[3]);
			execute_move(board, recvmove);
			black_turn = !black_turn;
			sent_play = false;
		}
	}

	network_shutdown();
}