#pragma once
#include <vector>
#include "tokens.h"


struct Move {
	int source, target;
	Type promotion;
	bool djump_pawn, enpassant;
	int castling;

	Move(int, int, Type, bool, bool, int);
};
