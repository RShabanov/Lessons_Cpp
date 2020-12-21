#pragma once
#include "Function.h"
#include "Polynomial.h"
using std::vector;


// y = k / (Ax + B) + C
template<typename T>
class Hyperbola : public Function<T> {
	double k;
	double C;
public:
	using Function<T>::coeff;
	Hyperbola(const vector<T>&, double _k = 1, double _C = 0);
	Hyperbola(const Hyperbola&);
	Hyperbola(const Polynomial<T>&, double _k = 1, double _C = 0);
	~Hyperbola();

	double get_k() const { return k; }

	double calculate(const double& x) const;
	double min(double, double) const;
	double max(double, double) const;

	const Hyperbola& operator=(const Hyperbola&);

	template<typename OT> friend std::ostream& operator<<(std::ostream& out, const Hyperbola<OT>&);
};


template<typename T>
Hyperbola<T>::Hyperbola(const vector<T>& _coeff, double _k, double _C)
	: Function<T>(_coeff) {
	if (coeff.size() > 2 || coeff.size() == 0) throw FunctionException();
	k = _k;
	C = _C;
}

template<typename T>
Hyperbola<T>::Hyperbola(const Hyperbola& H)
	: Function<T>(H) {
	k = H.k;
}

template<typename T>
Hyperbola<T>::Hyperbola(const Polynomial<T>& P, double _k, double _C)
	: Function<T>(P) {
	if (coeff.size() > 2 || coeff.size() == 0) throw FunctionException();
	k = _k;
	C = _C;
}


template<typename T>
Hyperbola<T>::~Hyperbola() {}


template<typename T>
double Hyperbola<T>::calculate(const double& x) const {
	if (coeff.size() == 2) return k / (coeff[0] * x + coeff[1]) + C;
	else return k / coeff[0] + C;
}

template<typename T>
double Hyperbola<T>::min(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double min1 = calculate(x1);
	double min2 = calculate(x2);
	return min1 < min2 ? min1 : min2;
}

template<typename T>
double Hyperbola<T>::max(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double max1 = calculate(x1);
	double max2 = calculate(x2);
	return max1 > max2 ? max1 : max2;
}


template<typename T>
const Hyperbola<T>& Hyperbola<T>::operator=(const Hyperbola<T>& H) {
	if (this != &H) {
		k = H.k;
		C = H.C;
		coeff = H.coeff;
	}
	return *this;
}


template<typename OT> 
std::ostream& operator<<(std::ostream& out, const Hyperbola<OT>& H) {
	out << H.k << " / (";
	if (H.coeff.size() == 2) {
		if (H.coeff[0] != 1) out << H.coeff[0] << "*";
		out << "x" << (H.coeff[1] < 0 ? " - " : " + ") << abs(H.coeff[1]);
	}
	else out << H.coeff[0];
	out << ")";
	if (H.C != 0) out << (H.C < 0 ? " - " : " + ") << abs(H.C);
	return out;
}
