#include "chess_pieces.h"


// King

King::King(Squares sq, Color cr)
	: Piece(Type::king, sq, cr) {
}

void King::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	for (int i = -1; i < offset_size; i++) {
		for (int j = 0; j < king_offset_size; j++) {
			int to_sq = sq + king_offsets[j] * i;

			if (on_board(to_sq)) {
				if (board[to_sq]->empty()) {
					// add move for empty
					moves.push_back(Move(sq, to_sq, board[to_sq]->type(),
						false, false, 0));
				}
				else if (is_opposite(*board[to_sq])) {
					// eat the opponent
					moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
				}
			}
		}
		i++; // чтобы i выступала в роли знака
	}
}



// Queen

Queen::Queen(Squares sq, Color cr)
	: Piece(Type::queen, sq, cr) {}

void Queen::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	Piece* piece = new Rook(Squares(sq), board[sq]->color());
	piece->generate_move(board, sq, moves);
	delete piece;

	piece = new Bishop(Squares(sq), board[sq]->color());
	piece->generate_move(board, sq, moves);
	delete piece;
}


// Rook

Rook::Rook(Squares sq, Color cr)
	: Piece(Type::rook, sq, cr) {}

void Rook::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	for (int i = -1; i < offset_size; i++) {
		for (int j = 0; j < offset_size; j++) {
			int to_sq = sq + rook_offsets[j] * i;

			while (on_board(to_sq)) {
				if (board[to_sq]->empty()) {
					// add empty move
					moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
				}
				else {
					if (is_opposite(*board[to_sq])) {
						// add move
						moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
					}
					break;
				}
				to_sq += rook_offsets[j] * i;
			}
		}
		i++; // чтобы i выступала в роли знака
	}
}



// Bishop

Bishop::Bishop(Squares sq, Color cr)
	: Piece(Type::bishop, sq, cr) {}

void Bishop::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	for (int i = -1; i < offset_size; i++) {
		for (int j = 0; j < offset_size; j++) {
			int to_sq = sq + bishop_offsets[j] * i;

			while (on_board(to_sq)) {
				if (board[to_sq]->empty()) {
					// add empty move
					moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
				}
				else {
					if (is_opposite(*board[to_sq])) {
						// add move
						moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
					}
					break;
				}
				to_sq += bishop_offsets[j] * i;
			}
		}
		i++; // чтобы i выступала в роли знака
	}
}


// Knight

Knight::Knight(Squares sq, Color cr)
	: Piece(Type::knight, sq, cr) {
}

void Knight::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	for (int i = -1; i < offset_size; i++) {
		for (int j = 0; j < knight_offset_size; j++) {
			int to_sq = sq + knight_offsets[j] * i;

			if (on_board(to_sq)) {
				if (board[to_sq]->empty()) {
					// add move for empty
					moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
				}
				else if (is_opposite(*board[to_sq])) {
					// eat the opponent
					moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
				}
			}
		}
		i++; // чтобы i выступала в роли знака
	}
}






// Pawn

Pawn::Pawn(Squares sq, Color cr)
	: Piece(Type::pawn, sq, cr) {}

void Pawn::generate_move(std::vector<Piece*>& board, int sq, std::vector<Move>& moves) {
	int to_sq;
	if (board[sq]->is_white()) {
		to_sq = sq - 8;
		if (on_board(to_sq) && board[to_sq]->empty())
			generate_quite_moves_w(sq, to_sq, board, moves);

		generate_capture_moves_w(sq, board, moves);
	}
	else {
		to_sq = sq + 8;
		if (on_board(to_sq) && board[to_sq]->empty())
			generate_quite_moves_b(sq, to_sq, board, moves);

		generate_capture_moves_b(sq, board, moves);
	}
}

void Pawn::generate_quite_moves_w(int sq, int to_sq, std::vector<Piece*>& board, std::vector<Move>& moves) {
	if (sq >= int(Squares::a7) && sq <= int(Squares::h7)) {
		// add_move somewhere
		moves.push_back(Move(sq, to_sq, Type::queen, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::rook, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::bishop, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::knight, 0, 0, 0));
	}
	else {
		// add square ahead pawn move
		moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
		// two
		if (sq >= int(Squares::a2) && sq <= int(Squares::h2) &&
			board[sq - 16]->empty()) {
			// add this move
			moves.push_back(Move(sq, to_sq - 16, Type::empty, 1, 0, 0));
		}
	}
}

void Pawn::generate_capture_moves_w(int sq, std::vector<Piece*>& board, std::vector<Move>& moves) {
	for (int j = 0; j < offset_size; j++) {
		register int pawn_offset = -bishop_offsets[j];
		if (pawn_offset < 0) { // since white pieces go up
			int to_sq = sq + pawn_offset;

			if (on_board(to_sq)) {
				if (sq >= int(Squares::a7) && sq <= int(Squares::h7) &&
					board[to_sq]->is_black()) {
					// add moves
					moves.push_back(Move(sq, to_sq, Type::queen, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::rook, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::bishop, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::knight, 0, 0, 0));
				}
				else {
					if (board[to_sq]->is_black()) {
						// add move
						moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
					}
					/*
					enpassant
					*/
				}
			}
		}
	}

}


void Pawn::generate_quite_moves_b(int sq, int to_sq, std::vector<Piece*>& board, std::vector<Move>& moves) {
	if (sq >= int(Squares::a2) && sq <= int(Squares::h2)) {
		// add_move somewhere
		moves.push_back(Move(sq, to_sq, Type::queen, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::rook, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::bishop, 0, 0, 0));
		moves.push_back(Move(sq, to_sq, Type::knight, 0, 0, 0));
	}
	else {
		// add square ahead pawn move
		moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
		// two
		if (sq >= int(Squares::a7) && sq <= int(Squares::h7) &&
			board[sq + 16]->empty()) {
			// add this move
			moves.push_back(Move(sq, to_sq, Type::empty, 1, 0, 0));
		}
	}
}

void Pawn::generate_capture_moves_b(int sq, std::vector<Piece*>& board, std::vector<Move>& moves) {
	for (int j = 0; j < offset_size; j++) {
		register int pawn_offset = bishop_offsets[j];
		if (pawn_offset > 0) { // since white pieces go up
			int to_sq = sq + pawn_offset;

			if (on_board(to_sq)) {
				if (sq >= int(Squares::a2) && sq <= int(Squares::h2) &&
					board[to_sq]->is_white()) {
					// add moves
					moves.push_back(Move(sq, to_sq, Type::queen, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::rook, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::bishop, 0, 0, 0));
					moves.push_back(Move(sq, to_sq, Type::knight, 0, 0, 0));
				}
				else {
					if (board[to_sq]->is_white()) {
						// add move
						moves.push_back(Move(sq, to_sq, Type::empty, 0, 0, 0));
					}
					/*
					enpassant
					*/
				}
			}
		}
	}
}