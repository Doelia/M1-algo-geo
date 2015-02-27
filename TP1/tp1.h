#ifndef TP1_H
#define TP1_H

#include "Segment.h"
#include "Point.h"
#include "ARN.h"
#include "Bessy.h"
#include <time.h>

Segment** generatePointRandom(int n);
bool cleEgales(int cle1, int cle2);
bool CleInferieure(int cle1, int cle2);
bool intersect(Segment* s1, Segment* s2);
bool intersectionParBalayage(Segment* segments[], int n);
void exec();

#endif
