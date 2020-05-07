//Пользователь вводит double / float (десятичное число).
//Необходимо вывести это же число в двоичном виде

#include <iostream>
#include <locale.h>
using namespace std;

void ToBinary(int arr[], int start, int end, long long number);

int main()
{
	setlocale(LC_ALL, "ru");
	int type, size, exponent;
	double number;
	cout << "Укажите тип данных (1 - float, 2 - double): ";
	cin >> type;
	while (cin.fail() || type < 1 || type > 2)
	{
		cin.clear();
		cin.ignore();
		cout << "Введите тип данных снова: ";
		cin >> type;
	}
	cout << "Введите число: ";
	cin >> number;
	if (type == 1)
	{
		size = sizeof(float) << 3;
		exponent = 8;
	}
	else
	{
		exponent = 11;
		size = sizeof(double) << 3;
	}
	//Action(number, size, exponent);
	int count = 0, offset_exponent;
	int *line = new int[size] {};
	if (number < 0)
	{
		line[0] = 1; // определяем знак
		number = -number;
	}
	long long num = int(number); //присваиваем целую часть
	number -= int(number); //находим то, что после точки
	while ((number - int(number) > 0.0000001)) //приводим к "целому" числу
	{
		number *= 10;
		count--; //порядок
	}
	offset_exponent = ((1 << (exponent - 1)) - 1) + count;
	count = -count;
	for (int i = 0; i < count; i++) //двигаем число num на count позиций
		num *= 10;
	num += (long long)number; //находим мантиссу
	ToBinary(line, exponent, 1, offset_exponent); //переводит смещенную экспоненту в двоичный код
	ToBinary(line, size - 1, exponent + 1, num); //переводит число в двоичный код
	for (int i = 0; i < size; i++)
	{
		if (i == 1 || i == (exponent + 1))
			cout << '.';
		cout << line[i];
	}
	cout << endl << endl;
	delete[] line;
	system("pause");
	return 0;
}

void ToBinary(int arr[], int start, int end, long long number)
{
	for (int i = start; i >= end; i--)
	{
		(number - ((number >> 1) << 1)) == 0 ? arr[i] = 0 : arr[i] = 1;
		number >>= 1;
		if (number == 0)
			break;
	}
}
