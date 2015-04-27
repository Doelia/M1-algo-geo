#include "tp1.h"


Segment** rdm;

void loadTest() {

	int n = 10;
	int i = 0;
	rdm = new Segment*[n];

	rdm[i++] = new Segment(new Point(202,203,0), new Point(351,223,0));
	rdm[i++] = new Segment(new Point(52,616,0), new Point(235,647,0));
	rdm[i++] = new Segment(new Point(250,100,0), new Point(381,246,0));
	rdm[i++] = new Segment(new Point(332,124,0), new Point(453,77,0));
	rdm[i++] = new Segment(new Point(318,613,0), new Point(485,649,0));
	rdm[i++] = new Segment(new Point(206,146,0), new Point(258,159,0));
	rdm[i++] = new Segment(new Point(24,287,0), new Point(221,331,0));
	rdm[i++] = new Segment(new Point(26,267,0), new Point(115,288,0));
	rdm[i++] = new Segment(new Point(75,114,0), new Point(174,130,0));
	rdm[i++] = new Segment(new Point(246,242,0), new Point(510,225,0));

}

Segment** generatePointRandom(int n) {
	Segment** tab = new Segment*[n];

	for (int i = 0; i < n; i++) {
		Point* p1 = new Point(rand()%380+20, rand()%600+100, 0);
		Point* p2 = new Point(p1->getX() + rand()%99+1, p1->getY() + rand()%100-50, 0);
		tab[i] = new Segment(p1, p2);
	}
	return tab;
}

bool cleEgales(int cle1, int cle2) {
	return (cle1 == cle2);
}

// renvoie vrai ssi le premier point du segment cle2
// est à gauche du segment cle1 (segment cle2 > segment cle1)
bool CleInferieure(int cle1, int cle2) {
	Segment* seg1 = rdm[cle1];
	Segment* seg2 = rdm[cle2];
	Vector v (seg1->x, seg1->y);
	Vector v2 (seg1->x, seg2->y);
	return v.getDeter(&v2) > 0;
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

bool intersectionParBalayage(Segment* segments[], int n) {
	int* tri = triLexico(segments, n);
	ARN T (&cleEgales, &CleInferieure);
	for (int i = 0; i < n*2; ++i) {

		int indicePoint = tri[i];

		Segment* segCourant = rdm[indicePoint/2];

		if (indicePoint % 2 == 0) { // Extremité gauche

			T.Insere(indicePoint/2);

			int auDessus = T.Predecesseur(indicePoint/2);
			Segment* segAuDessus = (auDessus != -1) ? rdm[auDessus] : NULL;
			int auDessous = T.Successeur(indicePoint/2);
			Segment* segAuDessous = (auDessous != -1) ? rdm[auDessous] : NULL;

			if (segAuDessus != NULL && intersect(segCourant, segAuDessus)) {
				cout << "Intersection entre " << segCourant->x << " et " << segAuDessus->x << endl;
				return true;
			} else {
				/*cout << "Il n'y a pas d'intersection entre " 
				<< segCourant->x->getX() << "," << segCourant->x->getY() << " -- "
				<< segCourant->y->getX() << "," << segCourant->y->getY() << " "
				<< " et " << *segAuDessus << endl;*/
			}
			
			if (segAuDessous != NULL && intersect(segCourant, segAuDessous)) {
				cout << "Intersection entre " << segCourant->x << " et " << segAuDessous->x << endl;
				return true;
			} else {
				/*
				cout << "Il n'y a pas d'intersection entre " << *segCourant << " et " << *segAuDessous << endl;*/
			}

		} else {
			int auDessus = T.Predecesseur(indicePoint/2);
			Segment* segAuDessus = (auDessus != -1) ? rdm[auDessus] : NULL;
			int auDessous = T.Successeur(indicePoint/2);
			Segment* segAuDessous = (auDessous != -1) ? rdm[auDessous] : NULL;

			if (segAuDessus != NULL && segAuDessous != NULL && intersect(segAuDessus, segAuDessous)) {
				cout << "Intersection entre " << *(segAuDessus->x) << " et " << *(segAuDessous->x) << endl;
				return true;
			}
			T.Supprime(indicePoint/2);
		}
	}
	return false;
}


void exec() {
	int n = 10;
	//rdm = generatePointRandom(n);
	loadTest();

	Segment::displayAll(rdm, n);
	cout << (intersectionParBalayage(rdm, n) ? "OUI" : "NON") << endl;

}
