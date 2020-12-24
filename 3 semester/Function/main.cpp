#include <iostream>
#include <vector>
#include "Polynomial.h"
#include "Hyperbola.h"
#include "Exp.h"
using namespace std;


int main() {

	Polynomial<int> poly({ 1,2,3,4,5 });
	cout << "poly:\t" << poly << endl;
	cout << "poly(10):\t" << poly.calculate(10) << endl;
	cout << "min(-2, 1):\t" << poly.min(-2, 1) << endl;
	cout << "min(1, 2):\t" << poly.min(1, 2) << endl;

	cout << "=======================================\n\n";

	Hyperbola<int> hyper({ 1,2 }, 5, 2);
	cout << "Hyperbola:\t" << hyper << endl;
	cout << "hyperbola(10):\t" << hyper.calculate(10) << endl;
	cout << "min(-2, -1):\t" << hyper.min(-2, -1) << endl;
	cout << "max(1, 2):\t" << hyper.max(1, 2) << endl;

	cout << "=======================================\n\n";


	Exp<int> e({ 1,2 }, 2);
	cout << "Exp:\t" << e << endl;
	cout << "Exp(10):\t" << e.calculate(10) << endl;
	cout << "min(-2, -1):\t" << e.min(-2, -1) << endl;
	cout << "max(1, 2):\t" << e.max(1, 2) << endl;

	cin.get();
	return 0;
}
