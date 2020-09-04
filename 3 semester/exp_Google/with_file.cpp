#include <iostream>
#include <fstream>
using namespace std;


bool is_prime(long long);
char* read_file(const char*);

int main() {
	char * e = read_file("e_2mil.txt");

	long long number = 0, power = 1e9;
	int start = 0;

	while (true) {
		for (int i = start; i < start + 10; i++, power /= 10)
			number += power * (e[i] % 48); // 48 - code of '0' char

		power = 1e9;
		start++; // shift start-index

		if (is_prime(number)) {
			cout << "Prime number: " << number << " at " << start << " position\n";
			break;
		}
		number = 0;
	}
	delete[] e;

	cin.get();
	return 0;
}

bool is_prime(long long n) {
	if ((n - 1) % 6 == 0 || (n + 1) % 6 == 0) { // any prime number can be represented as 6k +/- 1
		for (long long i = 2; i * i <= n; i++) if (n % i == 0) return false;
		return true;
	}
	return false;
}

char* read_file(const char* name) {
	fstream file(name);
	if (!file.is_open())
		cout << "File is not found...\n";
	else {
		size_t sizeF = file.seekg(0, ios_base::end).tellg();
		char* buffer = new char[sizeF];

		if (!file.seekg(0, ios_base::beg).read(buffer, sizeF)) {
			cout << "Something went wrong...\nMaybe memory error\n";
			return nullptr;
		}
		file.close();
		return buffer;
	}
	return nullptr;
}
