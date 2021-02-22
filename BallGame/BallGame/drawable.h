#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <list>
#include "types.h"
using namespace std;

class Drawable {
protected:
	list<Drawable*> elements;
	d_t type;
public:
	virtual ~Drawable();
	virtual void add(Drawable* d);
	virtual void remove(Drawable* d);
	virtual void draw();
	virtual void move();
	virtual d_t getType();
};

int collide(Drawable* a, Drawable* b);

#endif