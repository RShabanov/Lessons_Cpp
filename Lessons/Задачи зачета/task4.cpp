#include <iostream>
using namespace std;

void task4();
void fill_array(int ** , int);
int ** turn_matrix(int **, int);

int main()
{
  task4();
  system("pause");
  return 0;
}

void task4()
{
	srand(time(NULL));
	int n, degrees;
	cout << "Enter matrix's size: ";
	cin >> n;
	if (!cin || n < 1)
	{
		cout << "Input error!\nWrong size of matrix\n";
		return;
	}
	int** arr = new int*[n];
	for (int i{}; i < n; i++)
		arr[i] = new int[n];

	fill_array(arr, n);
	for (int i{}; i < n; i++)
	{
		for (int j{}; j < n; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
	cout << "\nMatrix turned on 90 degrees\n";
	arr = turn_matrix(arr, n);
	for (int i{}; i < n; i++)
	{
		for (int j{}; j < n; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}

	for (int i{}; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}

void fill_array(int ** arr, int SIZE)
{
	for (int i{}; i < SIZE*SIZE; i++)
		arr[i / SIZE][i % SIZE] = i + 1;
}

int ** turn_matrix(int ** arr, int SIZE)
{
	int ** ptrArr = arr;
	int ** new_arr = new int*[SIZE];
	for (int i{}; i < SIZE; i++)
		new_arr[i] = new int[SIZE];

	for (int i{}; i < SIZE; i++)
		for (int j{}; j < SIZE; j++)
			new_arr[j][SIZE - i - 1] = arr[i][j];

	arr = new_arr;
	new_arr = ptrArr;

	for (int i{}; i < SIZE; i++)
		delete[] new_arr[i];
	delete[] new_arr;
	return arr;
}
