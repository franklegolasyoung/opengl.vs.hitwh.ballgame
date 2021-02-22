#include "drawable.h"
#include "balls.h"
#include "edges.h"
#include "types.h"
#include <iostream>
#include "game.h"
#include "spark.h"
using namespace std;

int collide(Drawable* a, Drawable* b) {
	if (a->getType() & BALL & b->getType()) {
		//a, b are both balls
		Ball* b1 = (Ball*)a;
		Ball* b2 = (Ball*)b;
		Vec p1 = b1->getP();
		Vec p2 = b2->getP();
		if ((p2 - p1).length() > b1->getR() + b2->getR())
			return -1;
		Vec v1 = b1->getV();
		Vec v2 = b2->getV();
		//cout << "Before: \n";
		//cout << "p1:" << p1 << endl;
		//cout << "p2:" << p2 << endl;
		//cout << "v1: "<< v1 << endl;
		//cout << "v2: "<< v2 << endl;
		//cout << "E: " << v1.length()*v1.length() + v2.length()*v2.length() << endl;
		Vec normal = (p2 - p1).normalize();
		Vec tangent = Vec(normal.z, 0, -normal.x);
		//判断是否相向运动：
		if ((p1 - p2) * (v1 - v2) > 0)
			return -1;
		Vec vn2 = v1 * normal * normal;
		Vec vt1 = v1 * tangent * tangent;
		Vec vn1 = v2 * normal * normal;
		Vec vt2 = v2 * tangent * tangent;
		b1->setV(vt1 + vn1);
		b2->setV(vt2 + vn2);
		//添加火星碰撞
		Game* g = Game::getGame();
		g->addConsumable(new Spark((p1 + p2)/2));
		//cout << "After: \n";
		//cout << "v1: "<< b1->getV() << endl;
		//cout << "v2: "<< b2->getV() << endl;
		//cout << "E: " << b1->getV() * b1->getV() + b2->getV()*b2->getV() << endl;
		if (b1->getType() != MOTHERBALL) {
			Ball* temp = b1;
			b1 = b2;
			b2 = temp;
		}
		if (b1->getType() != MOTHERBALL)
			return 0;
		else
			switch (b2->getType()){
			case NORMALBALL:
				return 1;
			case MOVINGBALL:
				return 5;
			case FLYINGBALL:
				return 10;
			}
	}
	else if ((a->getType() & BALL) && (b->getType() & EDGE)) {
		//a is a ball and b is an edge
		Ball* ball = (Ball*)a;
		Edge* edge = (Edge*)b;
		Vec p = ball->getP();
		float x = p.x;
		float z = p.z;
		float r = ball->getR();
		float x1 = edge->getX1();
		float z1 = edge->getZ1();
		float x2 = edge->getX2();
		float z2 = edge->getZ2();
		Vec v = ball->getV();
		if (x1 == x2 && abs(x - x1) <= r){
			//cout << v;
			//cout << edge->getDir();
			if (v * edge->getDir() < 0) {
				ball->setV(Vec(-v.x, 0, v.z));
				return 0;
			}
		}
		if (z1 == z2 && abs(z - z1) <= r)
			if (v * edge->getDir() < 0){
				ball->setV(Vec(v.x, 0, -v.z));
				return 0;
			}
		/*
		if (x1 == x2 && abs(x - x1) <= r)
			ball->setV(Vec(-v.x, 0, v.z));
		if (z1 == z2 && abs(z - z1) <= r)
			ball->setV(Vec(v.x, 0, -v.z));
		*/
		return -1;
	}
	else if ((b->getType() & BALL) && (a->getType() & EDGE)) {
		//b is a ball and a is an edge
		return collide(b, a);
	}
	return 0;
}