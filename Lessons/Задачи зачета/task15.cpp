#include <iostream>
using namespace std;

void task15();
long long to_power(int n, int power);

int main()
{
  task15();
  system("pause");
	return 0;
}

void task15()
{
	int k, power = 1, i = 0;
	cout << "Enter k: ";
	cin >> k;
	if (k < 1 && !cin)
	{
		cout << "Input error!\n";
		return;
	}
	for (i; k - power > 0; i++)
	{
		k -= power;
		power += bool(i / to_power(10, power));
	}
	power -= k*(i != 9);
	if (i == 10) // для числа 11
		power = 0;
	if (i < 10)
		i++;
	cout << i / to_power(10, power) % 10 << '\t';
}

long long to_power(int n, int power)
{
	long long result = 1;
	if (n == 1)
		return 1;
	else if (!n)
		return 0;
	while (power--)
		result *= n;
	return result;
}

// ленивый и затратный способ со string
/*
#include <string>
void task15()
{
	string str;
	int k;
	cout << "Enter k: ";
	cin >> k;
	if (k < 1 && cin)
	{
		cout << "Input error!\n";
		return;
	}
	for (int i = 0; i <= k; i++)
		str += to_string(i);
	cout << str[k] << endl;
}
*/
