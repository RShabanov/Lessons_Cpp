#include <iostream>
#include "Vector.h"
using namespace std;


int main() {

	Vector<int> v;
	for (int i = 0; i < 5; i++)
		v.push_back(i + 1);

//	cout << v << endl;
	cout << v.size() << endl;

	/*Vector<int> a;
	for (int i = 5; i < 9; i++)
		a.push_back(i);

	cout << a << endl;
	cout << a.size() << endl;*/


	//v.insert(2, a);
	//cout << v << endl;


	cin.get();
	return 0;
}