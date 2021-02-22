#ifndef _TABLE_H_
#define _TABLE_H_

#include "drawable.h"
#include "libnoise/noise.h"
#include "noiseutils.h"
#include <string>
#pragma comment(lib, "libnoise/libnoise.lib")

using namespace std;
using namespace noise;
class Table: public Drawable {
protected:
	float width, length;
	Vec color;
	unsigned int id;
	module::Perlin perlin;
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	float** map;
public:
	Table(int, int, Vec = Vec(0,0,0));
	void draw();
	float getHeight(float x, float y);
};

#endif