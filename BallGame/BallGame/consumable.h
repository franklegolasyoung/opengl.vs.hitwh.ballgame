#ifndef _H_CONSUMABLE_
#define _H_CONSUMABLE_

#include "drawable.h"

class Consumable : public Drawable {
protected:
	bool dead;
public:
	Consumable() :dead(false) {}
	virtual void draw() { Drawable::draw(); }
	virtual void move() { Drawable::move(); }
	bool isDead() { return dead; }
};

#endif