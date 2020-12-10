#pragma once
#include <fstream>
#include <queue>
#include "MapException.h"
#include "Bitmap.h"
#include "Pixel.h"


constexpr int obstacle = -1, finish = -2, blank = 0;

struct Point {
	Point();
	Point(int, int);
	int row, column;
};


class Map
{
	Bitmap* bmp;
	Pixel** data;

	void prepare_data();
	
	// Point& - finish point
	void draw_path(int**, Point&);

	bool is_good_cell(int**, int, int) const;
	
public:
	Map();
	Map(const Bitmap&);
	Map(const std::string&);
	~Map();

	void wave_algorithm();

	void save_result() const;
};

