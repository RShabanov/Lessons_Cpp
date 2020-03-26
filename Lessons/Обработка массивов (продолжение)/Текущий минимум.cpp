#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	int size;
	float min = 100;
	cout << "Enter size of array: ";
	cin >> size;
	int* pArr = new int[size];
	for (int i = 0; i < size; i++)
		cout << (pArr[i] = rand() % 100) << " ";
	cout << endl << "\nNew array:\n";
	for (int i = 0; i < size; i++)
	{
		if (pArr[i] < min)
			min = pArr[i];
		pArr[i] = min, cout << pArr[i] << " ";
	}
	cout << endl;
	delete[] pArr;
	system("pause");
	return 0;
}
