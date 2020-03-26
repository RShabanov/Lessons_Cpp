#include <iostream>
#include <cmath>
using namespace std;

void prime_numbers_ISBN();
bool check_digit(long long);
void prime_number(long long, long long, bool&, bool&);

int main()
{
  prime_numbers_ISBN();
  system("pause");
  return 0;
}

void prime_numbers_ISBN()
{
	long long before, after;
	bool prime_before = true, prime_after = true;
	for (long long i = 1000000002, j; i < 10000000000; i += 6) // все простые числа можно представить в виде 6*k +/- 1
	{
		before = i - 1;
		after = i + 1;
		prime_number(before, after, prime_before, prime_after);

		if (prime_before && check_digit(before))
			cout << before << endl;

		if (prime_after && check_digit(after))
			cout << after << endl;

		if (i % 60 == 0) // чтобы не создавать второй подобный цикл, проверяет простые числа с 'X' на конце
		{
			prime_before = prime_after = true;
			before = i / 10 - 1;
			after = i / 10 + 1;
			prime_number(before, after, prime_before, prime_after);

			if (prime_before && check_digit(before))
				cout << before << 'X' << endl;

			if (prime_after && check_digit(after))
				cout << after << 'X' << endl;
		}
		prime_before = prime_after = true;
	}
}

bool check_digit(long long i)
{
	int sum{};
	bool amount_digit = (floor(log10(i)) + 1) < 10; // (floor(log10(i)) + 1 - находит количество цифр числа. Спасибо proglib (https://proglib.io/p/top-10-tryukov-na-c-kotorye-oblegchat-vam-zhizn-2019-12-10?utm_referrer=https%3A%2F%2Fzen.yandex.com)
	for (int k = 1 + amount_digit, power10 = 10; i > 0; k++, i /= 10) // ((floor(log10(i)) + 1) < 10 - проверяет количество цифр числа, переданного функции, если < 10, то в последующем будет выполнено sum += 10
		sum += i % power10 * k;
	if (amount_digit)
		sum += 10; // заменяем Х, если необходимо
	return sum % 11 == 0;
}

void prime_number(long long bnumber, long long anumber, bool& bprime, bool& aprime)
{
	for (long long j = 2; j * j < anumber && (bprime || aprime); j++)
	{
		if (bprime && bnumber % j == 0 && j * j < bnumber)
			bprime = false;
		if (aprime && anumber % j == 0)
			aprime = false;
	}
}
