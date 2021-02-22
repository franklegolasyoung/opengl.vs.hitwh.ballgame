#ifndef _H_RESPONSE_
#define _H_RESPONSE_

#include "consumable.h"
#include "time.h"
#include "gl\glut.h"

class MouseResponse : public Consumable {
private:
	clock_t t;
	Vec position;
	GLUquadricObj* quad;
public:
	MouseResponse(Vec pos);
	void draw();
	void move();
};

#endif