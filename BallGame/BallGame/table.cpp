#include "table.h"
#include "gl/glut.h"
#include "table3DS.h"
#include <iostream>
using namespace std;

#define TABLE_HEIGHT 10

Table::Table(int w, int l, Vec c) :width(w), length(l), color(c), id(0) {
	id = Gen3DObjectList();
	perlin.SetOctaveCount(2);
	perlin.SetFrequency(2.0);
	heightMapBuilder.SetSourceModule(perlin);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(w + 1, l + 1);
	int x = rand() % 1024;
	int y = rand() % 1024;
	heightMapBuilder.SetBounds(x, x + 4, y, y + 4);
	heightMapBuilder.Build();
	map = new float*[w + 1];
	for (int i = 0; i <= w; i++) {
		map[i] = new float[l + 1];
	}
	float min = 10;
	float max = -10;
	for (int i = 0; i <= w; i++) {
		for (int j = 0; j <= l; j++) {
			map[i][j] = heightMap.GetValue(i, j); 
			if (map[i][j] > max)
				max = map[i][j];
			if (map[i][j] < min)
				min = map[i][j];
		}
	}
	cout << max << " " << min << endl;
	for (int i = 0; i <= w; i++) {
		for (int j = 0; j <= l; j++) {
			map[i][j] = ((map[i][j] - min) / (max - min)) *  10 + 0.1;
		}
	}
}


void Table::draw() {
	glPushMatrix();
	glCallList(id);
	glPopMatrix();
	//GLfloat mat_ambient[] = { 0.231373f,0.462745f,0.231373f, 1};
	//GLfloat mat_diffuse[] = { 0.231373f,0.462745f,0.231373f, 1};
	//GLfloat mat_specular[] = { 1.32459f,1.32459f,1.32459f , 1};
	GLfloat mat_ambient[] = { 0, 0.1f, 0};
	GLfloat mat_diffuse[] = { 0, 0.5f, 0};
	GLfloat mat_specular[] = { 0, 0, 0};
	GLfloat mat_shininess[] = { 128. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	for (int i = -width / 2; i < width / 2 - 1; i++) {
		for (int j = -length / 2; j < length / 2 - 1; j++) {
			glBegin(GL_QUADS);
			Vec v1(1, getHeight(i + 1, j) - getHeight(i, j), 0);
			Vec v2(0, getHeight(i, j + 1) - getHeight(i, j), 1);
			Vec v = v2.dc(v1);
			v = v.normalize();
			if (v * v1 > 1e-6 || v * v2 > 1e-6) {
				cout << "Error: \n";
				cout << v1 << v2 << v << endl;
				cout << v * v1 << v * v2 << endl;
			}
			glNormal3f(v.x, v.y, v.z); glVertex3f(i, getHeight(i, j), j);
			glNormal3f(v.x, v.y, v.z); glVertex3f(i + 1, getHeight(i + 1, j), j);
			glNormal3f(v.x, v.y, v.z); glVertex3f(i + 1, getHeight(i + 1, j + 1), j + 1);
			glNormal3f(v.x, v.y, v.z); glVertex3f(i, getHeight(i, j + 1), j + 1);
			glEnd();
		}
	}
	return;
}

float Table::getHeight(float x, float z) {
	if (x > width / 2 || x < -width / 2 || z > length / 2 || z < -length / 2)
		return 0.1;
	return map[int(x + width/2)][int(z + length / 2)];
	float xx = float(x + width / 2) / width;
	float zz = float(z + length / 2) / length;
	if (xx > 1 || xx < 0 || zz > 1 || zz < 0)
		return 0.1;
	if (xx < 0.8 && xx > 0.2 && zz < 0.8 && zz > 0.2) {
		return 10 + 0.1;
	}
	float t1 = xx < zz ? xx : zz;	// xx, zz 中比较小的
	float t2 = xx + zz - t1;		// xx, zz 中比较大的
	t2 = 1 - t2;
	float minn = t1 < t2 ? t1: t2;
	return minn * 50 + 0.1;
}