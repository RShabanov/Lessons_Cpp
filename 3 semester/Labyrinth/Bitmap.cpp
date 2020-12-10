#include "Bitmap.h"



Bitmap::Bitmap() {
}

Bitmap::Bitmap(const std::string& _filename) : filename(_filename) {
	std::ifstream file(_filename, std::ios_base::binary);

	raw_data = nullptr;
	raw_size = 0;

	if (file.is_open()) file >> *this;
	else throw BitmapException();
}

Bitmap::Bitmap(const Bitmap& bmp) {
	file_header = bmp.file_header;
	info_header = bmp.info_header;
	raw_size = bmp.raw_size;
	filename = bmp.filename;

	if (bmp.raw_data != 0)
		for (int i = 0; i < raw_size; i++)
			raw_data[i] = bmp.raw_data[i];
	else raw_data = nullptr;
}

Bitmap::~Bitmap() {
	if (raw_data != 0)
		delete[] raw_data;
}



// I/O 
std::istream& operator>>(std::istream& in, Bitmap& bmp) {
	in >> bmp.file_header >> bmp.info_header;

	bmp.raw_size = bmp.img_height() * bmp.img_width() * (bmp.bpp() >> 3);

	if (bmp.raw_data != 0) delete[] bmp.raw_data;
	bmp.raw_data = new unsigned char[bmp.raw_size];

	// BMP follows bottom-up scanning
	// so we will fill our array from the end
	in.read((char*)bmp.raw_data, bmp.raw_size);

	return in;
}

std::ostream& operator<<(std::ostream& out, const Bitmap& bmp) {
	out << bmp.file_header << bmp.info_header;
	out.write((char*)bmp.raw_data, bmp.raw_size);
	return out;
}



// operator overloading
const Bitmap& Bitmap::operator=(const Bitmap& bmp) {
	file_header = bmp.file_header;
	info_header = bmp.info_header;
	raw_size = bmp.raw_size;
	filename = bmp.filename;

	if (raw_data != 0) delete[] raw_data;

	if (bmp.raw_data != 0)
		for (int i = 0; i < raw_size; i++)
			raw_data[i] = bmp.raw_data[i];
	else raw_data = nullptr;

	return *this;
}



// getters

unsigned char const* Bitmap::get_data() const { return raw_data; }

int Bitmap::img_width() const { return info_header.img_width; }

int Bitmap::img_height() const { return info_header.img_height; }

int Bitmap::bpp() const { return info_header.bits_per_pixel; }
