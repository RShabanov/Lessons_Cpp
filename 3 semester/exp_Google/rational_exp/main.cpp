#include <iostream>
#include <iomanip>
#include <fstream>
#include "exp.h"


using namespace std;

void compute_exp_with_fraction(const unsigned int, bool);
void check(const char*, const char*);
bool input_mode(const char*);


int main() {
	
	unsigned int number;

	// цепную дробь для е можно представить в виде бесконечной дроби
	// [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, 1, ..., 2n]
	// здесь запрашивается у пользователя число 2n
	// фактически, 2n - количество этажей
	cout << "Enter even number (how many digits you need):\t";
	while (!(cin >> number) || number % 2) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Please, enter even integer:\t";
	}

	compute_exp_with_fraction(number, input_mode("to output"));	

	//check("rational_exp.txt", "e_2mil.txt");

	system("pause");
	return 0;
}


// преобразуем цепную дробь в обычную
// и выводим ее в консоль или файл (вариант выбирает пользователь)
void compute_exp_with_fraction(unsigned int number, bool out = false) {

	register int cnt = 0;
	Exp e(number);

	number -= 2;
	while (number) {
		if (cnt++ < 2) e.add_denom(); // добавляем 1
		else {
			e.add_denom(number); // добавляем четное число
			number -= 2;
			cnt = 0;
		}
		e.flip(); // меняем числитель и знаменатель местами
	}
	// повторяем действия для первой "1" в цепной дроби
	e.add_denom(); 
	e.flip();

	// вывод
	if (out) {
		bool irrational = input_mode("irrational");

		if (input_mode("console output")) {
			if (irrational) {
				cout << "\n2.";
				e.output_irrational(cout);
			}
			else cout << endl << e << endl;
		}
		else {
			ofstream out("rational_exp.txt");
			if (irrational) {
				out << "2.";
				e.output_irrational(out);
			}
			else out << e << endl;
			out.close();
		}
	}
}

// проверка сгенерированного числа e с уже имеющимся файлом,
// где рассчитано 2 млн знаков e
void check(const char* filename1, const char* filename2) {

	ifstream file1(filename1);
	if (!file1.is_open()) {
		cout << "File " << filename1 << " is not opened...\n";
		return;
	}

	ifstream file2(filename2);
	if (!file2.is_open()) {
		cout << "File " << filename2 << " is not opened...\n";
		return;
	}

	int i = 0;
	while (file1.get() == file2.get()) i++;
	cout << "Mismatch at " << i++ << " position\n";

}

// шаблон запроса у пользователя информации о выводе
bool input_mode(const char* text) {
	char mode = 0;
	while (mode != 'y' && mode != 'n') {
		cout << "Do you want " << text << " [y/n]?: _\b";
		cin >> mode;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return mode == 'y' ? 1 : 0;
}
