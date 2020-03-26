#include <iostream>
using namespace std;

void median();
int main()
{
  median();
  system("pause");
  return 0;
}
void median()
{
	srand(time(0));
	int n, range, temp;
	cout << "Enter size of array: ";
	cin >> n;
	(n <<= 1)++;
	int* values = new int[n], *arr = new int[n];
	for (int i = 0; i < n; i++)
		values[i] = i + 1;
	range = n;
	cout << "Unsorted array:\t";
	for (int i = 0; i < n; i++)
	{
		temp = rand() % range--;
		cout << (arr[i] = values[temp]) << " ";
		values[n - 1 - i] ^= values[temp];
		values[temp] ^= values[n - 1 - i];
		values[n - 1 - i] ^= values[temp];
	}
	cout << "\n\nSorted array:\t";
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1 - i; j++)
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << "\n\nMedian is equal to " << arr[n / 2] << endl;
	delete[] values;
	delete[] arr;
}
