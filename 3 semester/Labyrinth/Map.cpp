#include "Map.h"


Point::Point() {
	row = column = 0;
}

Point::Point(int _row, int _col) {
	row = _row;
	column = _col;
}


// MAP

Map::Map() {
	bmp = nullptr;
	data = nullptr;
}

Map::Map(const Bitmap& _bmp) {
	bmp = new Bitmap(_bmp);
	prepare_data();
}

Map::Map(const std::string& filename) {
	bmp = new Bitmap(filename);
	prepare_data();
}

Map::~Map() {
	if (data != 0) {
		for (int i = 0; i < bmp->img_height(); i++)
			delete[] data[i];
		delete[] data;
	}
	if (bmp != 0) delete bmp;
}



// PRIVATE METHODS
void Map::prepare_data() {
	size_t height = bmp->img_height(),
		width = bmp->img_width();

	data = new Pixel*[height];

	int row = height, col = 0;
	for (int i = 0; i < bmp->raw_size; i += 3) {
		col = (i / 3) % width;
		if (col == 0) data[--row] = new Pixel[width];

		data[row][col].b = bmp->raw_data[i];
		data[row][col].g = bmp->raw_data[i + 1];
		data[row][col].r = bmp->raw_data[i + 2];
	}
}


void Map::draw_path(int** matrix, Point& start) {
	int length = matrix[start.row][start.column];
	int dx[4]{ -1, 0, 0, 1 };
	int dy[4]{ 0, -1, 1, 0 };

	while (length > 0) {
		data[start.row][start.column].set_color(0xE64A19);

		for (int i = 0; i < 4; i++) {
			int new_row = start.row + dx[i],
				new_col = start.column + dy[i];
			if ((length - matrix[new_row][new_col]) == 1) {
				start.row = new_row;
				start.column = new_col;
				break;
			}
		}
		length--;
	}
}


bool Map::is_good_cell(int** matrix, int _row, int _col) const {
	return _row >= 0 && _row < bmp->img_height() &&
		_col >= 0 && _col < bmp->img_width() &&
		(matrix[_row][_col] == blank || matrix[_row][_col] == finish);
}



// PUBLIC METHODS
void Map::wave_algorithm() {
	size_t height = bmp->img_height(),
		width = bmp->img_width();

	Point start_p;
	bool fst = true;

	//  initialization
	int** matrix = new int*[height];
	for (int i = 0; i < height; i++) {
		matrix[i] = new int[width] {0};
		for (int j = 0; j < width; j++) {
			if (data[i][j].is_white()) matrix[i][j] = blank;
			else if (data[i][j].is_black() || data[i][j].is_grey())
				matrix[i][j] = obstacle;
			else if (data[i][j].is_green())
				matrix[i][j] = finish;
			else if (data[i][j].is_red()) {
				matrix[i][j] = blank;
				if (fst) {
					start_p.row = i;
					start_p.column = j;
					fst = false;
				}
			}
		}
	}

	/* Algorithm */

	std::queue<Point> points;
	points.push(start_p);

	int dx[4]{ -1, 0, 0, 1 };
	int dy[4]{ 0, -1, 1, 0 };

	Point current_p;
	while (!points.empty()) {
		current_p = points.front();

		for (int i = 0; i < 4; i++) {
			int new_row = current_p.row + dx[i],
				new_col = current_p.column + dy[i];

			if (is_good_cell(matrix, new_row, new_col) &&
				(new_row != start_p.row || new_col != start_p.column)) {
				
				if (matrix[new_row][new_col] == finish) {
					matrix[new_row][new_col] = matrix[current_p.row][current_p.column] + 1;
					current_p.row = new_row;
					current_p.column = new_col;
					goto FIND_PATH;
				}
				matrix[new_row][new_col] += matrix[current_p.row][current_p.column] + 1;
				points.push(Point(new_row, new_col));
			}
		}
		points.pop();
	}

	/* Algorithm */

FIND_PATH:
	draw_path(matrix, current_p);

	for (int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[] matrix;
}


void Map::save_result() const {
	long long height = bmp->img_height(),
		width = bmp->img_width();
	std::string filename = bmp->filename;
	filename.resize(filename.size() - 4);
	filename += "_result.bmp";
	
	std::ofstream out(filename, std::ios_base::binary);

	if (out.is_open()) {
		unsigned char bgr[3]{ 0 };

		out << bmp->file_header << bmp->info_header;

		for (int i = height - 1; i >= 0; i--)
			for (int j = 0; j < width; j++) {
				bgr[2] = data[i][j].r;
				bgr[1] = data[i][j].g;
				bgr[0] = data[i][j].b;

				out.write((char*)bgr, 3);
			}
	}
	else throw MapException();

	out.close();
}