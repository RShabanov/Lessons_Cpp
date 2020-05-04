#pragma once
#ifndef _GEOMETRY_H
#define _GEOMETRY_H
struct Point
{
	double x, y;
};struct Triangle
{
	Point vertexes[3];
	double area;
};

double calcDistance(const Point& pa, const Point& pb);
double calcAreaBySides(double a, double b, double c);
double calcTriangleArea(Triangle& tr);

#endif // !_GEOMETRY_H



//// � ����� C
//struct Triangle
//{
//	struct Point vertexes[3]; // ��� ������� ������������
//	double area; // ������� ������������ (���� �����)
//};