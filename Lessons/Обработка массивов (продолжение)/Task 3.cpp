#include <iostream>
#include <ctime>

int main()
{
  	using namespace std;
  	srand(time(0));
	int n, sum{};
	cout << "Enter size of array: ";
	cin >> n;
	int* pArr = new int[n];
	for (int i = 0; i < n; i++)
		cout << (pArr[i] = rand() % 100) << " ", sum += pArr[i];
	cout << endl << endl;
	for (int i = n - 1; i > 0; i--)
		pArr[i] = (sum -= pArr[i]);
	for (int i = 0; i < n; i++)
		cout << pArr[i] << " ";
	cout << endl;
	delete pArr;
	system("pause");
	return 0;
}  
