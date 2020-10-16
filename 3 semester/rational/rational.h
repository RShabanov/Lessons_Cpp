#pragma once
#include <iostream>

class Rational {

	int numer, denom;


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
	

	// increment & decrement
	Rational& operator ++();
	Rational operator ++(int);
	Rational& operator --();
	Rational operator --(int);

	// comparison operations
	bool operator == (const Rational&) ;
	bool operator != (const Rational&) ;
	bool operator > (const Rational&) ;
	bool operator >= (const Rational&) ;
	bool operator < (const Rational&);
	bool operator <= (const Rational&) ;

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


	/////////////////////
	Rational flip();
	Rational sqrt();

	Rational& operator += (int);
	Rational operator + (int);

	Rational& operator /= (int);
	Rational operator / (int);
	
	Rational& operator *= (int);
	Rational operator * (int);

	bool operator == (int);
	bool operator != (int);
	bool operator > (int);
	bool operator >= (int);
	bool operator < (int);
	bool operator <= (int);
};
