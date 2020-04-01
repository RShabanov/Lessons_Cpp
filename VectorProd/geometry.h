#ifndef GEOMETRY_H_
#define GEOMETRY_H_

struct Point {
	int x, y;
};

typedef Point Vector;

int get_coord_v(const Vector&, const Vector&);
Point get_vector(const Point&, const Point&);

#endif // !GEOMETRY_H_
