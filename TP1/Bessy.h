#ifndef BESSH_H
#define BESSH_H

#include "Segment.h"

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;

void TriLexicographique(point segments[], int t, int Tri[]);

int* triLexico(Segment* segs[], int n);

#endif