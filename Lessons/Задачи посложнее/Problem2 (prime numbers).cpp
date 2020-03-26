#include <iostream>
#include <fstream>
using namespace std;

void Prime();
bool NO_Divisors(int, bool)

int main()
{
	Prime();
	cin.get();
	return 0;
}
void Prime()
{
	ifstream file("../../input3.dat");
	ofstream result("../../result3.dat");
	if (!file.is_open())
	{
		cout << "File cannot be opened!\n";
		exit(1);
	}
	int number, temp, power = 1;
	bool prime; 
	while (!file.eof())
	{
		file >> number;
		temp = number;
		prime = NO_Divisors(number, prime);
		if (!prime)
			for (int i = 0; i < 6; i++)
			{
				(number / power % 10 == 0) ? number += 9 * power : number -= power;
				if (!((number - power) / power))
				{
					number = temp;
					break;
				}
				if (prime = NO_Divisors(number, prime))
					break;
				number = temp;
				power *= 10;
			}
		prime ? result << number << endl : result << number << "*" << endl;
		power = 1;
	}
	result.close();
	file.close();
}

bool NO_Divisors(int number, bool prime)
{
	prime = true;
	for (int i = 2; i*i < number; i++)
		if (number % i == 0)
		{
			prime = false; // говорит нам о том, что есть делитель -> число не простое
			break;
		}
	return prime;
}
