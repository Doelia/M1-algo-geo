#ifndef COORD_H
#define COORD_H

#include <iostream>
#include "GlutInclude.h"

using namespace std;

class Coord {
protected:
	double x;
	double y;
	double z;
public:
	Coord(double x, double y, double z);
	Coord();
	Coord(Coord&);

	bool equals(Coord&);

	virtual void draw();
	virtual double getX();
	virtual double getY();
	virtual double getZ();
	virtual void setX(double x);
	virtual void setY(double y);
	virtual void setZ(double z);
};

ostream& operator<<(ostream &flux, Coord& v);

#endif
