#ifndef POINT_H
#define POINT_H

#include "Coord.h"
#include "Vector.h"

class Point : public Coord {
private:
public:
	Point(double x, double y, double z) : Coord(x, y, z) {};
	Point() : Coord() {};
	Point(Point& v) : Coord(v) {};
	void display();

	Point* projectOnLine(Point*, Point*);
	Point* projectOnLine(Vector*, Point*);
	Point* projectOnPlan(Point*, Vector*);
	static void displayAll(Point** list, int n, bool);
	bool equals(Point* p);
};

#endif
