#include "move.h"


Move::Move(int s, int t, Type p, bool dj, bool e, int c) {
	source = s;
	target = t;
	promotion = p;
	djump_pawn = dj;
	enpassant = e;
	castling = c;
}