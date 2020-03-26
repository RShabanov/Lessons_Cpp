#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	const int SIZE = 8;
	bool king = true; // короля можно поставить
	int r, x_king, y_king, min = SIZE; // уменьшим количество ферзей
	int arr[SIZE][SIZE]{}, distance[3][3]{ {8,8,8},{8,8,8},{8,8,8} };
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 1)
				continue;
			r = rand() % 3;
			if (king && r == 1)
			{
				x_king = rand() % 8;
				y_king = rand() % 8;
				arr[x_king][y_king] = r; // генерируем рандомное место для короля
				king = false;
			}
			else if (r == 2)
				arr[i][j] = r;
		}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	for (int i{}; i < SIZE; i++)
		for (int j{}; j < SIZE; j++)
			if (arr[i][j] == 2)
			{
				if (i < x_king)
				{
					if ((x_king - i) == (y_king - j) && abs(distance[0][0]) > abs(i - x_king))
						*distance[0] = i - x_king;
					else if ((x_king - i) == (j - y_king) && abs(distance[0][2]) > abs(x_king - i))//!!!
						distance[0][2] = x_king - i;
				}
				else
				{
					if ((i - x_king) == (y_king - j) && abs(distance[2][0]) > abs(i - x_king))
						*distance[2] = i - x_king;
					else if ((i - x_king) == (j - y_king) && abs(distance[2][2]) > abs(i - x_king))
						distance[2][2] = i - x_king;
				}
				if (y_king == j)
				{
					if (i > x_king && abs(distance[2][1]) > abs(i - x_king))
						distance[2][1] = i - x_king;
					else if (i <= x_king && abs(distance[0][1]) > abs(i - x_king))
						distance[0][1] = i - x_king;
				}
				else if (x_king == i)
				{
					if (j > y_king && abs(distance[1][2]) > abs(j - y_king))
						distance[1][2] = j - y_king;
					else if (j <= y_king && abs(*(distance[1])) > abs(j - y_king))
						*(distance[1]) = j - y_king;
				}
			}
	cout << endl << endl << "Coordinates of queen(s) which is dangerous for the king:\n";
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (distance[i][j] < 8)
			{
				if (i == 0 && j == 2)
					cout << "(" << x_king - (*distance)[j] + 1 << ";" << y_king + (*distance)[j] + 1 << ")" << endl;
				else if (i == 2 && j == 0)
					cout << "(" << x_king + distance[i][j] + 1 << ";" << y_king - distance[i][j] + 1 << ")" << endl;
				else if (j == 1)
					cout << "(" << x_king + distance[i][j] + 1 << ";" << y_king + 1 << ")" << endl;
				else if (i == 1)
					cout << "(" << x_king + 1 << ";" << y_king + distance[i][j] + 1 << ")" << endl;
				else
					cout << "(" << x_king + distance[i][j] + 1 << ";" << y_king + distance[i][j] + 1 << ")" << endl;
			}
	system("pause");
	return 0;
}
