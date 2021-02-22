#ifndef _TYPES_H_
#define _TYPES_H_

#include <math.h>
#include <iostream>
using namespace std;

enum d_t {
	DRAWABLE = 0,
	BALL = 1,
	EDGE = 2,
	NORMALBALL = 5,
	MOVINGBALL = 9,
	MOTHERBALL = 21,
	FLYINGBALL = 41
};

struct Vec {
	float x;
	float y;
	float z;
	Vec(float xx = 0, float yy = 0, float zz = 0);
	float operator * (Vec& v);
	Vec operator - (Vec& v);
	Vec operator + (Vec& v);
	float length();
	Vec normalize();
	Vec dc(Vec& v);
};

Vec operator * (Vec& v, float k);

Vec operator * (float k, Vec&v);

Vec operator / (Vec& v, float k);

ostream& operator << (ostream& ost, Vec&v);
#endif