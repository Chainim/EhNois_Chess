#include "board_utils.h"
#include <stdio.h>

void board_init(char board[8][8])
{
	for(int i = 0; i < 8; ++i)
		board[1][i] = PAWN;
	board[0][0] = ROOK;
	board[0][7] = ROOK;
	board[0][1] = KNIGHT;
	board[0][6] = KNIGHT;
	board[0][2] = BISHOP;
	board[0][5] = BISHOP;
	board[0][3] = QUEEN;
	board[0][4] = KING;

	for(int i = 0; i < 8; ++i)
		board[6][i] = PAWN;
	board[7][0] = ROOK;
	board[7][7] = ROOK;
	board[7][1] = KNIGHT;
	board[7][6] = KNIGHT;
	board[7][2] = BISHOP;
	board[7][5] = BISHOP;
	board[7][3] = QUEEN;
	board[7][4] = KING;
}

void print_board(char board[8][8])
{
	for(int i = 7; i >= 0; --i)
	{
		for(int j = 0; j < 8; ++j)
			printf("%c", board[i][j] & (~(1 << 7)));
		printf("\n");
	}
}