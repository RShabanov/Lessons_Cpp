#include <iostream>
#include <string>
using namespace std;


const int SIZE = 7;
char romanN[SIZE] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
int arabicN[SIZE] = { 1, 5, 10, 50, 100, 500, 1000 };

string to_roman(int);
int to_arabic(char*);

int main() {
	using namespace std;

	string number;
	START:
	cout << "Please, choose what you need to convert (what do you have otherwise?):\n"
		<< "1) arabic numerals;\n"
		<< "2) roman numerals.\n"
		<< "q - to quit\n"
		<< "Your choice: ";
	getline(cin, number);
	system("cls");
	if (number == "1") {
		cout << "Enter arabic number: ";
		getline(cin, number);
		number = to_roman(stoi(number));
		if (number == "") cout << "Input error!\n";
		else cout << "Your number: " << number << endl;
	}
	else if (number == "2") {
		cout << "Enter roman number: ";
		getline(cin, number);
		int n = to_arabic(&number[0]);
		if (n < 0) {
			cout << "Input error!\n";
			cout << "\n=======================================================================\n\n";
			if (n == -2) {
				cout << "Some of your symbols cannot be roman numerals.\n"
					<< "Roman numerals: I:\t1\n"
					<< "\t\tV:\t5\n"
					<< "\t\tX:\t10\n"
					<< "\t\tL:\t50\n"
					<< "\t\tC:\t100\n"
					<< "\t\tD:\t500\n"
					<< "\t\tM:\t1000\n";
			}
			else if (n == -3) {
				cout << "Wrong order.\n"
					<< "Right order: thousands, hundreds, tens, units\n"
					<< "Some digits (I, X, C, M) can be repeated not more than 3 times in a row\n";
			}
			cout << "\n\n=======================================================================\n\n";
		}
		else cout << "Your number: " << n << endl;
	}
	else if (number != "q") { cout << "Pay attention!\n"; }
	else {
		system("cls");
		cout << "Bye!\n";
		cin.get();
		return 0;
	}
	cin.get();
	goto START;
}

string to_roman(int number) {
	if (number > 0) {
		string roman_number;
		int i = SIZE - 1;
		int power = 1;

		while ((number / power) > 10) power *= 10;
		power /= 10;
		while (number) {
			if (arabicN[i] - (number - number % power) == power) {
				int index10 = i + (i % 2 ? -1 : -2);
				roman_number += romanN[index10];
				roman_number += romanN[i];
				number -= arabicN[i] - arabicN[index10];
			}
			else if (number >= arabicN[i]) {
				roman_number += romanN[i];
				number -= arabicN[i];
			}
			else { i--; }
			if (number / power == 0) power /= 10;
		}
		return roman_number;
	}
	return "";
}

int to_arabic(char* str) {
	int number = 0;
	int index_fst = -1, index_snd = -1;
	int triple = -1;
	*str = toupper(*str);
	do {
		*(str + 1) = toupper(*(str + 1));
		if (*(str + 1)) {
			for (int i = 0; i < SIZE && (index_fst < 0 || index_snd < 0); i++) {
				if (*str == romanN[i]) index_fst = i;
				if (*(str + 1) == romanN[i]) index_snd = i;
			}

			if (index_fst > -1 && index_snd > -1) {
				if ((index_fst == 0 || index_fst == 3) && index_snd > 2 ||
					(index_fst == 2 || index_fst == 5) && index_snd > 4 || 
					index_fst == 1 && index_snd > 0 ||
					(index_fst == 1 || index_fst == 3) && index_fst == index_snd ||
					triple == index_snd) return -3;
				else if (index_fst > index_snd) number += arabicN[index_fst];
				else {
					triple = -1;
					if (index_fst < index_snd) number += arabicN[index_snd] - arabicN[index_fst];
					else {
						number += 2 * arabicN[index_fst];
						triple = index_fst;
					}
					*(str + 1) = toupper(*(++str + 1));
				}
			}
		}
		else if (*(str + 1) == '\0')
			for (int i = 0; i < SIZE; i++) if (*str == romanN[i]) { number += arabicN[i]; break; }
		else
			return -2;
		index_fst = -1, index_snd = -1;
	} while (*++str);

	return number;
}