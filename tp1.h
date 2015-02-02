#include "Segment.h"
#include <time.h>

Segment** generatePointRandom(int n) {
	Segment** tab = new Segment*[n];

	for (int i = 0; i < n; i++) {
		Point* p1 = new Point(rand()%380+20, rand()%600+100, 0);
		Point* p2 = new Point(p1->getX() + rand()%99+1, p1->getY() + rand()%100-50, 0);
		tab[i] = new Segment(p1, p2);
	}
	return tab;
}

bool cleInferieure(Segment* s1, Segment* s2){
	Vector* v = new Vector(s1->x, s2->x);
	Vector* v2 = new Vector(s1->x, s2->y);
	return v->getDeter(v2) > 0;
}

bool intersect(Segment* s1, Segment* s2){
	Vector* v = new Vector(s1->x, s1->y);
	Vector* v2 = new Vector(s1->x, s2->y);
	Vector* v3 = new Vector(s1->x, s2->x);

	Vector* w = new Vector(s2->x, s2->y);
	Vector* w2 = new Vector(s2->x, s1->x);
	Vector* w3 = new Vector(s2->x, s1->y);

	return (
		v->getDeter(v2) * v->getDeter(v3) < 0
		&& 
		w->getDeter(w2) * w->getDeter(w3) < 0
	);
}


void exec() {
	/*
	Segment** rdm = generatePointRandom(10);
	Segment::displayAll(rdm, 10);
	*/

	int coef = 100;

	Segment* s1 = new Segment(new Point(1*coef,1*coef,0), new Point(3*coef,3*coef,0));
	Segment* s2 = new Segment(new Point(2*coef,1*coef,0), new Point(2*coef,0*coef,0));
	Segment::displayAll(&s1, 1);
	Segment::displayAll(&s2, 1);

	cout << intersect(s1, s2) << endl;

}
