#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include <iostream>
#include <fstream>
#include "FigureException.h"


//template<class T> 
class Point {
public:
	double x, y;

	Point() {}
	Point(double _x, double _y);

	double distance(const Point&) const;

	bool operator<(const Point&) const;
	bool operator>(const Point&) const;

	friend std::ostream& operator<<(std::ostream&, const Point&);
	friend std::istream& operator>>(std::istream&, Point&);
};


class Figure
{
protected:
	Point *points;
	int point_amount;

	Point get_vector(const Point&, const Point&) const;
	double vector_product(const Point&, const Point&) const;
public:
	Figure();
	Figure(int size);
	Figure(int size, Point[]);
	Figure(const Figure&);
	virtual ~Figure();
	virtual double area() const = 0;
	virtual double perimeter() const = 0;

	friend std::istream& operator>>(std::istream&, Figure&);
	friend std::ostream& operator<<(std::ostream&, const Figure&);
};


class Circle : public Figure {
	double radius;
public:
	Circle(double x, double y, double _radius);
	Circle(Point& start, double _radius);
	Circle(const Circle&);
	~Circle();

	double area() const;
	double perimeter() const;
};


class Triangle : public Figure {
public:
	Triangle(double x1, double y1,
		double x2, double y2,
		double x3, double y3);
	Triangle(const Point&, const Point&, const Point&);
	Triangle(int size, Point[]);
	Triangle(const Triangle&);
	~Triangle();

	double area() const;
	double perimeter() const;
};


class Rectangle : public Figure {
public:
	Rectangle(double x1, double y1,
		double x2, double y2,
		double x3, double y3,
		double x4, double y4);
	Rectangle(const Point&, const Point&, const Point&, const Point&);
	Rectangle(int size, Point[]);
	Rectangle(const Rectangle&);
	~Rectangle();

	double area() const;
	double perimeter() const;
};


class Polygon : public Figure {
public:
	Polygon() : Figure() {}
	Polygon(int _size, Point[]);
	Polygon(const Polygon&);
	Polygon(const std::string& filename);
	~Polygon();

	double area() const;
	double perimeter() const;
};

