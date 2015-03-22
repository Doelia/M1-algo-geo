#ifndef TP1_H
#define TP1_H

#include "Segment.h"
#include "Point.h"
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

vector<Point*> jarvis(Point** tab, int n);

Point** generatePointRandom(int n) {
	Point** tab = new Point*[n];

	for (int i = 0; i < n; i++) {
		Point* p1 = new Point(rand()%612, rand()%792, 0);
		tab[i] = p1;
	}
	return tab;
}

vector<Point*> retournerPoints(Point** tab, int n) {
	return jarvis(tab, n);
}

Point** generatePointRandomInCircle(int n) {
	// Centre 300,400 - rayon 250
	Point centre(300,400,0);

	Point** tab = new Point*[n];

	int i = 0;
	while (i < n) {
		Point* p1 = new Point(rand()%500+50, rand()%550+100, 0);
		Vector v(&centre,p1);
		if (v.getNorme() <= 250 ) {
			tab[i++] = p1;
		}
	}
	return tab;
}
 
bool anglePolaireInferieur(Point* p0, Point* p1, Point* p2) {
	Vector p01(p0, p1);
	Vector p02(p0, p2);
	return p01.getDeter(&p02) <= 0;
}

Point* getPointOrdiMin(Point** list, int n) {
	int iMin = 0;
	for (int i = 0; i < n; ++i)	{
		if (list[i]->getY() <= list[iMin]->getY()) {
			iMin = i;
		}
	}
	return list[iMin];
}

Point* getPointDiffOf(Point** tab, int n, Point* p) {
	for (int i = 0; i < n; ++i) {
		if (tab[i] != p)
			return tab[i];
	}
	return NULL;
}



vector<Point*> jarvis(Point** tab, int n) {
	vector<Point*> list;

	Point* pMin = getPointOrdiMin(tab, n);
	Point* pCourant = pMin;

	list.push_back(pCourant);

	do {
		Point* plusADroite = getPointDiffOf(tab, n, pCourant);
		for (int i = 0; i < n; ++i) {
			if (tab[i] != pCourant && anglePolaireInferieur(pCourant, plusADroite, tab[i])) {
				plusADroite = tab[i];
			}
		}
		list.push_back(plusADroite);
		pCourant = plusADroite;
	} while (pCourant != pMin);

	return list;
}


vector<Point*> graham(Point** tab, int n) {
	Point* pMin = getPointOrdiMin(tab, n);
	vector<Point*> Q;
	for (int i = 0; i < n; ++i) {
		if (tab[i] != pMin)
			Q.push_back(tab[i]);
	}

	std::sort(Q.begin(), Q.end(), [=] (Point* a, Point* b) {
		return (anglePolaireInferieur(pMin, a, b));
	});


	stack<Point*> l;
	l.push(pMin);
	l.push(Q[0]);
	l.push(Q[1]);
	for (int i = 3; i < n-1; ++i) {

		Vector* v;
		Vector* v2;
		do {
			Point* dernier = l.top(); l.pop();
			Point* avantDernier = l.top();
			v = new Vector(avantDernier, dernier);
			v2 = new Vector(avantDernier, Q[i]);
			l.push(dernier);
			if (v->getDeter(v2) >= 0)
				l.pop();
		} while (v->getDeter(v2) >= 0);

		l.push(Q[i]);
	}
	l.push(pMin);
	l.push(Q[n-2]);


	vector<Point*> list;
	while (l.size() > 0) {
		list.push_back(l.top());
		l.pop();
	}
	
	return retournerPoints(tab, n);
}


void exec() {
	int n = 100;
	Point** pts = generatePointRandomInCircle(n);

	glColor3f(1, 0, 1);
	Point::displayAll(pts, n, false);

	vector<Point*> list = graham(pts, n);
	Point** enveloppe = new Point*[list.size()];
	for (int i = 0; i < list.size(); ++i)	{
		enveloppe[i] = list[i];
	}
 
	glColor3f(1, 0, 0);
	glLineWidth(5);
	Point::displayAll(enveloppe, list.size(), true);

	

}

#endif
