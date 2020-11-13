#pragma once
#include <iostream>

class Rational {
	typedef long long LL;
	LL numer, denom;
public:
	Rational();
	Rational(int);
	Rational(int, int);

	Rational& operator += (const Rational&);
	Rational operator + (const Rational&);
	Rational operator - (const Rational&);
	Rational operator - () const;
	Rational& operator -= (const Rational&);
	Rational& operator /= (const Rational&);
	Rational operator / (const Rational&);
	Rational& operator *= (const Rational&);
	Rational operator * (const Rational&);

	template<typename T> Rational& operator+= (const T&);
	template<typename T> Rational operator+ (const T&);
	template<typename T> Rational operator- (const T&);
	template<typename T> Rational& operator-= (const T&);
	template<typename T> Rational& operator/= (const T&);
	template<typename T> Rational operator/ (const T&);
	template<typename T> Rational& operator*= (const T&);
	template<typename T> Rational operator* (const T&);


	Rational& operator=(const Rational&);
	template<typename T> Rational& operator=(T value) { return *this = Rational(value); };


	// increment & decrement
	Rational& operator ++();
	Rational operator ++(int);
	Rational& operator --();
	Rational operator --(int);

	// comparison operations
	bool operator == (const Rational&);
	bool operator != (const Rational&);
	bool operator > (const Rational&);
	bool operator >= (const Rational&);
	bool operator < (const Rational&);
	bool operator <= (const Rational&);

	// type transformation
	operator int() const;
	operator double() const;

	// streams
	friend std::istream& operator >> (std::istream&, Rational&);
	friend std::ostream& operator << (std::ostream&, const Rational&);


	void simplify();

	// getters & setters
	void set_numerator(int);
	void set_denominator(int);
	int get_numerator();
	int get_denominator();
};


template<typename T> 
Rational& Rational::operator+= (const T& value) {
	numer += value * denom;
	simplify();
	return *this;
}
template<typename T> Rational Rational::operator+ (const T& value) {
	Rational temp(*this);
	return temp += value;
}
template<typename T> Rational Rational::operator- (const T& value) {
	Rational temp(*this);
	return temp += -value;
}
template<typename T> Rational& Rational::operator-= (const T& value) {
	return *this += -value;
}
template<typename T> Rational& Rational::operator/= (const T& value) {
	denom *= value;
	simplify();
	return *this;
}
template<typename T> Rational Rational::operator/ (const T& value) {
	Rational temp(*this);
	return temp /= value;
}
template<typename T> Rational& Rational::operator*= (const T& value) {
	numer *= value;
	simplify();
	return *this;
}
template<typename T> Rational Rational::operator* (const T& value) {
	Rational temp(*this);
	return temp *= value;
}
