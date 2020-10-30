#include <iostream>
#include "Vector.h"
using namespace std;


int main() {

	Vector<int> v;
	for (int i = 0; i < 5; i++)
		v.push_back(i + 1);

	Vector<int> a(3, 10);

	cout << "Vector v:\n";
	v.print(cout);
	cout << endl << endl;

	cout << "Vector a:\n";
	a.print(cout);
	cout << endl << endl;

	cout << "a.is_empty(): " << a.is_empty() << endl << endl;

	cout << "Vector v after adding vector a at the end: v.push_back(a)\n";
	v.push_back(a);
	v.print(cout);
	cout << endl << endl;

	cout << "Compare vectors v and a: v == a\n" << (v == a) << endl << endl;

	cout << "v = a:\n";
	v = a;
	cout << v << endl << endl;

	cout << "Vector v after removing the last element: v.pop_back()\n";
	v.pop_back();
	cout << v << endl << endl;

	cout << "Vector v after inserting one element (56) at 2 position: v.insert(2, 56)\n";
	v.insert(2, 56);
	cout << v << endl << endl;

	cout << "Vector v after resizing: v.resize(1)\n";
	v.resize(1);
	cout << v << endl << endl;

	cin.get();
	return 0;
}
