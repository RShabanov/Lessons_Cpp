#include <iostream>
using namespace std;

void task14();
bool show_and_check(int, int);
int highest_power(int, int);

int main()
{
  task14();
  system("pause");
  return 0;
}

void task14()
{
	int n, temp, p = 2;
	bool good = true;
	cout << "Enter number: ";
	cin >> n;
	if (!cin || n < 0)
	{
		cout << "Input error!\n";
		return;
	}
	temp = n;
	cout << "p\tn\n";
	while (good)
	{
		cout << p << '\t';
		good = show_and_check(n, p);
		p += good;
	}
	cout << "\nMin. p = " << p << endl;
}

bool show_and_check(int n, int p)
{
	int remainder, power = highest_power(n, p), integer;
	bool good = true;
	while (power)
	{
		integer = n / power;
		if (integer == 0)
			good = false;
		if (integer > 9)
		{
			if (p < 17)
				cout << hex << integer << dec;
			else
				cout << '(' << integer << ')'; //для системы счисления больше 16
		}
		else
			cout << integer;
		if (power <= n)
			n %= power;
		power /= p;
	}
	cout << endl;
	return !good;
}

int highest_power(int n, int p)
{
	int remainder = n % p, power = 1;
	while ((n -= remainder * power) > power)
		remainder = (n / (power *= p)) % p;
	return power;
}
