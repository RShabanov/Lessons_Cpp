#pragma once
#include <iostream>

using type = unsigned long long;
const type BASE = 1e12;
const int ORDER_OF_BASE = 12; // log10(BASE)


inline int max(const int&, const int&);

class BigInt {
	type* number;
	int capacity, size;

	void set_data(unsigned int value);
	void clear();

public:
	BigInt();
	BigInt(const BigInt& N);
	BigInt(const unsigned int value, const int& _capacity);
	~BigInt();


	void add(const BigInt& addends);
	void subtract(const BigInt& subtrahend);
	void multiply(const unsigned int& multiplier);


	bool operator<(const BigInt&) const;


	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	friend class RationalExp;
};

class RationalExp
{
	BigInt *numer, *denom, *irrational;
	int capacity, floor;

	void compute_capacity(const unsigned int&);

public:
	RationalExp(const unsigned int);
	RationalExp(const RationalExp&);

	~RationalExp();

	void compute_irrational();
	void output_irrational(std::ostream&);


	friend std::ostream& operator<<(std::ostream&, const RationalExp&);

	void flip();
	void add_denom(const unsigned int& n = 1);

	void compute();
	void compute2(const int& stop, int iter = 1);

};

