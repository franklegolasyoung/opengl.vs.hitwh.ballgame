#ifndef _GAME_H_
#define _GAME_H

#include "drawable.h"
#include "generator.h"
#include "balls.h"
#include "consumable.h"
#include <list>
#include "table.h"

using namespace std;

class Game : public Drawable{
protected:
	MotherBall* motherBall;
	Vec mouse;
	int score;
	Generator gen;
	static Game* game;
	list<Consumable*> cons;
	Game();
	Table* table;
public:
	static Game* getGame();
	void move();
	void setMouse(Vec);
	void draw();
	void launch();
	void addConsumable(Consumable* con);
	Vec getMotherBallPos();
	float getHeight(float x, float y);
};

#endif