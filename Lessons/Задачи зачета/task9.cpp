#include <iostream>
#include <ctime>
using namespace std;

void task9();
void fill_array(char ** arr, int m, int n);
int search(char * arr[], int i, int j, int number);

int main()
{
  task9();
  system("pause");
  return 0;
}

void task9()
{
	srand(time(NULL));
	int m = rand() % 10, n = rand() % 10;
	//int m = 5, n = 5;
	if (m < 4 && n < 4)
	{
		cout << "Game field is too small to win...\nInput Error!\n";
		return;
	}
	char** arr = new char*[m];
	for (int i{}; i < m; i++)
		arr[i] = new char[n];

	fill_array(arr, m, n);

	for (int i{}; i < m; i++)
		for (int j{}; j < n; j++)
		{
			if (search(arr, i, j, 1) == 5)
			{
				cout << "Xs can win\n";
				j = n;
				i = m;
				break;
			}
			if (search(arr, i, j, 2) == 5)
			{
				cout << "Os can win\n";
				j = n;
				i = m;
			}
		}
	cout << "No one can win\n";

	for (int i{}; i < m; i++)
		delete[] arr[i];
	delete[] arr;
}

void fill_array(char ** arr, int m, int n)
{
	for (int i{}; i < m; i++)
	{
		for (int j{}; j < n; j++)
			cout << int((arr[i][j] = rand() % 3)) << " "; //где 0 - пусто, 1 - крестики, 2 - нолики 
		cout << endl;
	}
}

int search(char *arr[], int i, int j, int number)
{
	int cross{}, diagonal{}, verticalDOWN{}, verticalUP = 1;
	if (i > 4 && j > 4)
	{
		verticalUP = 0;
		for (int k{}; k < 5; k++)
			if (arr[i - k][j + k] == number)
				verticalUP++;
	}
	for (int k{}; k < 5; k++) 
	{
		if (arr[i][j] == number && arr[i][j + k] == number)
			cross++;
		if (arr[i][j] == number && arr[i + k][j + k] == number)
			diagonal++;
		if (arr[i][j] == number && arr[i + k][j] == number)
			verticalDOWN++;
	}
	return cross * verticalDOWN * verticalUP * diagonal % 5 ? cross : 5; // чтобы не проверять каждое число, проверим их произведение
}
