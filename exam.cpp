#include <iostream>
#include <string>
#include <fstream>
using namespace std;


char* readF(const char*, int&);
void reverse(const char*, const int);
void reverseEveryByte(char*, const int);
char reverseBits(char);
void writeF(const char*, const char*);


int main() {

	cout << "Enter file name (if file is somewhere out this folder, please, enter the path): ";
	string fName;
	getline(cin, fName);

	int size{};
	char* str = readF(&fName[0], size);

	reverse(str, size);
	reverseEveryByte(str, size);

	writeF(&fName[0], str);

	system("pause");
	return 0;
}

char* readF(const char* fName, int& size) {

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

void reverseEveryByte(char *str, const int size) {
	int temp;
	char* newStr = new char[size];

	for (int i = 0; i < size; i++) // изменить порядок
		newStr[i] = reverseBits(str[i]);

	delete[] str;
	str = newStr;
}

char reverseBits(char s) {

	char newS = 0;

	for (int i = 7; i >= 0; i--) {
		if (s >> i) {
			newS += (1 << (7 - i));
			s -= (1 << i);
		}
	}
	return newS;
}

void writeF(const char* fName, const char* str) {

	ofstream  file(fName, ios::binary);
	if (file) {
		file.write(str, sizeof(str));
		file.close();
	}
	else {
		cout << "Error...\nCannot write file...\n";
	}
}
