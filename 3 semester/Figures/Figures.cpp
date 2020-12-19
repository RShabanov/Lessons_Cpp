#include "Figures.h"

/*

	Point

*/

Point::Point(double _x, double _y) { x = _x, y = _y; }

double Point::distance(const Point& P) const {
	return sqrt((P.x - x)*(P.x - x) + (P.y - y)*(P.y - y));
}

std::ostream& operator<<(std::ostream& out, const Point& P) {
	out << P.x << '\t' << P.y;
	return out;
}

std::istream& operator>>(std::istream& in, Point& P) {
	in >> P.x >> P.y;
	return in;
}

bool Point::operator<(const Point& P) const {
	return x < P.x && y < P.y;
}

bool Point::operator>(const Point& P) const {
	return P < *this;
}

/*

	Figure

*/

Figure::Figure() {
	points = nullptr;
	point_amount = 0;
}

Figure::Figure(int size) {
	point_amount = size;
	points = new Point[size];
}

Figure::Figure(int size, Point _points[]) {
	if (size > 0 && size >= (sizeof(_points) / sizeof(Point))) {
		point_amount = size;
		points = new Point[size];
		for (int i = 0; i < size; i++)
			points[i] = _points[i];
	}
	else throw FigureException();
}

Figure::Figure(const Figure& F) {
	point_amount = F.point_amount;
	points = new Point[point_amount];
	for (int i = 0; i < point_amount; i++)
		points[i] = F.points[i];
}

Figure::~Figure() {
	if (points != nullptr) delete[] points;
}



Point Figure::get_vector(const Point& A, const Point& B) const {
	return { B.x - A.x, B.y - A.y };
}

double Figure::vector_product(const Point& A, const Point& B) const {
	return A.x * B.y - B.x * A.y;
}


std::ostream& operator<<(std::ostream& out, const Figure& F) {
	out << "Point amount: " << F.point_amount << std::endl
		<< "Vertices:\n";
	for (int i = 0; i < F.point_amount; i++)
		out << F.points[i] << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Figure& F) {
	in >> F.point_amount;
	if (in) {
		if (F.points != nullptr) delete[] F.points;
		F.points = new Point[F.point_amount];
		for (int i = 0; i < F.point_amount; i++)
			in >> F.points[i];
	}
	else throw FigureException();
	return in;
}





/*

	Circle

*/

Circle::Circle(double x, double y, double _radius)
	: Figure(1) {
	points->x = x;
	points->y = y;
	radius = _radius;
}

Circle::Circle(Point& start, double _radius) 
	: Figure(1) {
	points->x = start.x;
	points->y = start.y;
	radius = _radius;
}

Circle::Circle(const Circle& C) : Figure(C) {
	radius = C.radius;
}

Circle::~Circle() {}

double Circle::area() const {
	return M_PI * radius * radius;
}

double Circle::perimeter() const {
	return 2 * M_PI * radius;
}


/*

	Triangle

*/

Triangle::Triangle(double x1, double y1,
	double x2, double y2,
	double x3, double y3) : Figure(3) {
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	points[2].x = x3;
	points[2].y = y3;
}


Triangle::Triangle(const Point& P1, const Point& P2, const Point& P3) 
	: Figure(3) {
	points[0] = P1;
	points[1] = P2;
	points[2] = P3;
}

Triangle::Triangle(int size, Point _points[]) : Figure(size, _points) {}


Triangle::Triangle(const Triangle& _Triangle) : Figure(_Triangle) {}

Triangle::~Triangle() {}

double Triangle::area() const {
	return abs(vector_product(get_vector(points[0], points[1]),
		get_vector(points[0], points[2]))) / 2.0;
}

double Triangle::perimeter() const {
	return points[0].distance(points[1]) +
		points[0].distance(points[2]) + points[1].distance(points[2]);
}


/*

	Rectangle

*/

Rectangle::Rectangle(double x1, double y1,
	double x2, double y2,
	double x3, double y3,
	double x4, double y4) : Figure(4) {
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	points[2].x = x3;
	points[2].y = y3;
	points[3].x = x4;
	points[3].y = y4;
}

Rectangle::Rectangle(const Point& P1, const Point& P2, 
	const Point& P3, const Point& P4) : Figure(4) {
	points[0] = P1;
	points[1] = P2;
	points[2] = P3;
	points[3] = P4;
}

Rectangle::Rectangle(int size, Point _points[]) : Figure(size, _points) {}

Rectangle::Rectangle(const Rectangle& R) : Figure(R) {}

Rectangle::~Rectangle() {}

double Rectangle::area() const {
	return abs(vector_product(get_vector(points[0], points[1]),
		get_vector(points[0], points[2])));
}
double Rectangle::perimeter() const {
	return (points[0].distance(points[1]) + points[1].distance(points[2])) * 2.0;
}


/*

	Polygon

*/

Polygon::Polygon(int _size, Point _points[]) 
	: Figure(_size, _points) {}

Polygon::Polygon(const Polygon& CF) 
	: Figure(CF) {}

Polygon::Polygon(const std::string& filename)
	: Figure() {
	std::ifstream file(filename);
	if (file.is_open()) file >> *this;
	else throw FigureException();
}

Polygon::~Polygon() {}

double Polygon::area() const {
	double area = 0;
	
	for (int i = 1; i < point_amount - 1; i++)
		area += vector_product(get_vector(points[0], points[i]),
								get_vector(points[0], points[i + 1]));
	
	return abs(area / 2.0);
}

double Polygon::perimeter() const {
	double perim = 0;
	for (int i = 0; i < point_amount - 1; i++)
		perim += points[i].distance(points[i + 1]);
	perim += points[0].distance(points[point_amount - 1]);
	return perim;
}