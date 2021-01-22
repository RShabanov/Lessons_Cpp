#include "tokens.h"

bool on_board(int square) {
	return square >= 0 && square < BOARD_SIZE;
}