#pragma once

#include <iostream>

enum Cell { EMPTY, RED, YELLOW };

//Cell cell = RED;
const int FIELD_WIDTH = 7, FIELD_HEIGHT = 6;

const int DIR_NUMBER = 4;
const int di[] = { 1, 0 , 1, 1 };
const int dj[] = { 0, 1, -1, 1 };
const int WIN_LENGTH = 4;


class Field {

	Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
	bool is_red_turn;
	Cell winner;

	void check_winner();

public:
	Field(bool is_red_first);
	void clear();
	bool make_turn(int column);
	bool is_over() const;

	Cell get_cell(int i, int j) const;

	bool is_red_turn_now() const;
	void print() const;
	void print_result() const;

};
