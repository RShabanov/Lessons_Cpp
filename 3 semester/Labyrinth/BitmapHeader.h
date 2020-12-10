#pragma once
#include <iostream>
#include "BitmapException.h"


// BitmapFileHeader

// Fields: 5
// Width: 14 bytes
class BitmapFileHeader {
	char raw_header[14]{ 0 };
	char file_type[2]{ 'B', 'M' };
	size_t file_size = 0, data_offset = 0;
	unsigned short reserved[2]{ 0 };
public:
	BitmapFileHeader() {}
	~BitmapFileHeader() {}

	size_t get_size() const;
	size_t get_offset() const;

	friend std::ostream& operator<<(std::ostream&, const BitmapFileHeader&);
	friend std::istream& operator>>(std::istream&, BitmapFileHeader&);

	friend class Bitmap;
};


// BitmapInfoHeader

// Fields: 11
// Width: 40 bytes
class BitmapInfoHeader {
	char raw_header[40]{ 0 };
	size_t header_size = 0x28,
		compression,
		image_size,
		total_colors,
		important_colors;
	int img_width, img_height,
		x_pixels_per_meter,
		y_pixels_per_meter;
	unsigned short planes, bits_per_pixel;

public:
	BitmapInfoHeader() {}
	~BitmapInfoHeader() {}

	friend std::ostream& operator<<(std::ostream&, const BitmapInfoHeader&);
	friend std::istream& operator>>(std::istream&, BitmapInfoHeader&);

	friend class Bitmap;
};