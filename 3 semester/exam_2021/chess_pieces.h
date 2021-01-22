#pragma once
#include "chess_piece.h"


// на самом деле их в 2 раза больше, т.к.
// необходимо учитывать отступы с противоположным знаком


constexpr int offset_size = 2,
			  knight_offset_size = 4,
			  king_offset_size = 4;

constexpr int knight_offsets[knight_offset_size] = { 17, 15, 10, 6 };
constexpr int bishop_offsets[offset_size] = { 7, 9 };
constexpr int rook_offsets[offset_size] = { 1, 8 };
constexpr int king_offsets[king_offset_size] = { 7, 9, 1, 8 };



class King : public Piece {
public:
	King(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};


class Queen : public Piece {
public:
	Queen(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};


class Rook : public Piece {
public:
	Rook(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};


class Knight : public Piece {
public:
	Knight(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};


class Bishop : public Piece {
public:
	Bishop(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};


class Pawn : public Piece {
	// white
	void generate_quite_moves_w(int, int, std::vector<Piece*>&, std::vector<Move>&);
	void generate_capture_moves_w(int, std::vector<Piece*>&, std::vector<Move>&);

	// black
	void generate_quite_moves_b(int, int, std::vector<Piece*>&, std::vector<Move>&);
	void generate_capture_moves_b(int, std::vector<Piece*>&, std::vector<Move>&);
public:
	Pawn(Squares, Color cr);

	virtual void generate_move(std::vector<Piece*>&, int, std::vector<Move>&) override final;
};