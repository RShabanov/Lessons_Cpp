#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	int SIZE;
	cout << "Enter size of matrix: ";
	cin >> SIZE;
	int* arr = new int[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 100;
		cout << arr[i] << " ";
	}
	cout << endl << "Your index: ";
	for (int i = 1; i < SIZE - 1; i++)
		if (arr[i - 1] < arr[i] && arr[i] > arr[i+1])
			cout << i << " ";
	delete[] arr;
	system("pause");
	return 0;
}
