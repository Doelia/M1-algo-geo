#ifndef TP1_H
#define TP1_H

#include "Segment.h"
#include "Point.h"
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include "tests.h"


vector<Point*> points;
int nbrFlips = 0;

bool isValid(Point* p) {
  for (auto i : points) {
    if (i->getX() == p->getX() && i->getY() == p->getY())
      return false;
  }
  return true;
}

void generer(int n) {
  points.clear();
  for (int i = 0; i < n; i++) {
    Point* p1 = new Point(rand()%500+50, rand()%600+50, 0);
    if (isValid(p1))
      points.push_back(p1);
    // else
    //   i--;
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
  std::vector<Triangle*> voisins;
  bool inAlphaShape;

  Triangle() {

  }

  Triangle(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
  }

  std::vector<int> getPoints() {
    std::vector<int> pts;
    pts.push_back(a);
    pts.push_back(b);
    pts.push_back(c);
    return pts;
  }

  void afficher() {
    glBegin(GL_LINE_STRIP);
    getPoint(a)->draw();
    getPoint(b)->draw();
    getPoint(c)->draw();
    getPoint(a)->draw();
    glEnd();
  }

  void afficherIndices() {
    cout << a << ", " << b << ", " << c << endl;
  }

  void afficherInAlphaShape() {
    int a = 1;
    int b = 1;
    int c = 1;

    for (auto i : this->voisins) {
      if(i->inAlphaShape) {
        for (auto j : i->getPoints()) {
         a += j == this->a;
         b += j == this->b;
         c += j == this->c;
       }
     }
   }

   glBegin(GL_LINE_STRIP);
   if(a == 2) getPoint(this->a)->draw();
   if(b == 2) getPoint(this->b)->draw();
   if(c == 2) getPoint(this->c)->draw();

    // if(a < 3) getPoint(this->a)->draw();
    // if(b < 3) getPoint(this->b)->draw();
    // if(c < 3) getPoint(this->c)->draw();
   glEnd();
 }

 vector<int> getSommets() {
  vector<int> v;
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);
  return v;
}

bool equals(Triangle* t) {
  int cpt = 0;
  for (auto i : this->getSommets()) {
    for (auto j : t->getSommets()) {
     cpt += (i == j);
   }
 }
 return cpt == 3;
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

    /*if (points[i+1]->equals(*points[i])) {
      continue;
      }*/

      int j = 0;
      while (true) {
        Vector a(points[i+1], points[EC[j]]);
        Vector b(points[i+1], points[EC[j+1]]);
        if (a.getDeter(&b) <= 0) {
         Triangle* nouv = new Triangle();
         nouv->a = EC[j];
         nouv->b = EC[j+1];
         nouv->c = i+1;
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
      if (a.getDeter(&b) >= 0) {
       Triangle* nouv = new Triangle();
       nouv->a = EC[j];
       nouv->b = EC[j-1];
       nouv->c = i+1;
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
    if(a->getX() == b->getX())
     return a->getY() < b->getY();
   return a->getX() < b->getX();
 });
}

bool vectorContains(std::vector<Triangle*> triangles, Triangle* t) {
  for (auto i : triangles) {
    if(i->equals(t))
      return true;
  }
  return false;
}

std::vector<Triangle*> getVoisinsForTriangle(Triangle* t, std::vector<Triangle*> triangles) {
  std::vector<Triangle*> voisins;
  for (auto t1 : triangles) {
    vector<int> points = t->getSommets();
    for (auto i : t1->getSommets()) {
      points.erase(remove(points.begin(), points.end(), i), points.end());
    }
    if (points.size() == 1 && !vectorContains(voisins, t1)) {
      voisins.push_back(t1);
    }
  }
  return voisins;
}

void removeDuplicatesVoisins(Triangle* t) {
  std::vector<Triangle*> vec;
  for (auto i : t->voisins) {
    if(!vectorContains(vec, i) && !vectorContains(vec, t)) {
      vec.push_back(i);
    }
  }
  t->voisins = vec;
}

std::vector<Triangle*> removeTriangle(std::vector<Triangle*> triangles, Triangle* t) {
  std::vector<Triangle*> var;
  for (auto i : triangles) {
    if(!i->equals(t))
      var.push_back(i);
  }
  return var;
}

// Intervertit l'arret IJ dans les triangles t1 et t2
void flip(Triangle* t1, Triangle* t2, std::vector<Triangle*> var) {
  std::vector<Triangle*> triangles;

  for (auto i : t1->voisins) {
    if(!i->equals(t2)) {
      triangles.push_back(i);
      // i->voisins.erase(remove(i->voisins.begin(), i->voisins.end(), t1), i->voisins.end());
      i->voisins = removeTriangle(i->voisins, t1);
      // i->voisins = removeTriangle(i->voisins, t2);
    }
  }
  
  for (auto i : t2->voisins) {
    if(!i->equals(t1)) {
      triangles.push_back(i);
      // i->voisins.erase(remove(i->voisins.begin(), i->voisins.end(), t2), i->voisins.end());
      // i->voisins = removeTriangle(i->voisins, t1);
      i->voisins = removeTriangle(i->voisins, t2);
    }
  }

  triangles.push_back(t1);
  triangles.push_back(t2);
  t1->voisins.clear();
  t2->voisins.clear();

  // std::cout << triangles.size() << std::endl;

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

for (auto i : triangles) {
  std::vector<Triangle*> t =  getVoisinsForTriangle(i, (triangles.size() > 100)?var:triangles);
  for (auto j : t) {
    i->voisins.push_back(j);
  }
}

for (auto i : triangles) {
  removeDuplicatesVoisins(i);
}
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

Point getCenter(Triangle t) {
  double x,y;
  circumCircleCenter(getPoint(t.a)->getX(), getPoint(t.a)->getY(),
   getPoint(t.b)->getX(), getPoint(t.b)->getY(),
   getPoint(t.c)->getX(), getPoint(t.c)->getY(),
   x, y);

  Point p (x,y,0);
  return p;
}

double getRayon(Triangle t) {
  Point center;
  center = getCenter(t);
  Vector v(&center, getPoint(t.a));
  return v.getNorme();
}

bool flipPossible(Triangle t1, Triangle t2) {
  vector<int> points = t2.getSommets();
  for (auto i : t1.getSommets()) {
    points.erase(remove(points.begin(), points.end(), i), points.end());
  }
  if (points.size() != 1) {
    return false;
  }
  // std::cout << "avant pointout" << std::endl;
  int pointOut = points[0];
  vector<int> pointIn = t1.getSommets();
  int a = pointIn[0];
  int b = pointIn[1];
  int c = pointIn[2];
  int d = pointOut;

  double x;
  double y;
  circumCircleCenter(getPoint(a)->getX(), getPoint(a)->getY(),
   getPoint(b)->getX(), getPoint(b)->getY(),
   getPoint(c)->getX(), getPoint(c)->getY(),
   x, y);
  Point center;
  center = getCenter(Triangle(a,b,c));
  Vector v(&center, getPoint(a));
  Vector toD(&center, getPoint(d));
  return (v.getNorme() > toD.getNorme());
}

void matriceAdjacence(std::vector<Triangle*> triangles) {
  cout << "calcul matriceAdjacence " << endl;
  for (auto t : triangles) {
    t->voisins = getVoisinsForTriangle(t, triangles);
  }
}

void delaunay(vector<Triangle*> triangles) {
  cout << "Nous allons traiter " << triangles.size() << " triangles" << endl;
  std::map<std::vector<Triangle*>, int> m;
  bool flipped = true;
  int cpt = 0;

  while (flipped) {
   glClear(GL_COLOR_BUFFER_BIT);
   for (Triangle* v : triangles) {
     v->afficher();
   }
   glFlush();
   
   flipped = false;
   std::cout << cpt++ << std::endl;
   for (Triangle* i : triangles) {

    for (Triangle* j : i->voisins) {
     std::vector<Triangle*> key;
     key.push_back(i);
     key.push_back(j);
     if(flipPossible(*i, *j) && m.count(key) == 0) {
       m.insert(std::pair<std::vector<Triangle*>, int>(key, 1));
       flip(i, j, triangles);
       flipped = true;
       nbrFlips++;
       cout << "flip # " << nbrFlips << " entre ";
       i->afficherIndices();
       j->afficherIndices();
       break;
     }
   }
 }
}

}


int getNbVoisinsForAlphaShape(Triangle* t) {
  int n = 0;
  for (auto i : t->voisins) {
    n += i->inAlphaShape;
  }
  return n;

}

void alphaComplexe(float alpha, std::vector<Triangle*> triangles) {
  for (Triangle* v : triangles) {
    float rayon = getRayon(*v);
    if (rayon < alpha) {
      v->afficher();
    }
  }
}


void alphaShape(float alpha, std::vector<Triangle*> triangles) {
  std::vector<Triangle*> t;
  for (Triangle* v : triangles) {
    float rayon = getRayon(*v);
    // std::cout << v->voisins.size() << std::endl;
    if(rayon < alpha) {
      t.push_back(v);
      v->inAlphaShape = true;
    } else {
      v->inAlphaShape = false;
    }
  }

  for (auto i : t) {
    if(getNbVoisinsForAlphaShape(i) < 3) {
      i->afficherInAlphaShape();
    }
  }
}

struct pointTest {
  int abscisse;
  int ordonnee;
};


void loadTest() {
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

  for (int i = 0; i < n; i++) {
    points.push_back(new Point(sommet[i].abscisse, sommet[i].ordonnee, 0));
  }


}

void loadTest3() {
  int n = 32;
  pointTest sommet[n];

sommet[0].abscisse=100;
sommet[0].ordonnee=100;
sommet[1].abscisse=100;
sommet[1].ordonnee=500;
sommet[2].abscisse=120;
sommet[2].ordonnee=300;
sommet[3].abscisse=140;
sommet[3].ordonnee=100;
sommet[4].abscisse=140;
sommet[4].ordonnee=500;
sommet[5].abscisse=160;
sommet[5].ordonnee=300;
sommet[6].abscisse=180;
sommet[6].ordonnee=100;
sommet[7].abscisse=180;
sommet[7].ordonnee=500;
sommet[8].abscisse=200;
sommet[8].ordonnee=300;
sommet[9].abscisse=220;
sommet[9].ordonnee=100;
sommet[10].abscisse=220;
sommet[10].ordonnee=500;
sommet[11].abscisse=240;
sommet[11].ordonnee=300;
sommet[12].abscisse=260;
sommet[12].ordonnee=100;
sommet[13].abscisse=260;
sommet[13].ordonnee=500;
sommet[14].abscisse=280;
sommet[14].ordonnee=300;
sommet[15].abscisse=300;
sommet[15].ordonnee=100;
sommet[16].abscisse=300;
sommet[16].ordonnee=500;
sommet[17].abscisse=320;
sommet[17].ordonnee=300;
sommet[18].abscisse=340;
sommet[18].ordonnee=100;
sommet[19].abscisse=340;
sommet[19].ordonnee=500;
sommet[20].abscisse=360;
sommet[20].ordonnee=300;
sommet[21].abscisse=380;
sommet[21].ordonnee=100;
sommet[22].abscisse=380;
sommet[22].ordonnee=500;
sommet[23].abscisse=400;
sommet[23].ordonnee=300;
sommet[24].abscisse=420;
sommet[24].ordonnee=100;
sommet[25].abscisse=420;
sommet[25].ordonnee=500;
sommet[26].abscisse=440;
sommet[26].ordonnee=300;
sommet[27].abscisse=460;
sommet[27].ordonnee=100;
sommet[28].abscisse=460;
sommet[28].ordonnee=500;
sommet[29].abscisse=480;
sommet[29].ordonnee=300;
sommet[30].abscisse=500;
sommet[30].ordonnee=100;
sommet[31].abscisse=500;
sommet[31].ordonnee=500;


  for (int i = 0; i < n; i++) {
    points.push_back(new Point(sommet[i].abscisse, sommet[i].ordonnee, 0));
  }


}



int ok = 0;
vector<Triangle*> triangles;
vector<Triangle*> base;

void ex3() {

   glColor4f(0,1,0,0.5f);

  if (ok == 0) {
    cout << "Génération..." << endl;
    int n = 20;
    loadTest();
    trierWithAbssice();
    Point::displayAll(vectorToTab(points), n, false);
    triangles = triangulation();
    base = triangulation();
    ok++;
    return;
  }

  if (ok % 2 == 0) {
     for (Triangle* v : base) {
      v->afficher();
    }
    triangles = base;
  } else {
    matriceAdjacence(triangles);
    delaunay(triangles);
  }

  ok++;

  
}

void ex4() {
     glColor4f(0,1,0,0.5f);

  if (ok == 0) {
    cout << "Génération..." << endl;
    int n = 32;
    loadTest3();
    trierWithAbssice();
    Point::displayAll(vectorToTab(points), n, false);
    triangles = triangulation();
    base = triangulation();
    ok++;
    return;
  }

  if (ok % 2 == 0) {
     for (Triangle* v : base) {
      v->afficher();
    }
    triangles = base;
  } else {
    matriceAdjacence(triangles);
    delaunay(triangles);
  }

  ok++;

}


/**

20 => 23 (1x)
100 => 294 flips (3x)
200 => 725 flips (4x)
300 => 1250 (4x)
400 => 1800 (4.5x)
600 => 2900 (4.8x)
800 => 4200 (5.25x)

**/

void ex5() {
   glColor4f(0,1,0,0.5f);

  if (ok == 0) {
    cout << "Génération..." << endl;
    int n = 800;

    generer(n);
    trierWithAbssice();
    Point::displayAll(vectorToTab(points), n, false);
    triangles = triangulation();
    base = triangulation();
    ok++;
    return;
  }

  if (ok % 2 == 0) {
     for (Triangle* v : base) {
      v->afficher();
    }
    triangles = base;
  } else {
    matriceAdjacence(triangles);
    delaunay(triangles);
  }

  ok++;
}

void tp4(int alpha, bool ashape) {

  if (ok == 0) {
    ok++;
    return;
  }

  if (ok >= 2) {
    if(ashape) 
      alphaShape(alpha, triangles);
    else
      alphaComplexe(alpha, triangles);
    return;
  }

  //*

  const int n = 800;

  Point** sommet = sommets_801;

  points.clear();

  for (int i = 0; i < n; ++i) {
    if(isValid(sommet[i]))
      points.push_back(sommet[i]);
  }
  // generer(n);
  std::cout << points.size() << std::endl;
  // Point::displayAll(vectorToTab(points), points.size(), false);
  std::cout << "generation ok" << std::endl;
  trierWithAbssice();
  cout << "tri ok" << endl;
  triangles = triangulation();
  cout << "Triangles OK" << endl;

  matriceAdjacence(triangles);
  delaunay(triangles);

  //*/
  ok++;
}

void ex6(int alpha, int ashape) {
  if (ok == 0) {
    ok++;
    return;
  }

  if (ok >= 2) {
    if(ashape) 
      alphaShape(alpha, triangles);
    else
      alphaComplexe(alpha, triangles);
    return;
  }

  //*

  const int n = 500;

  Point** sommet = new Point*[n];

  for (int iBaba = 0; iBaba < n; ++iBaba)  {
    sommet[iBaba] = new Point(baba[iBaba].a, baba[iBaba].b, 0);
  }


  points.clear();

  for (int i = 0; i < n; ++i) {
    if(isValid(sommet[i]))
      points.push_back(sommet[i]);
  }
  // generer(n);
  std::cout << points.size() << std::endl;
  // Point::displayAll(vectorToTab(points), points.size(), false);
  std::cout << "generation ok" << std::endl;
  trierWithAbssice();
  cout << "tri ok" << endl;
  triangles = triangulation();
  cout << "Triangles OK" << endl;

  matriceAdjacence(triangles);
  delaunay(triangles);

  //*/
  ok++;
}


void exec(int alpha, bool ashape) {

  nbrFlips = 0;

 // ex3();
  ex4();
  //ex5();
  //ex6(alpha, ashape);
  //tp4(alpha, ashape);

}

#endif
