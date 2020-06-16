#include <iostream>
#include <string>
#include <fstream>
#include <climits>
using namespace std;


char* read(int&);
void reverse(const char*, const int);
void reverseEveryBit(const char*, const int);
void write(char*);


int main() {

	char* str = read(size);

	reverse(str, size);


	system("pause");
	return 0;
}

char* read(int& size) {
	cout << "Enter file name (if file is somewhere out this folder, please, enter the path): ";
	string fName;
	getline(cin, fName);

	ifstream file(fName, ios_base::binary | ios_base::in);


	if (!file.is_open())
		cout << "File is not found...\n";
	else {
		size_t sizeF = file.seekg(0, ios_base::end).tellg();
		char* buffer = new char[sizeF];

		size = sizeF;

		if (!file.seekg(0, ios_base::beg).read(buffer, sizeF)) {
			cout << "Something went wrong...\nMaybe memory error\n";
			return nullptr;
		}
		file.close();
		return buffer;
	}
	return nullptr;
}

void reverse(const char* str, const int size) {

	char* newStr = new char[size];
	
	for (int i = 0; i < size; i++)
		newStr[i] = str[size - 1 - i];

	delete[] str;

	str = newStr;
}

void reverseEveryBit(const char *str, const int size) {
	int temp;
	char* newStr = new char[size];

	for (int i = 0; i < size; i++) { // изменить порядок
		
	}
}
