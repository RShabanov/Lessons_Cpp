#include <iostream>
#include <ctime>
using namespace std;

void task2();

int main()
{
  task2();
  system("pause");
  return 0;
}

void task2()
{
	srand(time(0));
	int n;
	cout << "Enter size of cube: ";
	if (!(cin >> n) || n < 0)
	{
		cout << "Input error!\n";
		return;
	}
	bool *** cube = new bool**[n];
	for (int i{}; i < n; i++)
		cube[i] = new bool*[n];
	for (int i{}; i < n; i++)
		for (int j{}; j < n; j++)
			cube[i][j] = new bool[n];

	cout << "Cube:\n";
	// filling array
	for (int i{}; i < n; i++)
	{
		for (int j{}; j < n; j++)
		{
			for (int k{}; k < n; k++)
				cout << (cube[i][j][k] = rand() % 2) << "\t";
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	//
	cout << "\nCoordinates of transparent cubes:\n";
	for (int i{}; i < n; i++)
		for (int j{}; j < n; j++)
			for (int k{}; k < n; k++)
				if (cube[i][j][k] == 0)
				{
					int l{}, m{};
					bool state = true;
					if (j == 0 || j == n - 1 || k == 0 || k == n - 1 || i == 0 || i == n - 1)
					{
						cout << '(' << i << ", " << j << ", " << k << ')' << endl;
						state = false;
					}
					if (state && (cube[i][j][k - 1] == 0 || cube[i][j][k + 1] == 0))
					{
						for (l = k - 2; l > 0 && cube[i][j][l] == 0; l--);
						for (m = k + 2; m < n && cube[i][j][m] == 0; m++);
						if (l == 0 || m == n)
						{
							state = false;
							cout << '(' << i << ", " << j << ", " << k << ')' << endl;
						}
					}
					if (state && (cube[i][j + 1][k] == 0 || cube[i][j - 1][k] == 0))
					{
						for (l = j - 2; l > 0 && cube[i][l][k] == 0; l--);
						for (m = j + 2; m < n && cube[i][m][k] == 0; m++);
						if (l == 0 || m == n)
						{
							state = false;
							cout << '(' << i << ", " << j << ", " << k << ')' << endl;
						}
					}
					if (state && (cube[i + 1][j][k] == 0 || cube[i - 1][j][k] == 0))
					{
						for (l = i - 2; l > 0 && cube[l][j][k] == 0; l--);
						for (m = i + 2; m < n && cube[m][j][k] == 0; m++);
						if (l == 0 || m == n)
						{
							state = false;
							cout << '(' << i << ", " << j << ", " << k << ')' << endl;
						}
					}
				}

	for (int i{}; i < n; i++)
		for (int j{}; j < n; j++)
			delete[] cube[i][j];
	for (int i{}; i < n; i++)
		delete[] cube[i];
	delete[] cube;
}
