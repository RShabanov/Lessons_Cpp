#pragma once
#include <cmath>
#include "Function.h"
#include "Polynomial.h"
using std::vector;


// y = e^(Ax + B) + C
template <typename T>
class Exp : public Function<T> {
	double C;
public:
	using Function<T>::coeff;
	Exp(const vector<T>&, double _C = 0);
	Exp(const Polynomial<T>&, double _C = 0);
	Exp(const Exp&);
	~Exp();

	double calculate(const double& x) const;
	double min(double, double) const;
	double max(double, double) const;

	const Exp& operator=(const Exp&);

	template<typename OT> friend std::ostream& operator<<(std::ostream&, const Exp<OT>&);
};


template<typename T>
Exp<T>::Exp(const vector<T>& _coeff, double _C) 
	: Function<T>(_coeff) {
	if (coeff.size() > 2) throw FunctionException();
	C = _C;
}

template<typename T>
Exp<T>::Exp(const Polynomial<T>& poly, double _C)
	: Function<T>(poly) {
	if (coeff.size() > 2) throw FunctionException();
	C = _C;
}

template<typename T>
Exp<T>::Exp(const Exp<T>& E)
	: Function<T>(E) {
	C = E.C;
}


template<typename T>
Exp<T>::~Exp() {}


template<typename T>
double Exp<T>::calculate(const double& x) const {
	double power = 0;
	if (coeff.size() == 2) power = coeff[0] * x + coeff[1];
	else power = coeff[0];
	return exp(power) + C;
}

template<typename T>
double Exp<T>::min(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double min1 = calculate(x1);
	double min2 = calculate(x2);
	return min1 < min2 ? min1 : min2;
}

template<typename T>
double Exp<T>::max(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double max1 = calculate(x1);
	double max2 = calculate(x2);
	return max1 > max2 ? max1 : max2;
}


template<typename T>
const Exp<T>& Exp<T>::operator=(const Exp<T>& E) {
	C = E.C;
	coeff = E.coeff;
}


template<typename OT>
std::ostream& operator<<(std::ostream& out, const Exp<OT>& E) {
	out << "e^(";
	if (E.coeff.size() == 2) {
		if (E.coeff[0] != 1) out << E.coeff[0] << "*";
		out << "x" << (E.coeff[1] < 0 ? " - " : " + ") << abs(E.coeff[1]);
	}
	else out << E.coeff[0];
	out << ")";
	if (E.C != 0) out << (E.C < 0 ? " - " : " + ") << abs(E.C);
	return out;
}