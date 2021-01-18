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

void execute_move(char board[8][8], char *move)
{
	int org_column = toupper(move[0]) - 'A';
	int org_row = toupper(move[1]) - '1';
	int dst_column = toupper(move[2]) - 'A';
	int dst_row = toupper(move[3]) - '1';
	board[dst_row][dst_column] = board[org_row][org_column];
	board[org_row][org_column] = ' ';
}