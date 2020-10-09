#include <iostream>
#include "field.h"
using namespace std;


int main() {

	setlocale(LC_ALL, "rus");
	Field field(true);
	while (!field.is_over()) {
		field.print();
		cout << "Ходит " << (field.is_red_turn_now() ? "красный" : "желтый")
			<< " игрок, введите ход (1-7)\n";
		int column;
		cin >> column;
		field.make_turn(column);
	}
	field.print_result();
	
	system("pause");
	return 0;
}
