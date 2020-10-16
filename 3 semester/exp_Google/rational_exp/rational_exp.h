#pragma once
#include <iostream>
#include <iomanip>


using ull = unsigned long long;
//using ull = unsigned int;
//using ull = unsigned short;

const ull BASE = 1e12;

// рассчитывает возможную точность для числа при 2n этажей
int define_accuracy(int);


class Exp {
	ull *numer = nullptr, *denom = nullptr,*ir_number = nullptr;
  int size;

	void set_data(ull*, int, const int);

	// сравнивает 2 длинных числа
	int compare(ull*, ull*, const int) const;
	
	// деление дроби числитель / знаменатель
	void div(const int);
	
	// копирование длинных чисел
	void copy(ull*, ull*, const int);
	
	// добавляет к одному длинному числу другое
	void add(ull*, ull*, const int);
	
	// вычитает из одного длинного числа другое
	void subtract(ull*, ull*, const int);
	
	// домножение числа на 10
	void shift(ull*, const int, const int);

public:
	Exp(const unsigned int);
	Exp(const Exp&);

	~Exp();

	// рассчет иррационального числа
	void irrational();
	
	// вывод иррационального числа
	void output_irrational(std::ostream&);

	// вычисляет значение числителя:
	// numer + k * denom
	// где k - либо 2n, либо 1
	Exp add_denom(const unsigned int n = 1);
	
	// домножает знаменатель на k
	void multiply_denom(const unsigned int);

	friend std::ostream& operator << (std::ostream&, const Exp&);

	// меняет числитель и знаменатель местами
	void flip();
};
