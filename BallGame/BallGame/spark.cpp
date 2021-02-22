#include "spark.h"
#include <GL\GLUT.H>
#include "settings.h"

#define SPARK_AMOUNT 100
#define SPARK_INITIAL_VELOCITY 5
#define SPARK_R 10
#define LIFE 3
#define SPARK_SPHERE_R 0.4

Spark::Spark(Vec pos) {
	t = clock();
	for (int i = 0; i < SPARK_AMOUNT; i++) {
		int x = -SPARK_R / 2 + rand() % SPARK_R;
		int y = -SPARK_R / 2 + rand() % SPARK_R;
		int z = -SPARK_R / 2 + rand() % SPARK_R;
		Vec nPos(pos.x + x, pos.y + y, pos.z + z);
		add(new SparkComponent(nPos, (nPos - pos).normalize()*SPARK_INITIAL_VELOCITY*(rand() % 1000/1000.0), SPARK_SPHERE_R, 2 * (rand() % 1000 / 1000.0)));
	}
}

void Spark::draw() {
	if (dead)
		return;
	Drawable::draw();
}

void Spark::move() {
	if (dead)
		return;
	if (clock() - t > CLOCKS_PER_SEC * LIFE) {
		dead = true;
		return;
	}
	Drawable::move();
}

SparkComponent::SparkComponent(Vec p, Vec v, float s, float l) {
	position = p;
	velocity = v;
	size = s;
	lifetime = l;
	t = clock();
	dead = false;
	cr = (rand() % 1000)*0.001;
	cg = (rand() % 1000)*0.001;
	cb = (rand() % 1000)*0.001;
}

void SparkComponent::draw() {
	if (dead)
		return;
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
	glDisable(GL_LIGHTING);
	glTranslatef(position.x, position.y, position.z);
	glColor4f(cr, cg, cb, 1 - float(clock() - t) / CLOCKS_PER_SEC / lifetime);
	glutSolidSphere(size, 10, 10);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void SparkComponent::move() {
	if (dead)
		return;
	if (clock() - t > CLOCKS_PER_SEC * lifetime) {
		dead = true;
		return;
	}
	position = position + velocity / FPS;
	//velocity = velocity + Vec(0, -5, 0) / FPS;
}