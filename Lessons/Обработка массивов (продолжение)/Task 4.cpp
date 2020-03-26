#include <iostream>
using namespace std;

// Поскольку в задаче не сказано, что необходимо заполнять массив всеми числами, мы это сделаем
int main()
{
	int m, n, filler = 1;
	cout << "Enter space-separated size of matrix (M x N): ";
	cin >> m >> n;
	if (((m < 2 || n < 2) && (m != 1 && m < 4 || n != 1 && n < 4) || (m == 1 && n == 1)))
	{
		cout << "Matrix is not big enough to fill the matrix numbers or input error!\n";
		return -1;
	}
	int** ptrArr = new int*[m];
	for (int i = 0; i < m; i++)
		ptrArr[i] = new int[n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++, filler++)
		{
			if (m == 1 || n == 1)
			{
				ptrArr[i][j] = filler;
				if (filler > 3)
					filler = 0;
			}
			else
			{
				if (j % 2 == 0)
				{
					if (i % 2 != 0)
						ptrArr[i][j] = 1;
					else
						ptrArr[i][j] = 3;
				}
				else
				{
					if (i % 2 != 0)
						ptrArr[i][j] = 2;
					else
						ptrArr[i][j] = 4;
				}
			}
			cout << ptrArr[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < m; i++)
		delete[] ptrArr[i];
	delete[]ptrArr;
	system("pause");
	return 0;
}
