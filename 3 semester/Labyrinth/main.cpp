#include <iostream>
#include "Bitmap.h"
#include "Map.h"
using namespace std;


int main() {

	Map map("ДНК_Лабиринт.bmp");
	map.wave_algorithm();
	map.save_result();

	system("pause");
	return 0;
}
