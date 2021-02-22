#include "drawString.h"
#include <GL/glut.h>


void drawString(float x, float y, void* font, string s) {
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	for (int i = 0; i < s.size(); i++) {
		glutBitmapCharacter(font, s[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
