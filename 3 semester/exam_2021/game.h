#pragma once
#include <algorithm>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include "chess_pieces.h"
#include "GameException.h"
#include "piece_square_table.h"




class Game {
	const char* filename;

	std::vector<Piece*> board;

	void read_file();
	void create_pieces(std::ifstream&, Color color);
	Piece* define_piece(char, int, Color);

	bool is_square_attacked(int square, bool white_attack) const;
	bool does_pawn_attack(int square, bool white_attack) const;
	bool does_king_attack(int square) const;
	bool does_knight_attack(int square) const;
	bool does_bq_attack(int square) const;
	bool does_rq_attack(int square) const;

	void print_board();

	void generate_moves(std::vector<Move>&);

	int board_score() const;
	int get_piece_score(int sq) const;

	int score_alphabeta(int depth, int alpha, int beta);

	void make_move(const Move&);
	void undo_move(const Move&);

public:
	Game();
	Game(const char* filename);
	~Game();

	void find_checkmates();
};

