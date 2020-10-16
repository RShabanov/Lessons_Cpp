#include "rational.h"


Rational::Rational() : numer{ 0 }, denom{ 1 }{};
Rational::Rational(int n) : numer{ n }, denom{ 1 }{};
Rational::Rational(int n, int d) : numer{ n }, denom{ d }{};


// arithmetic operations
Rational& Rational::operator+=(const Rational& r) {
	numer = (numer*r.denom + r.numer*denom);
	denom *= r.denom;
	simplify();
	return *this;
}

Rational Rational::operator+ (const Rational& r) {
	Rational res(*this);
	return res += r;
}

Rational Rational::operator- () const {
	Rational r(-numer, denom);
	return r;
}

Rational& Rational::operator-= (const Rational& r) {
	return (*this += (-r));
}

Rational Rational::operator - (const Rational& r) {
	Rational res(*this);
	return res -= r;
}

Rational& Rational::operator /= (const Rational& r) {
	Rational res(r.denom, r.numer);
	*this *= res;
	return *this;
}

Rational Rational::operator / (const Rational& r) {
	Rational factor(r.denom, r.numer);
	Rational res(*this);
	return res *= factor;
}

Rational& Rational::operator *= (const Rational& r) {
	numer *= r.numer;
	denom *= r.denom;
	simplify();
	return *this;
}

Rational Rational::operator * (const Rational& r) {
	Rational res(*this);
	return res *= r;
}



// increment & decrement
Rational& Rational::operator++() {
	numer += denom;
	return *this;
}

Rational Rational::operator++(int) {
	Rational r(*this);
	numer += denom;
	return r;
}

Rational& Rational::operator--() {
	numer -= denom;
	return *this;
}

Rational Rational::operator--(int) {
	Rational r(*this);
	numer -= denom;
	return r;
}


// comparison operations
bool Rational::operator == (const Rational& r)  {
	return (numer == r.numer) && (denom == r.denom);
}

bool Rational::operator!= (const Rational& r)  {
	return !(*this == r);
}

bool Rational::operator > (const Rational& r)  {
	return (numer*r.denom > denom*r.numer);
}

bool Rational::operator >= (const Rational& r) {
	return !(*this < r);
}

bool Rational::operator < (const Rational& r) {
	return (numer*r.denom < denom*r.numer);
}

bool Rational::operator <= (const Rational& r) {
	return !(*this > r);
}



// type transformation
Rational::operator int() const {
	return numer / denom;
}

Rational::operator double() const {
	return double(numer) / denom;
}


// streams
std::istream& operator >> (std::istream& in, Rational& r) {
	in >> r.numer >> r.denom;
	while (r.denom == 0) {
		std::cout << "Denominator can't be equal to 0.\n";
		std::cout << "Please, enter rational number again:\n";
		in >> r.numer >> r.denom;
	}
	return in;
}

std::ostream& operator << (std::ostream& out, const Rational& r) {
	out << r.numer;
	if (r.numer && r.denom != 1) out << '/' << r.denom;
	return out;
}



// getters & setters
void Rational::set_numerator(int n) {
	numer = n;
}

void Rational::set_denominator(int d) {
	denom = d;
}

int Rational::get_numerator() { return numer; }
int Rational::get_denominator() { return denom; }



void Rational::simplify() {
	if (denom < 0) {
		numer = -numer;
		denom = -denom;
	}
	for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
		if (numer % i == 0 && denom % i == 0) {
			numer /= i;
			denom /= i;
			i--;
		}
}



///////////////
Rational Rational::flip() {
	Rational res(denom, numer);
	return res;
}

Rational& Rational::operator += (int n) {
	numer += n * denom;
	return *this;
}

Rational Rational::operator + (int n) {
	Rational res(*this);
	return res += n;
}


Rational& Rational::operator /= (int d) {
	if (numer % d) denom *= d;
	else numer /= d;
	return *this;
}

Rational Rational::operator / (int d) {
	Rational res(*this);
	return res /= d;
}

Rational& Rational::operator *= (int n) {
	if (denom % n) numer *= n;
	else denom /= n;
	return *this;
}

Rational Rational::operator * (int n) {
	Rational res(*this);
	return res *= n;
}

bool Rational::operator == (int n) { return numer == n * denom; }
bool Rational::operator != (int n) { return !(*this == n); }
bool Rational::operator > (int n) { return (numer / denom) > n; }
bool Rational::operator >= (int n) { return !(*this < n); }
bool Rational::operator < (int n) { return (numer / denom) < n; }
bool Rational::operator <= (int n) { return !(*this > n); }

// надо доделать
Rational Rational::sqrt() {
	int power = 1, x = int(*this);

	if (x) x--;
	else return numer;

	while ((1 << power) < x) power++;
	if (power > 1) power--;

	Rational g0(1 << power);
	Rational g1((g0 + g0.flip()*(*this)) / 2);
	
	while (g1 < g0 && g1.numer > 0 && g1.denom) {
		g0 = g1;
		g1 = (g0 + g0.flip()*(*this)) / 2;
	}
	return g0;
}
