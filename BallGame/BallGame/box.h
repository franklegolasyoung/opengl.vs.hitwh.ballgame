#ifndef _H_BOX_
#define _H_BOX_

#include "drawable.h"
#include <GL\glut.h>

class Box: public Drawable {
private:
	float x, y, z;
	GLuint w1, w2, w3, w4, ground, ceiling;
public:
	Box(float x, float y, float z);
	void draw();
};

#endif