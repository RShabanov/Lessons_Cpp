#include "pch.h"
#include "geometry.h"

int get_coord_v(const Vector& a, const Vector& b) {
	return a.x * b.y - b.x * a.y;
	//switch (coord)
	//{
	//case 1: // для определения других координат
	//case 2:
	//	break;
	//case 3:
	//	return a.x * b.y - b.x * a.y;
	//}
}

Point get_vector(const Point& A, const Point& B) {
	return {B.x - A.x, B.y - A.y};
}