#ifndef TP2_H
#define TP2_H

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
	return p01.getDeter(&p02) < 0;
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

	return list;
	
	return retournerPoints(tab, n);
}

struct pointTest {
	int abscisse;
	int ordonnee;
};

Point** goTest() {
	int n = 20;
	pointTest sommet[n];

	sommet[0].abscisse=123;
	sommet[0].ordonnee=523;
	sommet[1].abscisse=259;
	sommet[1].ordonnee=476;
	sommet[2].abscisse=411;
	sommet[2].ordonnee=280;
	sommet[3].abscisse=60;
	sommet[3].ordonnee=400;
	sommet[4].abscisse=187;
	sommet[4].ordonnee=544;
	sommet[5].abscisse=447;
	sommet[5].ordonnee=381;
	sommet[6].abscisse=296;
	sommet[6].ordonnee=194;
	sommet[7].abscisse=273;
	sommet[7].ordonnee=614;
	sommet[8].abscisse=130;
	sommet[8].ordonnee=250;
	sommet[9].abscisse=212;
	sommet[9].ordonnee=587;
	sommet[10].abscisse=500;
	sommet[10].ordonnee=400;
	sommet[11].abscisse=280;
	sommet[11].ordonnee=170;
	sommet[12].abscisse=280;
	sommet[12].ordonnee=630;
	sommet[13].abscisse=311;
	sommet[13].ordonnee=233;
	sommet[14].abscisse=345;
	sommet[14].ordonnee=512;
	sommet[15].abscisse=130;
	sommet[15].ordonnee=550;
	sommet[16].abscisse=430;
	sommet[16].ordonnee=250;
	sommet[17].abscisse=212;
	sommet[17].ordonnee=587;
	sommet[18].abscisse=430;
	sommet[18].ordonnee=550;
	sommet[19].abscisse=431;
	sommet[19].ordonnee=450;

	Point** pts = new Point*[n];
	for (int i = 0; i < n; i++) {
		pts[i] = new Point(sommet[i].abscisse, sommet[i].ordonnee, 0);
	}

	return pts;

}

void exec() {
	int n = 20;
	//Point** pts = generatePointRandomInCircle(n);
	Point** pts = goTest();

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
