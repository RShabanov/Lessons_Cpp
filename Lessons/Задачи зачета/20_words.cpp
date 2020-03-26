#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void task7();
bool availability(const char*, char**, int&, int []);
char** append(const char*, const int, char**, int, int []);
int* append(int [], int&);

int main()
{
  task7();
  system("pause");
  return 0;
}

void task7() 
{
	ifstream file("../text.txt");
	if (!file.is_open())
	{
		cout << "File is not found!\n";
		return;
	}
	string word = "";

	int* word_amount = new int[1]{0};
	char** words = new char*[1];

	words[0] = new char[0];
	words[0] = &word[0];
	int size = 0, wordLen{};

	MetNumber:
	while (!file.eof())
	{
		file >> word;
		wordLen = word.length();
		for (int i{}; i < wordLen; i++)
		{
			if (!isalpha(unsigned char(word[i])))
				goto MetNumber;
			word[i] = tolower(word[i]);
		}
		if (availability(&word[0], words, size, word_amount)) //если нет такого слова, добавляем
		{
			words = append(&word[0], wordLen, words, size, word_amount);
			word_amount = append(word_amount, size);
		}
	}
	cout << "20 most common words:\n\n";

	for (int i{}, max{}, index{}; i < 20; i++)
	{
		for (int j{}; j < size; j++)
			if (max < word_amount[j])
			{
				max = word_amount[j];
				index = j;
			}
		cout << i + 1 << ") ";
		//cout << setw((i + 1 > 9 ? 20 : 21)) << left << words[index] << ':';
		cout << '\t' << word_amount[index] << endl;
		max = word_amount[index] = 0;
	}

	for (int i{}; i < size; i++)
		delete[] words[i];
	delete[] words;
	delete[] word_amount;

	file.close();
}

bool availability(const char* word, char** words, int& size, int amount[])
{
	int i{};
	for (i; i < size; i++)
		if (!strcmp(word, words[i]))
		{
			amount[i]++;
			break;
		}
	return i == size;
}

char** append(const char* word, const int WordLen, char** words, int size, int amount[])
{
	char** ptrArr = new char*[size + 1];
	for (int i{}; i < size; i++)
		ptrArr[i] = new char[strlen(words[i]) + 1];
	ptrArr[size] = new char[WordLen + 1];

	for (int i{}, length; i < size; i++)
	{
		length = strlen(words[i]) + 1;
		for (int j{}; j < length; j++)
			ptrArr[i][j] = words[i][j];
	}

	for (int i{}; i < WordLen + 1; i++)
		ptrArr[size][i] = word[i];

	char** tempPtr = words;
	words = ptrArr;
	ptrArr = tempPtr;

	for (int i{}; i < size; i++)
		delete[] ptrArr[i];
	delete[] ptrArr;

	return words;
}

int* append(int arr[], int& size)
{
	int* new_arr = new int[size + 1];
	for (int i{}; i < size; i++)
		new_arr[i] = arr[i];
	new_arr[size] = 1;

	int* tempPtr = arr;
	arr = new_arr;
	new_arr = tempPtr;
	delete[] new_arr;
	size++;
	return arr;
}
