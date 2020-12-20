#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "FunctionException.h"
using std::vector;


template<typename T>
T fast_pow(T a, int n) {
	if (n == 0) return 1;
	if (n % 2) return fast_pow(a, n - 1) * a;
	else {
		T b = fast_pow(a, n / 2);
		return b * b;
	}
}


template<typename T>
class Function {
protected:
	vector<T> coeff;
	// TODO
	// * парсинг строки
	// Function(const string& _f);
	Function(const vector<T>& _c);
	Function(const Function& F);
	virtual ~Function() {}

public:
	
	const vector<T> get_coeff() const { return coeff; }
	
	virtual double calculate(const double&) const = 0;
	virtual double min(double x1, double x2) const = 0;
	virtual double max(double x1, double x2) const = 0;

	template <typename OT> friend std::ostream& operator<<(std::ostream&, const Function&);
};


template<typename T>
Function<T>::Function(const vector<T>& _c) {
	if (!_c.empty()) {
		bool is_zero_fst = true;
		for (T item : _c) {
			if (is_zero_fst && item == 0) continue;
			else {
				coeff.push_back(item);
				is_zero_fst = false;
			}
		}
	}
	else throw FunctionException();
}

template<typename T>
Function<T>::Function(const Function<T>& F) {
	if (!F.coeff.empty()) {
		bool is_zero_fst = true;
		for (T item : F.coeff) {
			if (is_zero_fst && item == 0) continue;
			else {
				coeff.push_back(item);
				is_zero_fst = false;
			}
		}
	}
	else throw FunctionException();
}


template<typename OT>
std::ostream& operator<<(std::ostream& out, const Function<OT>& F) {
	out << "Functions coefficients: ";
	for (OT item : F.coeff) out << item << " ";
	out << std::endl;
	return out;
}