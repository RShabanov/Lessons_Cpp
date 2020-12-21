#pragma once
#include "Function.h"
using std::vector;



template<typename T>
class Polynomial : public Function<T> {
	int degree;

public:
	using Function<T>::coeff;

	Polynomial(const vector<T>& _coeff);
	Polynomial(const Polynomial&);
	~Polynomial();

	int get_degree() const { return degree; }

	Polynomial<T> deriv(int n = 1) const;
	vector<double> roots() const;
	double calculate(const double&) const;
	double min(double x1, double x2) const;
	double max(double x1, double x2) const;

	template <typename OT> friend std::ostream& operator<<(std::ostream&, const Polynomial<OT>&);

	const Polynomial& operator=(const Polynomial&);

};



template<typename T>
Polynomial<T>::Polynomial(const vector<T>& _coeff)
	: Function<T>(_coeff) {
	degree = coeff.size();
	if (degree != 0) degree--;
}


template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& P)
	: Function<T>(P) { degree = P.degree; }


template<typename T>
Polynomial<T>::~Polynomial() {}


template<typename T>
Polynomial<T> Polynomial<T>::deriv(int n) const {
	if (n == 0) return *this;
	else if (n < 0) throw FunctionException();

	vector<T> deriv_coeff(coeff);
	int deriv_degree = degree;

	while (n-- && deriv_coeff.size() > 0) {
		deriv_coeff.pop_back();
		for (int i = 0; i < deriv_coeff.size(); i++)
			deriv_coeff[i] *= deriv_degree - i;
		deriv_degree--;
	}

	return Polynomial(deriv_coeff);
}

template<typename T>
vector<double> Polynomial<T>::roots() const {
	// TODO
	// ðåàëèçîâàòü ðàáîòó ñ êîìïëåêñíûìè ÷èñëàìè?

	if (degree == 0) return vector<double>();
	vector<double> r;
	if (degree == 1) r.push_back(coeff[1]);
	else if (degree == 2) {
		double D = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
		if (D > 0) {
			D = sqrt(D);
			r.push_back((-coeff[1] - D) / 2);
			r.push_back((-coeff[1] + D) / 2);
		}
		else if (D == 0) r.push_back(-coeff[1] / 2);
		else throw FunctionException();
	}
	else {
		// TODO 
		// ðåàëèçîâàòü íàõîæäåíèå êîðíåé ïîëèíîìà
	}

	return r;
}


template<typename T>
double Polynomial<T>::calculate(const double& x) const {
	double res = coeff[0];
	for (int i = 1; i <= degree; i++)
		res = res * x + coeff[i];
	return res;
}


template<typename T>
const Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& P) {
	if (this != &P) {
		coeff = P.coeff;
		degree = P.degree;
	}
	return *this;
}


template<typename T>
double Polynomial<T>::min(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double min_var = calculate(x1), temp = 0;
	vector<double> r = deriv().roots();
	for (double root : r)
		if (root > x1 && root < x2) {
			temp = calculate(root);
			if (temp < min_var) min_var = temp;
		}
	temp = calculate(x2);
	if (temp < min_var) min_var = temp;

	return min_var;
}

template<typename T>
double Polynomial<T>::max(double x1, double x2) const {
	if (x1 > x2) throw FunctionException();
	double max_var = calculate(x1), temp = 0;
	vector<double> r = deriv().roots();

	for (double root : r)
		if (root > x1 && root < x2) {
			temp = calculate(root);
			if (temp > max_var) max_var = temp;
		}
	temp = calculate(x2);
	if (temp > max_var) max_var = temp;

	return max_var;
}



template<typename OT> 
std::ostream& operator<<(std::ostream& out, const Polynomial<OT>& P) {
	if (P.coeff.empty()) out << "Polynomial is empty\n";
	else {
		for (int i = 0; i < P.degree; i++) {
			int d = P.degree - i;
			if (P.coeff[i] != 0) {
				if (P.coeff[i] != 1) {
					if (i == 0) out << P.coeff[i];
					else
						out << (P.coeff[i] < 0 ? " - " : " + ") << abs(P.coeff[i]);
				}
				out << (d != 0 && i != 0 ? "*" : "") << "x";
				if (d > 1) out << "^" << d;
			}
		}
		if (P.degree)
			out << (P.coeff[0] < 0 ? " - " : " + ") << abs(P.coeff[P.degree]);
		else out << P.coeff[P.degree];
	}
	return out;
}
