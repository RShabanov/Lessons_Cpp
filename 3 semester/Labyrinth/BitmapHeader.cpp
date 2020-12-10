#include "BitmapHeader.h"


// BitmapFileHeader

size_t BitmapFileHeader::get_size() const { return file_size; }
size_t BitmapFileHeader::get_offset() const { return data_offset; }

std::istream& operator>>(std::istream& in, BitmapFileHeader& bmp) {

	in.read(bmp.raw_header, 14);

	if (bmp.raw_header[0] == bmp.file_type[0] && 
		bmp.raw_header[1] == bmp.file_type[1]) {

		int start = 2;
		bmp.file_size = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		for (auto& item : bmp.reserved) {
			item = *(short*)&bmp.raw_header[start];
			start += sizeof(short);
		}

		bmp.data_offset = *(int*)&bmp.raw_header[start];
	}
	else throw BitmapException();

	return in;
}

std::ostream& operator<<(std::ostream& out, const BitmapFileHeader& bmp) {
	out.write(bmp.raw_header, 14);
	return out;
}





// BitmapInfoHeader

std::istream& operator>>(std::istream& in, BitmapInfoHeader& bmp) {

	in.read(bmp.raw_header, 40);

	if (bmp.header_size == *(int*)&bmp.raw_header[0]) {

		int start = 4;

		bmp.img_width = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.img_height = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.planes = *(short*)&bmp.raw_header[start];
		start += sizeof(short);

		bmp.bits_per_pixel = *(short*)&bmp.raw_header[start];
		start += sizeof(short);

		bmp.compression = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.image_size = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.x_pixels_per_meter = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.y_pixels_per_meter = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.total_colors = *(int*)&bmp.raw_header[start];
		start += sizeof(int);

		bmp.important_colors = *(int*)&bmp.raw_header[start];
		start += sizeof(int);
	}
	else throw BitmapException();

	return in;
}

std::ostream& operator<<(std::ostream& out, const BitmapInfoHeader& bmp) {
	out.write(bmp.raw_header, 40);
	return out;
}