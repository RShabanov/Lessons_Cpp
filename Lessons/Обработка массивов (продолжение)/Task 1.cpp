#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;

// 1
int main()
{
	srand(time(0));
	int SIZE, d;
	cout << "Enter size of matrix: ";
	cin >> SIZE;
	int **arr = new int*[SIZE];
	for (int i = 0; i < SIZE; i++)
		arr[i] = new int[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			arr[i][j] = rand() % 100;
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < SIZE; i++)
	{
		d = arr[i][i];
		for (int j = 0; j < SIZE; j++)
			arr[j][i] /= d;
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	
	if (arr != 0)
	{
		for (int i = 0; i < SIZE; i++)
			delete[] arr[i];
		delete[] arr;
	}
	system("pause");
	return 0;
}
