#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	int size;
	float sum{};
	cout << "Enter size of array: ";
	cin >> size;
	float* pArr = new float[size];
	for (int i = 0; i < size; i++)
		cout << (pArr[i] = rand() % 100) << " ";
	cout << endl << "\nNew array:\n" << fixed << setprecision(2);
	for (int i = 0; i < size; i++)
		cout << (sum += pArr[i]) / (i + 1) << " ";
	cout << endl;
	delete[] pArr;
	system("pause");
	return 0;
}
