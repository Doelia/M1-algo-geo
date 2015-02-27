#include "Point.h"

Point* Point::projectOnLine(Point* b, Point *c) {
	Vector* u = new Vector(b,c);
	cout << "u = " << *u << endl;
	return this->projectOnLine(u, b);
}

void Point::displayAll(Point** list, int n, bool relier) {
	!relier?glBegin(GL_POINTS):glBegin(GL_LINE_STRIP);
	for (int i=0; i < n; i++) {
		Point* j = list[i];
		j->display();
	}
	glEnd();
}

void Point::display() {
	this->draw();
}


Point* Point::projectOnLine(Vector* u, Point* b) {
	Point* a = this;

	Vector* uNormal = new Vector(*u);
	uNormal->normalize();
	Vector* ba = new Vector(b,a);

	double normeBAPrim = ba->getScalar(uNormal);
	return new Point(
		b->getX() + uNormal->getX()*normeBAPrim,
		b->getY() + uNormal->getY()*normeBAPrim,
		b->getZ() + uNormal->getZ()*normeBAPrim
	);
}

Point* Point::projectOnPlan(Point* a, Vector* n) {
	Point* m = this;

	Vector* nNormal = new Vector(*n);
	nNormal->normalize();

	Vector* ma = new Vector(m, a);
	double normeMMPrim = ma->getScalar(nNormal);
	return new Point(
		m->getX() + nNormal->getX() * normeMMPrim,
		m->getY() + nNormal->getY() * normeMMPrim,
		m->getZ() + nNormal->getZ() * normeMMPrim
	);
}

