#include "pch.h"
#include "geometry.h"
#include "file.h"
#include <iostream>

// task_1
void bypass_direction();

// task_2
void polygon_area();

int main()
{
	using namespace std;
	// bypass_direction();
	polygon_area();
	system("pause");
	return 0;
}

void bypass_direction() {
	int size = 0, index_min = 0;
	Point* points = read_file(index_min, size);
	if (points == nullptr)
		return;

	Vector pair[2];

	// проверяем случаи когда крайняя имеет индекс
	// равный 0 или количеству точек - 1
	if (index_min == 0) {
		pair[0] = get_vector(points[size - 1], points[index_min]);
		pair[1] = get_vector(points[index_min], points[index_min + 1]);
	}
	else if (index_min == size - 1) {
		pair[0] = get_vector(points[index_min - 1], points[index_min]);
		pair[1] = get_vector(points[index_min], points[0]);
	}
	else {
		pair[0] = get_vector(points[index_min - 1], points[index_min]);
		pair[1] = get_vector(points[index_min], points[index_min + 1]);
	}

	if (get_coord_v(pair[0], pair[1]) < 0)
		std::cout << "Clockwise\n";
	else // случай == 0 можно не рассматривать, т.к. он невозможен
		std::cout << "Counterclockwise\n";

	delete points;
}

void polygon_area() {
	long long area = 0;
	if (!read_task2(area)) return;

	if (area < 0) area = -area; // находим длину

	write(long double(area / 2.0));
}
