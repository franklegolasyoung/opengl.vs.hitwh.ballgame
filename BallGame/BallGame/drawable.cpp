#include "drawable.h"
#include <math.h>
using namespace std;

//Destructor
Drawable::~Drawable() {
	list<Drawable*>::iterator iter = elements.begin();
	while (iter != elements.end()) {
		delete (*iter);
		iter++;
	}
}

//Add a new element
void Drawable::add(Drawable* d) {
	elements.push_back(d);
}

//Remove a element
void Drawable::remove(Drawable* d) {
	elements.remove(d);
}

//Draw
void Drawable::draw() {
	list<Drawable*>::iterator iter = elements.begin();
	while (iter != elements.end()) {
		(*iter)->draw();
		iter++;
	}
}

//Move
void Drawable::move() {
	list<Drawable*>::iterator iter = elements.begin();
	while (iter != elements.end()) {
		(*iter)->move();
		iter++;
	}
}

d_t Drawable::getType() {
	return type;
}

