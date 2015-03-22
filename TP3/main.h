#ifndef TP1_H
#define TP1_H

#include "Segment.h"
#include "Point.h"
#include <string>
#include <vector>
#include <stack>
#include <algorithm>


vector<Point*> points;

bool isValid(Point* p) {
	for (auto i : points) {
		if (i->getY() == p->getY() || i->getX() == p->getX())
			return false;
	}
	return true;
}

void generer(int n) {
	points.clear();
	for (int i = 0; i < n; i++) {
		Point* p1 = new Point(rand()%400+50, rand()%600+50, 0);
		if (isValid(p1))
			points.push_back(p1);
		else
			i--;
	}
}



Point* getPoint(int indice) {
	return points[indice];
}

class Triangle {
public:
	int a;
	int b;
	int c;

	void afficher() {
		if (a < 100 && b < 100 && c < 100) {
			glBegin(GL_LINES);
			getPoint(a)->draw();
			getPoint(b)->draw();
			getPoint(b)->draw();
			getPoint(c)->draw();
			getPoint(c)->draw();
			getPoint(a)->draw();
			glEnd();
		}
	}

	vector<int> getSommets() {
		vector<int> v;
		v.push_back(a);
		v.push_back(b);
		v.push_back(c);
		return v;
	}

	void displayCoords() {
		cout << "Triangle: " << a << ", " << b << ", " << c << "." << endl;
	}
};

vector<Triangle*> triangulation() {
	vector<Triangle*> T;
	Triangle* first = new Triangle();
	first->a = 0;
	first->b = 1;
	first->c = 2;
	T.push_back(first);

	vector<int> EC;
	EC.push_back(2);

	Vector a(points[0], points[2]);
	Vector b(points[0], points[1]);

	if (a.getDeter(&b) < 0) {
		EC.push_back(0);
		EC.push_back(1);
	} else {
		EC.push_back(1);
		EC.push_back(0);
	}

	EC.push_back(2);

	for (int i = 2; i < points.size()-1; ++i) {

		int j = 0;
		while (true) {
			Vector a(points[i+1], points[EC[j]]);
			Vector b(points[i+1], points[EC[j+1]]);
			if (a.getDeter(&b) < 0) {
				Triangle* nouv = new Triangle();
				nouv->a = EC[j];
				nouv->b = EC[j+1];
				nouv->c = i+1;
				//nouv->displayCoords();
				T.push_back(nouv);
				j++;
			}
			else {
				break;
			}
		}
		int kDroite = j;


		j = EC.size()-1;
		while (true) {
			Vector a(points[i+1], points[EC[j]]);
			Vector b(points[i+1], points[EC[j-1]]);
			if (a.getDeter(&b) > 0) {
				Triangle* nouv = new Triangle();
				nouv->a = EC[j];
				nouv->b = EC[j-1];
				nouv->c = i+1;
				//nouv->displayCoords();
				T.push_back(nouv);
				j--;
			}
			else {
				break;
			}
		}
		int kGauche = j;

		vector<int> copy;
		copy.push_back(i+1);
		for (int i = kDroite; i < kGauche+1; ++i) {
			copy.push_back(EC[i]);
		}
		copy.push_back(i+1);
		EC = copy;
		
	}

	cout << "ALGO OK" << endl;

	return T;

}

Point** vectorToTab(vector<Point*> pts) {
	Point** tab = new Point*[pts.size()];
	for (int i = 0; i < pts.size(); ++i) {
		tab[i] = pts[i];
	}
	return tab;
}

void trierWithAbssice() {
	std::sort(points.begin(), points.end(), [=] (Point* a, Point* b) {
		return a->getX() < b->getX();
	});
}

// Intervertit l'arret IJ dans les triangles t1 et t2
void flip(Triangle* t1, Triangle* t2) {

	vector<int> flip;
	vector<int> flop;
	for (auto i : t1->getSommets()) {
		for (auto j : t2->getSommets()) {
			if (i == j) {
				flip.push_back(i);
			}	
		}
	}

	for (auto i : t1->getSommets()) {
		if (find(flip.begin(), flip.end(), i) == flip.end()) {
			flop.push_back(i);
		}
	}
	for (auto i : t2->getSommets()) {
		if (find(flip.begin(), flip.end(), i) == flip.end()) {
			flop.push_back(i);
		}
	}

	t1->a = flip[0];
	t1->b = flop[1];
	t1->c = flop[0];

	t2->a = flop[0];
	t2->b = flip[1];
	t2->c = flop[1];

}

void circumCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double &x, double &y)
{
  double v,m1, m2, m3, n1, n2, n3;
  m1 = 2.*(x3-x2); m2 = -2.*(y2-y3); m3 = (y2-y3)*(y2+y3)-(x3-x2)*(x2+x3);
  n1 = 2.*(x3-x1); n2 = -2.*(y1-y3); n3 = (y1-y3)*(y1+y3)-(x3-x1)*(x1+x3);
  v=1./(n2*m1-n1*m2);
  x = v*(n3*m2-n2*m3);
  y = v*(n1*m3-n3*m1);
}

bool flipPossible(Triangle t1, Triangle t2) {

	vector<int> points = t2.getSommets();
	for (auto i : t1.getSommets()) {
		points.erase(remove(points.begin(), points.end(), i), points.end());
	}
	if (points.size() != 1) {
		return false;
	}
	int pointOut = points[0];
	vector<int> pointIn = t1.getSommets();
	int a = pointIn[0];
	int b = pointIn[1];
	int c = pointIn[2];
	int d = pointOut;

	double x;
	double y;
	circumCircleCenter(
		getPoint(a)->getX(), getPoint(a)->getY(),
		getPoint(b)->getX(), getPoint(b)->getY(),
		getPoint(c)->getX(), getPoint(c)->getY(),
		x, y);
	Point center(x,y,0);
	Vector v(&center, getPoint(a));
	Vector toD(&center, getPoint(d));

	return (v.getNorme() > toD.getNorme());
	//return (da.getNorme() * cb.getNorme() * ca.getScalar(&db) <= da.getNorme() * db.getNorme() * ca.getScalar(&cb));
}

void delaunay(vector<Triangle*> triangles) {
	bool flipped = true;
	while (flipped) {
		flipped = false;
		for (auto i : triangles) {
			for (auto j : triangles) {
				if (flipPossible(*i, *j)) {
					flip(i, j);
					flipped = true;
				}
			}
		}
	}
}

void exec() {

	int n = 90;
	generer(n);
	trierWithAbssice();
	Point::displayAll(vectorToTab(points), n, false);

	vector<Triangle*> triangles = triangulation();

	glColor4f(1,0,0,0.5f);

	for (Triangle* v : triangles) {
		v->afficher();
	}

	glColor4f(0,1,0,0.5f);
	delaunay(triangles);

	for (Triangle* v : triangles) {
		v->afficher();
	}

}

#endif
