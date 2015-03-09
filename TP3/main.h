#ifndef TP1_H
#define TP1_H

#include "Segment.h"
#include "Point.h"
#include <string>
#include <vector>
#include <stack>
#include <algorithm>


vector<Point*> points;

void generer(int n) {
	points.clear();
	for (int i = 0; i < n; i++) {
		Point* p1 = new Point(rand()%612, rand()%792, 0);
		points.push_back(p1);
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

		cout << "Traitement i=" << i << endl;

		cout << "Calcul des points en haut..." << endl;

		int j = 0;
		while (true) {
			Vector a(points[i+1], points[EC[j]]);
			Vector b(points[i+1], points[EC[j+1]]);
			cout << "Deter entre (" << i+1 << ", " << EC[j] << ") et (" << i+1 << ", " << EC[j+1] << ")" << endl;
			if (a.getDeter(&b) < 0) {
				Triangle* nouv = new Triangle();
				nouv->a = EC[j];
				nouv->b = EC[j+1];
				nouv->c = i+1;
				nouv->displayCoords();
				T.push_back(nouv);
				j++;
			}
			else {
				break;
			}
		}
		int kDroite = j;

		cout << "Calcul des points en bas..." << endl;


		j = EC.size()-1;
		while (true) {
			Vector a(points[i+1], points[EC[j]]);
			Vector b(points[i+1], points[EC[j-1]]);
			cout << "Deter entre (" << i+1 << ", " << EC[j] << ") et (" << i+1 << ", " << EC[j-1] << ")" << endl;
			if (a.getDeter(&b) > 0) {
				Triangle* nouv = new Triangle();
				nouv->a = EC[j];
				nouv->b = EC[j-1];
				nouv->c = i+1;
				nouv->displayCoords();
				T.push_back(nouv);
				j--;
			}
			else {
				break;
			}
		}
		int kGauche = j;

		cout << "Recalcul de l'EC..." << endl;

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

void exec() {

	int n = 5;
	generer(n);
	trierWithAbssice();
	Point::displayAll(vectorToTab(points), n, false);

	vector<Triangle*> triangles = triangulation();
	for (Triangle* v : triangles) {
		v->afficher();
	}

}

#endif
