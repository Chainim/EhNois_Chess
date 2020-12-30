
#define PAWN 'P'
#define BISHOP 'B'
#define ROOK 'R'
#define KING 'K'
#define QUEEN 'Q'
#define KNIGHT 'L'
#define EMPTY ' '

void board_init(char board[8][8]);

void print_board(char board[8][8]);

bool validate_move(char board[8][8]);