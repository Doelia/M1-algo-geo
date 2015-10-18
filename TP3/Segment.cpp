#include "Segment.h"
#include <iostream>

Segment::Segment(Coord* x, Coord* y) {
	this->x = x;
	this->y = y;
	r = 1;
	g = 1;
	b = 1;
}

Segment::Segment(Coord* x, Coord* y, float r, float g, float b) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->g = g;
	this->b = b;
}

void Segment::displayAll(vector<Segment*> list) {
	glBegin(GL_LINES);
	for (Segment* i : list) {
		i->display();
	}
	glEnd();
}

void Segment::displayAll(Segment** list, int n) {
	glBegin(GL_LINES);
	for (int i=0; i < n; i++) {
		Segment* j = list[i];
		j->display();
	}
	glEnd();
}

void Segment::display() {
	glColor3f(r, g, b);
	x->draw();
	y->draw();
}

ostream& operator<<(ostream &flux, Segment& v) {
   // flux << "[" <<  "]";
   // flux << "[" << v.x->getX() <<  "]";
    return flux;
}
