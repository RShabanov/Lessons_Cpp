#include <iostream>
#include <ctime>
using namespace std;

void task5();

int main()
{
  task5();
  system("pause");
  return 0;
}

void task5()
{
	srand(time(NULL));
	int n; 
	cout << "Enter size of array: ___\b\b\b";
	if (!(cin >> n) || n < 0)
	{
		cout << "Input error!\n";
		return;
	}
	int* arr = new int[2 * n];
	int* arrB = new int[n];
	int* arrC = new int[n];
	cout << "Main array:\t";
	for (int i{}; i < 2 * n; i++)
		cout << (arr[i] = rand() % 100) << "\t";

	for (int i{}, k{}, min = abs(arr[i] - arr[i + 1]), index{}; i < 2 * n - 1; i += 2, k++)
	{
		for (int j{ i + 1 }; j < 2 * n; j++)
			if (abs(arr[i] - arr[j]) <= min)
			{
				min = abs(arr[i] - arr[j]);
				index = j;
			}
		arrB[k] = arr[i] < arr[index] ? arr[i] : arr[index];
		arrC[k] = arrB[k] + min;
		min = arr[index]; 
		arr[index] = arr[i + 1];
		arr[i + 1] = min;
		if (i + 3 < 2*n)
			min = abs(arr[i + 2] - arr[i + 3]);
	}

	cout << "\n\nArray B: ";
	for (int i{}; i < n; i++)
		cout << arrB[i] << "\t";
	cout << "\n\nArray C: ";
	for (int i{}; i < n; i++)
		cout << arrC[i] << "\t";
	cout << endl;

	delete[] arr;
	delete[] arrB;
	delete[] arrC;
}
