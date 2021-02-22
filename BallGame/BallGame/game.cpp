#include "game.h"
#include "balls.h"
#include "types.h"
#include "edges.h"
#include "table.h"
#include "box.h"
#include "drawString.h"
#include "texture.h"
#include <sstream>
using namespace std;

#define TABLE_WIDTH 150
#define TABLE_LENGTH 270

#define INITIAL_LAUNCH_VELOCITY 100

Game* Game::game = NULL;

Vec nbp[6] = { Vec(20, 5, 20), Vec(20, 5, -20), Vec(-20, 5, 20), Vec(-20, 5, -20), Vec(0, 5, 40), Vec(0, 5, -40) };
Vec mbp[6] = { Vec(50, 5, 10), Vec(30, 5, 0), Vec(0, 5, 20), Vec(40, 5, 20), Vec(-40, 5, 20), Vec(-40, 5, 40) };
Vec mbv[6] = { Vec(3, 0, 0), Vec(-3, 0, 3), Vec(3, 0, 3), Vec(3, 0, 3), Vec(3, 0, 3), Vec(3, 0, 3) };

Vec motherBallPosition = Vec(0, 5, 70);

Game* Game::getGame() {
	if (game == NULL) {
		game = new Game();
	}
	return game;
}

Game::Game() {
	gen.set2Color(utils::Color(255, 127, 127, 255), utils::Color(255, 0, 0, 255));
	gen.generate("RedBall.bmp");
	gen.set2Color(utils::Color(255, 255, 127, 255), utils::Color(255, 255, 0, 255));
	gen.generate("YellowBall.bmp");
	gen.set2Color(utils::Color(255, 127, 255, 255), utils::Color(255, 0, 255, 255));
	gen.generate("BlueBall.bmp");
	gen.set2Color(utils::Color(255, 255, 255, 255), utils::Color(192, 192, 192, 255));
	gen.generate("WhiteBall.bmp");
	GLuint redTexture = ATLLoadTexture("RedBall.bmp");
	GLuint yellowTexture = ATLLoadTexture("YellowBall.bmp");
	GLuint blueTexture = ATLLoadTexture("BlueBall.bmp");
	GLuint whiteTexture = ATLLoadTexture("WhiteBall.bmp");
	for (int i = 0; i < 6; i++) {
		NormalBall* nb = new NormalBall(nbp[i], 5);
		nb->setTexture(yellowTexture);
		nb->setColor(Vec(1, 1, 1));
		add(nb);
	};
	for (int i = 0; i < 6; i++) {
		MovingBall* mb = new MovingBall(mbp[i], 5);
		mb->setTexture(redTexture);
		mb->setColor(Vec(1, 1, 1));
		//mb->setV(mbv[i]);
		add(mb);
	}
	table = new Table(TABLE_WIDTH, TABLE_LENGTH, Vec(0, 0, 0));
	add(table);
	FlyingBall* fb = new FlyingBall(Vec(0, getHeight(0, 0) + 5, 0), 5);
	fb->setTexture(blueTexture);
	fb->setColor(Vec(0, 1, 1));
	add(fb);
	add(new Edge(-TABLE_WIDTH / 2, TABLE_LENGTH / 2, TABLE_WIDTH / 2, TABLE_LENGTH / 2, Vec(0, 0, -1)));
	add(new Edge(-TABLE_WIDTH / 2, TABLE_LENGTH / 2, -TABLE_WIDTH / 2, -TABLE_LENGTH / 2, Vec(1, 0, 0)));
	add(new Edge(-TABLE_WIDTH / 2, -TABLE_LENGTH / 2, TABLE_WIDTH / 2, -TABLE_LENGTH / 2, Vec(0, 0, 1)));
	add(new Edge(TABLE_WIDTH / 2, -TABLE_LENGTH / 2, TABLE_WIDTH / 2, TABLE_LENGTH / 2, Vec(-1, 0, 0)));
	add(new Box(4 * TABLE_WIDTH, 400 ,4 * TABLE_LENGTH));
	motherBall = new MotherBall(motherBallPosition, 5);
	motherBall->setTexture(whiteTexture);
	motherBall->setColor(Vec(1, 1, 1));
	add(motherBall);
}

void Game::move() {
	Drawable::move();
	list<Consumable*>::iterator iter = cons.begin();
	list<Consumable*>::iterator temp;
	while (iter != cons.end()) {
		(*iter)->move();
		temp = iter;
		iter++;
		if ((*temp)->isDead()) {
			delete (*temp);
			cons.erase(temp);
		}
	}
	for (list<Drawable*>::iterator i = elements.begin(); i != elements.end(); i++)
		for (list<Drawable*>::iterator j = i; j != elements.end(); j++) {
			if (i != j){
				int c = collide(*i, *j);
				if (c > 0) {
					score += c;
				}
			}
		}
}

void Game::setMouse(Vec vec) {
	mouse = vec;
}
void Game::draw() {
	Drawable::draw();
	list<Consumable*>::iterator iter = cons.begin();
	while (iter != cons.end()) {
		(*iter)->draw();
		iter++;
	}
	glPushMatrix();
	stringstream stream;
	string temp;
	stream << score;
	stream >> temp;
	glColor3f(1.0, 1.0, 1.0);
	drawString(-1.0, 0.9, GLUT_BITMAP_HELVETICA_18, " Rules: Collide to get more points");
	drawString(-1.0, 0.8, GLUT_BITMAP_HELVETICA_18, " Yellow: 1  Red: 5  Blue: 10");
	drawString(-1.0, 0.7, GLUT_BITMAP_HELVETICA_18, " Score: "+temp);
	GLfloat mat_ambient[] = { 1, 1, 1, 1. };
	GLfloat mat_diffuse[] = { 1, 1, 1, 1. };
	GLfloat mat_specular[] = { 1, 1, 1, 1. };
	GLfloat mat_shininess[] = { 128. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glVertex3f(motherBall->getP().x, motherBall->getP().y, motherBall->getP().z);
	glVertex3f(mouse.x, mouse.y, mouse.z);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

void Game::launch() {
	Vec velocity = Vec(mouse.x - motherBall->getP().x, 0, mouse.z - motherBall->getP().z).normalize() * INITIAL_LAUNCH_VELOCITY;
	motherBall->setV(velocity);
}

void Game::addConsumable(Consumable* con) {
	cons.push_back(con);
}

Vec Game::getMotherBallPos() {
	return motherBall->getP();
}

float Game::getHeight(float x, float y) {
	return table->getHeight(x, y);
}