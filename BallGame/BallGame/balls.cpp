#include "balls.h"
#include "settings.h"
#include "game.h"
using namespace std;

GLfloat iden[16] = { 1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 
};

void Ball::draw() {
	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	GLfloat mat_ambient[] = { 0.3 * color.x, 0.3 * color.y, 0.3 * color.z, 1. };
	GLfloat mat_diffuse[] = { 0.5 * color.x, 0.5 * color.y, 0.5 * color.z, 1. };
	GLfloat mat_specular[] = { 1. * color.x, 1.0 * color.y, 1.0 * color.z, 1. };
	GLfloat mat_shininess[] = { 128. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (ft) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glMultMatrixf(rM); 
	gluSphere(quadratic, r, 50, 50);
	if (ft) {
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

void Ball::move() {
	p.x = p.x + v.x / FPS;
	p.z = p.z + v.z / FPS;
	p.y = Game::getGame()->getHeight(p.x, p.z) + r;
	//if (v.length() > 10.0 / FPS)
	//	v = (v.length() - 10.0 / FPS) * v.normalize();
	//else
	//	v = Vec(0, 0, 0);
	GLfloat tx = v.x / FPS;
	GLfloat ty = 0;
	GLfloat tz = v.z / FPS;
	Vec delta(tx, ty, tz);
	float theta = delta.length() / r / 3.1415 * 180;
	glPushMatrix();
	//glLoadMatrixf(rM);
	Vec z = delta.dc(Vec(0, 1, 0));
	glLoadIdentity();
	glRotatef(-theta, z.x, z.y, z.z);
	glMultMatrixf(rM);
	glGetFloatv(GL_MODELVIEW_MATRIX, rM);
	glPopMatrix();
}

void MovingBall::move() {
	if (clock() - t > CLOCKS_PER_SEC * 1) {
		//cout << f;
		f = Vec((rand() % 200 - 100) / 10.0, 0, (rand() % 200 - 100) / 10.0);
		t = clock();
	}
	//p.x = p.x + v.x / FPS;
	//p.z = p.z + v.z / FPS;
	v = v + f / FPS;
	Ball::move();
}

void FlyingBall::move() {
	if (!flying){
		p.x = p.x + v.x / FPS;
		p.z = p.z + v.z / FPS;
		if (clock() - t >= CLOCKS_PER_SEC * 1) {
			//Start going up
			//cout << "Start going up\n";
			landing = false;
			flying = true;
			v.x = 0;
			v.y = 30;
			v.z = 0;
			t = clock();
		}
		//Going
	}
	else {
		p = p + v / FPS;
		Vec f = Vec(0, -15, 0);
		v = v + f / FPS;
		if (!landing){
			if (v.y <= 0)
				v.y = 0;
			if (clock() - t >= CLOCKS_PER_SEC * 5) {
				t = clock();
				landing = true;
			}
		}
		else {
			if (p.y <= 10) {
				landing = false;
				flying = false;
				t = clock();
			}
		}
	}
}

void Ball::setTexture(GLuint text) {
	ft = true;
	texture = text;
	gluQuadricTexture(quadratic, GLU_TRUE);
}