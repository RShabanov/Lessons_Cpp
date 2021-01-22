#include "game.h"



Game::Game() {
	for (int i = 0; i < BOARD_SIZE; i++)
		board.push_back(new Piece({ Type::empty, Squares(i), Color::empty }));
}

Game::Game(const char* _filename)
	: Game() { 
	filename = _filename; 
	read_file();
}

Game::~Game() {
	for (size_t i = 0; i < board.size(); i++)
		delete board.at(i);
}


void Game::read_file() {
	std::ifstream fin(filename);
	if (!fin.is_open()) 
		throw GameException(game_exception::CANNOT_OPEN_FILE);

	auto str_to_lower{ [](unsigned char ch) { return std::tolower(ch); } };
	std::string temp;
	int cnt = 2;
	
	while (cnt--) {
		fin >> temp;

		std::transform(temp.begin(), temp.end(), temp.begin(), str_to_lower);
		if (temp == "white:")
			create_pieces(fin, Color::white);
		else if (temp == "black:")
			create_pieces(fin, Color::black);
		else throw GameException(game_exception::BAD_FILE);
	}

	if (!fin.eof()) throw GameException(game_exception::BAD_FILE);
}

void Game::create_pieces(std::ifstream& fin, Color color) {
	char type, posL; // posLetter
	int posD; // posDigit
	int size = 0;
	fin >> size;

	while (size--) {
		fin >> type >> posL >> posD;
		int new_sq = ((8 - posD) << 3) + (std::tolower(posL) - 'a');

		delete board[new_sq];

		board[new_sq] = define_piece(std::tolower(type), new_sq, color);
	}
}

Piece* Game::define_piece(char type, int sq, Color cr) {
	switch (type) {
	case char(Type::king) :
		return new King(Squares(sq), cr);
	case char(Type::queen):
		return new Queen(Squares(sq), cr);
	case char(Type::rook) :
		return new Rook(Squares(sq), cr);
	case char(Type::knight):
		return new Knight(Squares(sq), cr);
	case char(Type::bishop):
		return new Bishop(Squares(sq), cr);
	case char(Type::pawn):
		return new Pawn(Squares(sq), cr);
	default:
		throw GameException(game_exception::BAD_FILE);
		break;
	}
}


void Game::print_board() {
	using std::cout;
	using std::endl;

	Piece* t = 0;

	for (int i = 0; i < board.size(); i++) {
		if (i % 8 == 0) cout << endl;
		cout << char(board.at(i)->type()) << " ";
	}
	cout << endl;
}


void Game::find_checkmates() {
	print_board();
	std::cout << std::endl;

	std::cout << score_alphabeta(3, INT_MIN, INT_MAX) << std::endl;
}

bool Game::is_square_attacked(int square, bool white_attack) const {
	if (does_pawn_attack(square, white_attack) ||
		does_knight_attack(square) ||
		does_king_attack(square) ||
		does_bq_attack(square) ||
		does_rq_attack(square))
		return true;

	return false;
}

bool Game::does_pawn_attack(int square, bool white_attack) const {
	// т.к. bishop_offset подходит для pawn
	// используем его
	for (int i = 0; i < offset_size; i++) {
		register int target_sq = square + bishop_offsets[i] * (white_attack ? -1 : 1);
		if (on_board(target_sq) && board[target_sq]->type() == Type::pawn)
			return true;
	}
	return false;
}

bool Game::does_king_attack(int square) const {
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < king_offset_size; j++) {
			register int target_sq = square + i * king_offsets[j];
			if (on_board(target_sq) && board[target_sq]->type() == Type::king)
				return true;
		}
		i++;
	}
	return false;
}
bool Game::does_knight_attack(int square) const {
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < knight_offset_size; j++) {
			register int target_sq = square + i * knight_offsets[j];
			if (on_board(target_sq) && board[target_sq]->type() == Type::king)
				return true;
		}
		i++;
	}
	return false;
}
bool Game::does_bq_attack(int square) const {
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < offset_size; j++) {
			register int target_sq = square + i * bishop_offsets[j];
			while (on_board(target_sq)) {
				if (board[target_sq]->type() == Type::bishop ||
					board[target_sq]->type() == Type::queen) return true;

				if (!board[target_sq]->empty()) break;

				target_sq += i * bishop_offsets[j];
			}
		}
		i++;
	}
	return false;
}
bool Game::does_rq_attack(int square) const {
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < offset_size; j++) {
			register int target_sq = square + i * rook_offsets[j];
			while (on_board(target_sq)) {
				if (board[target_sq]->type() == Type::rook ||
					board[target_sq]->type() == Type::queen) return true;

				if (!board[target_sq]->empty()) break;

				target_sq += i * rook_offsets[j];
			}
		}
		i++;
	}
	return false;
}


void Game::generate_moves(std::vector<Move>& moves) {
	moves.clear();

	for (int square = 0; square < BOARD_SIZE; square++) {
		if (!board[square]->empty())
			board[square]->generate_move(board, square, moves);
		// TODO: castling
	}
}


int Game::board_score() const {
	register int score = 0;
	for (int sq = 0; sq < BOARD_SIZE; sq++)
		if (on_board(sq)) score += get_piece_score(sq);
	return score;
}

int Game::get_piece_score(int sq) const {
	if (board[sq]->empty()) return 0;

	int score = 0;
	int pos = board[sq]->is_white() ? sq : get_reverse_pos(sq);
	switch (board[sq]->type()) {
	case Type::pawn:
		score += 10 + pawn_t[pos];
	case Type::rook:
		score += 30 + rook_t[pos];
	case Type::bishop:
		score += 35 + bishop_t[pos];
	case Type::knight:
		score += 50 + knight_t[pos];
	case Type::queen:
		score += 90 + queen_t[pos];
	case Type::king:
		score += 1000 + king_t[pos];
	}

	return board[sq]->is_white() ? score : -score;
}


int Game::score_alphabeta(int depth, int alpha, int beta) {
	if (!depth) return 0;

	int score_best = alpha;
	int score;

	std::vector<Move> moves;
	generate_moves(moves);

	for (size_t i = 0; i < moves.size(); i++) {
		make_move(moves[i]);
		score = -score_alphabeta(depth - 1, beta, -score_best);
		undo_move(moves[i]);

		if (score > score_best) {
			score_best = score;
			if (score_best >= beta) break;
		}
	}
	return score_best;
}

void Game::make_move(const Move& move) {
	// TODO: check if king is under check

	if (is_square_attacked(move.target, bool(board[move.source]->color()))) {

	}

	board[move.target]->set_new_piece(board[move.source]->type(),
		board[move.source]->color());

	board[move.source]->set_new_piece(Type::empty, Color::empty);

	print_board();
}

void Game::undo_move(const Move& move) {
	board[move.source]->set_new_piece(board[move.target]->type(),
		board[move.target]->color());

	board[move.target]->set_new_piece(move.promotion,
		move.promotion == Type::empty ? Color::empty :
		board[move.target]->is_white() ? Color::black : Color::white);

}
