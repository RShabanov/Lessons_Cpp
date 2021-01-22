#ifndef CHESS_PIECE_H_
#define CHESS_PIECE_H_

#include <iostream>
#include <vector>
#include "tokens.h"
#include "move.h"


int get_reverse_pos(int);

class Piece {
	Squares pos;
	Type cell_type;
	Color colour;
public:
	Piece(Type, Squares, Color);
	virtual ~Piece();

	Type type() const;
	int get_position() const;
	Color color() const;

	void set_new_piece(Type, Color);

	bool empty() const;
	bool is_black() const;
	bool is_white() const;
	bool is_opposite(const Piece&) const;

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) {}

	friend std::ostream& operator<<(std::ostream&, const Piece&);
};

#endif