// Шахматы. Мат в 3 хода

#include <iostream>
#include <list>
#include <cstdlib>
#include "game.h"


int main() {
	using namespace std;

	Game g("test.txt");
	g.find_checkmates();

	cin.get();
	return 0;
}