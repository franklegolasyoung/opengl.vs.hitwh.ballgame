#ifndef _H_SPARK_
#define _H_SPARK_

#include "consumable.h"
#include "types.h"
#include <time.h>

class Spark :public Consumable {
private:
	clock_t t;
public:
	Spark(Vec pos);
	void draw();
	void move();
};

class SparkComponent : public Consumable {
private:
	Vec position, velocity;
	float size;
	clock_t t;
	float lifetime;
	float cr, cg, cb;
public:
	SparkComponent(Vec pos, Vec v, float size, float lifetime);
	void draw();
	void move();
};

#endif