#include <iostream>
using namespace std;

void Narcissistic_number();
long long to_power(int n, int power);

int main()
{
  Narcissistic_number();
  system("pause");
  return 0;
}

void Narcissistic_number()
{
	int power = 1;
	long long sum{};
	for (int i = 0; i < 1000000; i++)
	{
		for (int k = i; k; k /= 10)
			sum += to_power(k % 10, power);
		if (sum == i)
			cout << sum << endl;
		power += bool(i / to_power(10, power));
		sum = 0;
	}
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
