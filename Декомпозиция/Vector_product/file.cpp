#include "pch.h"
#include "file.h"

Point* read_file(int& index_min, int& size) {
	std::ifstream file("../Границы участка2.txt");
	if (!file.is_open())
		std::cout << "File is not found...";
	else {
		int n;
		if (file >> n && n > 0) {
			size = n;
			Point min;
			Point* list = new Point[n];
			file >> list[0].x >> list[0].y;
			min = list[0];
			for (int i = 1; i < n; i++) {
				file >> list[i].x >> list[i].y;
				if (min.x >= list[i].x)
					if (min.x > list[i].x || min.y > list[i].y) {
						min = list[i];
						index_min = i;
					}
			}
			file.close();
			return list;
		}
		else
			std::cout << "Input error! Point amount cannot be less than 0 or equal to that\n" << n << std::endl;
	}
	file.close();
	return nullptr;
}

void write(const long double area) {
	std::ofstream file("../output.txt");
	if (!file.is_open()) {
		std::cout << "Undefined problems with file!\nCannot be open\n";
		return;
	}
	file << area << std::endl;
	file.close();
}

bool read_task2(long long & sum) {
	std::ifstream file("../Границы участка2.txt");
	if (!file.is_open()) {
		std::cout << "File is not found...";
		return false;
	}
	else {
		int n;
		if (file >> n && n > 0) {
			Point current, points2[2];
			file >> current.x >> current.y;
			file >> points2[0].x >> points2[0].y;
			for (int i = 0; i < n - 2; i++) {
				file >> points2[1].x >> points2[1].y;
				sum += get_coord_v(get_vector(current, points2[0]),
									get_vector(current, points2[1]));
				points2[0] = points2[1];
			}
		}
		else {
			file.close();
			std::cout << "Input error! Point amount cannot be less than 0 or equal to that\n" << n << std::endl;
			return false;
		}
	}
	file.close();
	return true;
}