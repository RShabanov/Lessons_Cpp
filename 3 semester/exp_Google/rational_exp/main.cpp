#include <iostream>
#include <ctime>
#include <fstream>
#include "RationalExp.h"
using namespace std;


void compare_e(const char* filename1, const char* filename2);

int main() {
	double start = clock();
	RationalExp e(200000);
	e.compute();
	double end = (clock() - start) / 1e3;
	cout << "Time:\t" << end << endl;
	
	ofstream time_file("time.txt", ios_base::app);
	time_file << end << endl;
	time_file.close();


	ofstream file("e_by_fractions.txt");
	if (file.is_open()) {
		e.output_irrational(file);
		file.close();
	}

	compare_e("e_by_fractions.txt", "e_2mil.txt");
	cout << "Done!\a\n";
	
	system("pause");
	return 0;
}

void compare_e(const char* filename1, const char* filename2) {

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
