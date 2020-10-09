#include "field.h"



Field::Field(bool is_red_first) {
	is_red_turn = is_red_first;
	clear();
}

void Field::clear() {
	winner = EMPTY;
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++)
			cells[i][j] = EMPTY;
}

bool Field::make_turn(int column) {
	if (winner != EMPTY ||
		column < 1 || column > FIELD_WIDTH) return false;
	int i = column - 1;
	for (int j = 0; j < FIELD_HEIGHT; j++) {
		if (cells[i][j] == EMPTY) {
			cells[i][j] = is_red_turn ? RED : YELLOW;
			check_winner();
			is_red_turn = !is_red_turn;
			return true;
		}
	}
	return false;
}


void Field::check_winner() {
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++) {
			Cell start = cells[i][j];
			if (start == EMPTY) continue;
			for (int dir = 0; dir < DIR_NUMBER; dir++) {
				int length = 0, iline = i, jline = j;
				while (++length < WIN_LENGTH) {
					iline += di[dir];
					jline += dj[dir];
					if (iline < 0 || iline >= FIELD_WIDTH ||
						jline < 0 || jline >= FIELD_HEIGHT ||
						cells[iline][jline] != start)
						break;
					//if (cells[iline][jline] != start) break;
				}
				if (length == WIN_LENGTH) {
					winner = start;
					return;
				}
			}
		}
}

bool Field::is_over() const {
	if (winner != EMPTY) return true;
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++)
			if (cells[i][j] == EMPTY) return false;
	return true;
}

void Field::print() const {
	system("cls");

	for (int i = 0; i < FIELD_WIDTH; i++) {
		for (int j = 0; j < FIELD_HEIGHT; j++)
			std::cout << ( (cells[i][j] == EMPTY) ? '.' : (cells[i][j] == RED) ? 'X' : 'O' );
		std::cout << std::endl;
	}
}

void Field::print_result() const {
	system("cls");
	print();
	
	std::cout << std::endl << std::endl;
	if (winner == EMPTY)
		std::cout << "There is no winner\n";
	else
		std::cout << ((winner == RED) ? "X" : "O") << " player is a winner!\n";
}

bool Field::is_red_turn_now() const {
	return is_red_turn;
}

Cell Field::get_cell(int i, int j) const {
	return cells[i][j];
}
