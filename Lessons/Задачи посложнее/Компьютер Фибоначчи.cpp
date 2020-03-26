#include <iostream>
#include <cmath>
using namespace std;

void Fibonacci();
int main()
{
  Fibonacci();
  system("pause");
  return 0;
}
void Fibonacci()
{
	const long double sqrtFive = sqrt(5);
	int n, j{};
	cout << "Enter your number: ";
	cin >> n;
	if (n < 0 || n > 109)
	{
		cout << "Input error!\n";
		exit(1);
	}
	for (j; (pow((1 + sqrtFive) / 2, j) - pow((1 - sqrtFive) / 2, j)) / sqrtFive < n; j++); //находим количество чисел фибоначчи с помощью золотого сечения

	long double* FNumbers = new long double[j] {1, 1};
	char* str = new char[j];
	for (int i = 2; i < j; i++) //заполняем массив числами Фибоначчи
		FNumbers[i] = FNumbers[i - 1] + FNumbers[i - 2];
	for (int i = j - 1; i >= 0; i--)
	{
		(n - FNumbers[i] >= 0) ? str[i] = 1, n -= FNumbers[i] : str[i] = 0;
		cout << int(str[i]);
	}
	cout << endl;
	delete[] str;
	delete[] FNumbers;
}
