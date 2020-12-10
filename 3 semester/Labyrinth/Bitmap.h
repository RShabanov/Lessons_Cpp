#pragma once
#include <fstream>
#include "BitmapHeader.h"
#include "BitmapException.h"


class Bitmap {
	BitmapFileHeader file_header;
	BitmapInfoHeader info_header;
	
	size_t raw_size;
	unsigned char* raw_data;
	std::string filename;

public:
	Bitmap();
	Bitmap(const std::string&);
	Bitmap(const Bitmap&);
	~Bitmap();

	friend std::ostream& operator<<(std::ostream&, const Bitmap&);
	friend std::istream& operator>>(std::istream&, Bitmap&);

	const Bitmap& operator=(const Bitmap&);

	unsigned char const* get_data() const;

	int img_width() const;
	int img_height() const;

	// bits_per_pixel
	int bpp() const;

	friend class Map;
};

