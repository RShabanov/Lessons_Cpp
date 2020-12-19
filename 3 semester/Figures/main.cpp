#include <iostream>
#include <vector>
#include <fstream>
#include "Figures.h"
using namespace std;


int main() {

	//Point arr[9] = { Point(2,-6), Point(3,-3), Point(4,-5), Point(6,-4), Point(6, -6),
	//Point(4, -6), Point(5,-7),Point(3,-8), Point(3,-6) };

	//Point p1(5, 2), p2(5, 4), p3(9, 4), p4(9,2);
	//Polygon C(9, arr);

	Circle circle(0, 0, 5);
	Triangle triangle(0, 0, 5, 0, 0, 5);
	Rectangle rectangle(0, 0, 5, 0, 5, 5, 5, 0);
	Polygon polygon("Границы участка2.txt");

	vector<Figure*> figures;
	figures.push_back(&circle);
	figures.push_back(&triangle);
	figures.push_back(&rectangle);
	figures.push_back(&polygon);

	double total_area = 0.0;
	double area = 0.0;
	for (size_t i = 0; i < figures.size(); i++) {
		total_area += area = figures.at(i)->area();
		cout << "Figure # " << i << '\t' << typeid(figures.at(i)).name() << '\n'
			<< "area: " << area << endl
			<< "perim: " << figures.at(i)->perimeter() << endl << endl;

	}

	cout << "Total area: " << total_area << endl;


	system("pause");
	return 0;
}