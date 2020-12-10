#include "Pixel.h"


// PIXEL

void Pixel::set_color(int color) {
	r = ((color & 0xFF0000) >> 16);
	g = ((color & 0x00FF00) >> 8);
	b = (color & 0x0000FF);
}


bool Pixel::is_grey() const {
	// |r - g| <= 8 && |r - b| <= 8
	return abs(r - g) < 9 && abs(r - b) < 9;
}

bool Pixel::is_black() const {
	return r == g && r == b && r == 0;
}

bool Pixel::is_white() const {
	return r == g && r == b && r == 0xFF;
}

bool Pixel::is_green() const {
	return g >= (r + b);
}

bool Pixel::is_red() const {
	return r >= (g + b);
}