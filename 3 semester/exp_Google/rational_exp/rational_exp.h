#pragma once
#include <iostream>
#include <iomanip>


using ull = unsigned long long;
//using ull = unsigned int;
//using ull = unsigned short;

const ull BASE = 1e12;

int define_accuracy(int);


class Exp {
	ull *numer = nullptr, *denom = nullptr,*ir_number = nullptr;
  int size;

	void set_data(ull*, int, const int);

	int compare(ull*, ull*, const int) const;
	void div(const int);
	void copy(ull*, ull*, const int);
	void add(ull*, ull*, const int);
	void subtract(ull*, ull*, const int);
	void shift(ull*, const int, const int);

public:
	Exp(const unsigned int);
	Exp(const Exp&);

	~Exp();

	void irrational();
	void output_irrational(std::ostream&);

	Exp add_denom(const unsigned int n = 1);
	void multiply_denom(const unsigned int);

	friend std::ostream& operator << (std::ostream&, const Exp&);

	void flip();
};
