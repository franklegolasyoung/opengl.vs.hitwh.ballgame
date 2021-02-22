#ifndef _BALLS_H_
#define _BALLS_H_

#include "drawable.h"
#include <gl/glut.h>
#include <time.h>
using namespace std;

extern GLfloat iden[16];

class Ball : public Drawable {
protected:
	float r;
	Vec p;	//Position
	Vec v;	//Velocity
	Vec color;	//Color		(x, y, z)=>(r, g, b)
	bool ft;
	GLuint texture;
	GLUquadricObj *quadratic;
	GLfloat rM[16];
public:
	Ball(Vec pp, float rr = 1, Vec cc = Vec(1, 1, 0)) 
		:p(pp), r(rr), v(Vec(0, 0, 0)), color(cc), ft(false), texture(0), quadratic(gluNewQuadric()) { 
		type = BALL; 
		for (int i = 0; i < 16; i++) {
			rM[i] = iden[i];
		}
	}
	void setTexture(GLuint text);
	virtual Vec getP() { return p; }
	virtual float getR() { return r; }
	virtual void setV(Vec vv) { v = vv; }
	virtual Vec getV() { return v; }
	virtual void setColor(Vec c) { color = c; }
	virtual void draw();
	virtual void move();
};

class NormalBall : public Ball {
public:
	NormalBall(Vec pp, float rr = 1, Vec cc = Vec(1, 1, 0)) :Ball(pp, rr, cc) { type = NORMALBALL; }
};

class MovingBall : public Ball {
protected:
	clock_t t;
	Vec f;
public:
	MovingBall(Vec pp, float rr = 1, Vec cc = Vec(1, 1, 0)) :Ball(pp, rr, cc), t(clock()) { type = MOVINGBALL; }
	virtual void move();
};

class FlyingBall : public Ball {
protected:
	clock_t t;
	bool flying;
	bool landing;
public:
	FlyingBall(Vec pp, float rr = 1, Vec cc = Vec(1, 1, 0)) :Ball(pp, rr, cc), t(clock()), flying(false), landing(false) { type = FLYINGBALL; }
	virtual void move();
};

class MotherBall : public Ball {
public:
	MotherBall(Vec pp, float rr = 1, Vec cc = Vec(1, 1, 0)) :Ball(pp, rr, cc) { type = MOTHERBALL; }
};

#endif