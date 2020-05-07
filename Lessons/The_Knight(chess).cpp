// The_Knight(chess).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <locale.h>

int main()
{
	using namespace std;
	setlocale(LC_ALL, "ru");
	int N, count = 0;
	cout << "Введите в каком пространстве необходимо найти количество ходов коня: ";
	cin >> N;
	if (N <= 0)
	{
		cout << "Ошибка ввода!\n";
		return 0;
	}
	int *arrCoordinates = new int[N];
	cout << "Введите координаты коня через пробел: ";
	for (int i = 0; i < N; i++)
		cin >> arrCoordinates[i];
	for (int i = 0; i < N; i++) // проверяет находится ли конь на доске, т.е. каждая координата в пределах от 1 до 8 включительно 
		if (arrCoordinates[i] < 1 || arrCoordinates[i] > 8)
		{
			cout << "Конь не находится на доске!\n";
			return 0;
		}
	for (int i = 0; i < N - 1; i++) // данный цикл можно описать формулой n*(n-1)/2
	{
		for (int j = i; j < N; j++)
		{
			if (i != j) // проверяет позицию коня, т.е. останется конь на доске после хода
			{
				if ((arrCoordinates[i] - 1) > 0 && (arrCoordinates[j] - 2 > 0))
					count++;
				if ((arrCoordinates[i] - 1) > 0 && (arrCoordinates[j] + 2 <= 8))
					count++;
				if ((arrCoordinates[i] - 2) > 0 && (arrCoordinates[j] - 1 > 0))
					count++;
				if ((arrCoordinates[i] - 2) > 0 && (arrCoordinates[j] + 1 <= 8))
					count++;
				if ((arrCoordinates[i] + 1) <= 8 && (arrCoordinates[j] - 2 > 0))
					count++;
				if ((arrCoordinates[i] + 1) <= 8 && (arrCoordinates[j] + 2 <= 8))
					count++;
				if ((arrCoordinates[i] + 2) <= 8 && (arrCoordinates[j] - 1 > 0))
					count++;
				if ((arrCoordinates[i] + 2) <= 8 && (arrCoordinates[j] + 1 <= 8))
					count++;
			}
		}
	}
	cout << "Количество ходов коня: " << count << endl;
	delete[] arrCoordinates;
	return 0;
}
