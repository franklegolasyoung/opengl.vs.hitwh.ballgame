#include "response.h"

MouseResponse::MouseResponse(Vec pos){
	t = clock();
	position = pos;
	quad = gluNewQuadric();
}

void MouseResponse::draw() {
	if (dead)
		return;
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);
	glColor4f(1, 1, 1, 1 - float(clock() - t) / CLOCKS_PER_SEC / 1);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(90, 1, 0, 0);
	float now = float(clock() - t)/CLOCKS_PER_SEC;
	glDisable(GL_DEPTH_TEST);
	gluDisk(quad, 5 * now , 10 * now, 30, 30);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void MouseResponse::move() {
	if (dead)
		return;
	dead = (clock() - t) > CLOCKS_PER_SEC;
}