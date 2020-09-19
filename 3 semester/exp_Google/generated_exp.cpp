#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;


typedef unsigned long long ull;

ull base = 1e12;
ull N = 1e6; // количество разрядов exp
ull K = N / log10(base) + 1; // количество элементов массива


void set_data(ull*, const ull&, const int&);

bool is_zero(const ull*, int);

void add(ull*, const ull*, int);

void divide(ull*, const int&);

void output(ostream& out, const ull* e, const int& size);

bool check(const char*, const char*);


int main() {
	double start = clock();

	ull* e = new ull[K]; 
	ull* div_f = new ull[K]; // обратный факториал
	
	set_data(e, K * sizeof(ull), 1);
	set_data(div_f, K * sizeof(ull), 1);

	int number = 1; 
	while (!is_zero(div_f, K)) {
		divide(div_f, number);
		add(e, div_f, K);
		number++;
	}

	cout << "Time:\t" << (clock() - start) / 1000.0 << endl;

	// вывод в файл
	ofstream fout("generated_exp.txt");
	output(fout, e, K);
	fout.close();
  
	cout << check("e_2mil.txt", "generated_exp.txt") << endl;

	// вывод в консоль
	//output(cout, e, K);

	system("pause");
	return 0;
}


void set_data(ull* arr, const ull& size, const int& first = 0) {
	memset(arr, 0, size);
	arr[0] = first;
}

bool is_zero(const ull* arr, int size) {
	while (size--) 
		if (arr[size]) return false;
	return true;
}

void add(ull* fst, const ull* snd, int size) {
	register int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		fst[i] += snd[i] + carry;
		if (carry = (fst[i] >= base)) fst[i] -= base;
	}
}

void divide(ull* numerator, const int& denominator) {
	register ull carry = 0, xi;
	for (int i = 0; i < K; i++) {
		xi = numerator[i] + carry * base;
		numerator[i] = ull(xi / denominator);
		carry = ull(xi % denominator);
	}
}

void output(ostream& out, const ull* e, const int& size) {
	int order = log10(base);
	for (int i = 0; i < size; i++) {
		if (i > 0) out << setfill('0') << setw(order);
		out << e[i];
		if (!i) out << '.';
	}
}

bool check(const char* filename1, const char* filename2) {

	ifstream file1(filename1);
	if (!file1.is_open()) {
		cout << "File " << filename1 << " is not opened...\n";
		return -1;
	} 
	ifstream file2(filename2);
	if (!file2.is_open()) {
		cout << "File " << filename2 << " is not opened...\n";
		return -2;
	}

	int i = 0;
	while (true || i < N) {
		if (file1.get() != file2.get()) {
			cout << "Mismatch at " << i + 1 << " position\n";
			return false;
		}
		i++;
	}

	return true;
}
