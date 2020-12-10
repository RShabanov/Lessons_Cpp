#pragma once
#include <iostream>

struct Pixel {
	unsigned char r, g, b;

	void set_color(int);

	bool is_grey() const;
	bool is_black() const;
	bool is_white() const;
	bool is_green() const;
	bool is_red() const;
};
