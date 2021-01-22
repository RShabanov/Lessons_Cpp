#include "chess_piece.h"


int get_reverse_pos(int pos) {
	if (on_board(pos))
		return BOARD_SIZE - pos;
	else throw; // don't know what error should be here
}

// Chess piece

Piece::Piece(Type _type, Squares _sq, Color _colour)
	: cell_type(_type), pos(_sq), colour(_colour) {}

Piece::~Piece() {}


Type Piece::type() const { return cell_type; }

int Piece::get_position() const { return int(pos); }

Color Piece::color() const { return colour; }

bool Piece::empty() const {
	return cell_type == Type::empty;
}

bool Piece::is_black() const {
	return colour == Color::black;
}
bool Piece::is_white() const {
	return colour == Color::white;
}

bool Piece::is_opposite(const Piece& P) const {
	return colour != P.colour && 
		colour != Color::empty && P.colour != Color::empty;
}


std::ostream& operator<<(std::ostream& out, const Piece& c) {
	out << char(c.pos);
	return out;
}


void Piece::set_new_piece(Type t, Color c) {
	cell_type = t, colour = c;
}

