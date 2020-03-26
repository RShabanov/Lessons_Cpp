#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	int n, m;
	cout << "Enter size of array: ";
	cin >> n;
	int *pa = new int[n];
	cout << "Your array: ";
	for (int i = 0; i < n; i++)
		cout << (pa[i] = rand() % 100) << " ";
	cout << "\n\nEnter shift: ";
	cin >> m;
	m %= n;
	for (int i = 0, temp = *pa, buffer_value;;)
	{
		i = n - 1 - (n - 1 - i + m) % n; // определение положения (индекса) после сдвига
		buffer_value = pa[i];
		pa[i] = temp;
		temp = buffer_value;
		if (i == 0) break;
	}
	cout << "Your array now: ";
	for (int i = 0; i < n; i++)
		cout << pa[i] << " ";
	cout << endl;
	delete[] pa;	
	system("pause");
	return 0;
}
