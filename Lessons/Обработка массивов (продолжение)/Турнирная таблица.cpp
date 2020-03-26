#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	int n;
	cout << "Enter amount of players: ";
	cin >> n;
	int** pArr = new int*[n];
	for (int i = 0; i < n; i++)
		pArr[i] = new int[n] {};

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				pArr[j][i] = pArr[i][j] = 0;
			else
				pArr[i][j] = rand() % 10;
			cout << pArr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			pArr[i][i] += pArr[i][j] - pArr[j][i];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << pArr[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < n; i++)
		delete[] pArr[i];
	delete[] pArr;
	system("pause");
	return 0;
}
