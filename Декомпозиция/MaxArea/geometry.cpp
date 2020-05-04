#include "pch.h"
#include "geometry.h"
#include <cmath>
double calcDistance(const Point& pa, const Point& pb)
{
	return sqrt((pb.x - pa.x)*(pb.x - pa.x) +
		(pb.y - pa.y)*(pb.y - pa.y));
}double calcTriangleArea(Triangle& tr)
{
	Point* v = tr.vertexes;
	double a = calcDistance(v[0], v[1]);
	double b = calcDistance(v[1], v[2]);
	double c = calcDistance(v[2], v[0]);
	return tr.area = calcAreaBySides(a, b, c);
}double calcAreaBySides(double a, double b, double c)
{
	double p2 = (a + b + c) / 2.0;
	if (p2 <= 0.0 || p2 <= a || p2 <= b || p2 <= c)
		return 0.0;
	return sqrt(p2*(p2 - a)*(p2 - b)*(p2 - c));
}