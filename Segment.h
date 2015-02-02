#ifndef SEGMENT_H
#define SEGMENT_H

#include "Coord.h"
#include <GL/glut.h>
#include <vector>

using namespace std;

class Segment;

class Segment {
protected:
	float r, g, b;
public:
	Coord* x;
	Coord* y;
	Segment(Coord* x, Coord* y);
	Segment(Coord* x, Coord* y, float, float, float);
	void display();

	static void drawPoint(Coord* c);
	static void displayAll(vector<Segment*> list);
	static void displayAll(Segment** list, int n);
	
};

ostream& operator<<(ostream &flux, Segment& v);

#endif
