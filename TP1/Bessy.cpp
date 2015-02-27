#include "Bessy.h"


void TriLexicographique(point segments[], int t, int Tri[]){
  //En entree, Tri, tableau de taille 2*n, contient les indices dans 'segments' des sommets a trier, 
  //a l'initialisation Tri[i]=i, et t est la taille de Tri, donc t=2*n pour le premier appel.
  //En sorti, Tri contient les indices des sommets tries par ordre lexicographique croissant. 
  if(t>1){
    int pivot=Tri[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td
    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){//A droite
	Td[indice_droit]=Tri[i];
	indice_droit++;}
      else{//A gauche
	Tg[indice_gauche]=Tri[i];
	indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriLexicographique(segments,d,Td);}
    if(t-d-1>0){TriLexicographique(segments,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}

int* triLexico(Segment* segs[], int n) {

	point segments[n*2];

	for (int i = 0; i < n*2; i+=2) {
		segments[i].abscisse = segs[i/2]->x->getX();
		segments[i].ordonnee = segs[i/2]->x->getY();

		segments[i+1].abscisse = segs[i/2]->y->getX();
		segments[i+1].ordonnee = segs[i/2]->y->getY();
	}

	int* tabTri = new int[n*2];
	for(int i=0;i<2*n;i++){
		tabTri[i]=i;
	}

	TriLexicographique(segments, n*2, tabTri);

	return tabTri;
}

