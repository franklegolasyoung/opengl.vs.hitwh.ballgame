#include "box.h"
#include "texture.h"

Box::Box(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {
	w1 = ATLLoadTexture("image/wall.jpeg");
	w2 = w1;
	w3 = w1;
	w4 = w1;
	ground = ATLLoadTexture("image/floor.jpeg");
	ceiling = ATLLoadTexture("image/roof.jpg");
}

void Box::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, w1); 
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1. };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1. };
	GLfloat mat_specular[] = { 1., 1.0, 1.0, 1. };
	GLfloat mat_shininess[] = { 128. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(-x / 2, -y / 2, -z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(x / 2, -y / 2, -z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(x / 2, y / 2, -z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(-x / 2, y / 2, -z / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, w2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(-x / 2, -y / 2, -z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(-x / 2, -y / 2, z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(-x / 2, y / 2, z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(-x / 2, y / 2, -z / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, w3);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(-x / 2, -y / 2, z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(x / 2, -y / 2, z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(x / 2, y / 2, z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(-x / 2, y / 2, z / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, w4);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(x / 2, -y / 2, -z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(x / 2, -y / 2, z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(x / 2, y / 2, z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(x / 2, y / 2, -z / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, ceiling);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(-x / 2, y / 2, -z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(-x / 2, y / 2, z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(x / 2, y / 2, z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(x / 2, y / 2, -z / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, ground);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(-x / 2, -y / 2, -z / 2);
		glTexCoord2f(1.0, 0.0); glVertex3f(-x / 2, -y / 2, z / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(x / 2, -y / 2, z / 2);
		glTexCoord2f(0.0, 1.0); glVertex3f(x / 2, -y / 2, -z / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
