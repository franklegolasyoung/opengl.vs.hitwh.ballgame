#ifndef _EDGES_H_
#define _EDGES_H_

#include "drawable.h"
using namespace std;

class Edge : public Drawable {
protected:
	float x1, z1, x2, z2;
	Vec dir;
public:
	Edge(float xx1, float zz1, float xx2, float zz2, Vec vec) :x1(xx1), z1(zz1), x2(xx2), z2(zz2), dir(vec) { type = EDGE; }
	Vec getDir() { return dir; }
	float getX1() { return x1; }
	float getZ1() { return z1; }
	float getX2() { return x2; }
	float getZ2() { return z2; }
};

#endif