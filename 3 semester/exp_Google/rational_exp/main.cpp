#include <iostream>
#include <iomanip>
#include <fstream>
#include "exp.h"


using namespace std;

void compute_exp_with_fraction(const unsigned int, bool);
void check(const char*, const char*);
bool input_mode(const char*);


int main() {
	
	int number;

	cout << "Enter even number (how many digits you need):\t";
	while (!(cin >> number)) {
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



void compute_exp_with_fraction(unsigned int number, bool out = false) {

	register int cnt = 0;
	Exp e(number);

	number -= 2;
	while (number) {
		if (cnt++ < 2) e.add_denom();
		else {
			e.add_denom(number);
			number -= 2;
			cnt = 0;
		}
		e.flip();
	}
	e.add_denom();
	e.flip();

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

bool input_mode(const char* text) {
	char mode = 0;
	while (mode != 'y' && mode != 'n') {
		cout << "Do you want " << text << " [y/n]?: _\b";
		cin >> mode;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return mode == 'y' ? 1 : 0;
}
