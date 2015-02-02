#ifndef TOOLGL_H
#define TOOLGL_H

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <GL/glut.h> 

void drawPoint(Coord* c) {
	glVertex3f(c->getX(), c->getY(), c->getZ());
}

void drawCurve(Point** tab, long nbPoints) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPoints; ++i) {
		drawPoint(tab[i]);
		cout << "tab[" << i << "] = " << *tab[i] << endl;
	}
	glEnd();
}

Point** hermiteCurve(Point* p0, Point* p1, Vector* v0, Vector* v1, long nbU) {
	Point** pts = new Point*[nbU];
	for (int i = 0; i < nbU; ++i) {
		double u = 1.0/nbU * (double) i;

		double f1 = 2*pow(u,3) - 3*pow(u,2) + 1;
		double f2 = -2*pow(u,3) + 3*pow(u,2);
		double f3 = pow(u,3) - 2*pow(u,2) + u;
		double f4 = pow(u,3) - pow(u,2);

		pts[i] = new Point(
			f1*p0->getX() + f2*p1->getX() + f3*v0->getX() + f4*v1->getX(),
			f1*p0->getY() + f2*p1->getY() + f3*v0->getY() + f4*v1->getY(),
			f1*p0->getZ() + f2*p1->getZ() + f3*v0->getZ() + f4*v1->getZ()
		);
	}
	return pts;
}

double fact(double n) {
	if (n == 0) {
		return 1.0;
	}
	return n*fact(n-1);
}

Point** bezierCurveByBernstein(Point** tab, long nControl, long nbU) {
	Point** pts = new Point*[nbU];

	for (int j = 0; j < nbU; ++j) {
		double u = 1.0/nbU * (double) j;
		Point* p = new Point();
		for (int i = 0; i < nControl; ++i) {
			double n = nControl-1;
			double Bni = (fact(n) / (fact(i) * fact(n-i))) * pow(u, i) * pow(1-u, n-i);
			p->setX(p->getX() + Bni*tab[i]->getX());
			p->setY(p->getY() + Bni*tab[i]->getY());
			p->setZ(p->getZ() + Bni*tab[i]->getZ());
		}
		pts[j] = p;

	}
	return pts;

}

#endif
