#ifndef _H_GENERATOR_
#define _H_GENERATOR_

#include "libnoise/noise.h"
#include "noiseutils.h"
#include <string>
#pragma comment(lib, "libnoise/libnoise.lib")

using namespace std;
using namespace noise;

class Generator {
private:
	module::Perlin perlin;
	utils::NoiseMap colorMap;
	utils::NoiseMapBuilderPlane colorMapBuilder;
	utils::RendererImage renderer;
	utils::Image image;
	utils::WriterBMP writer;
public:
	Generator();
	void generate(string fileName);
	void set2Color(utils::Color c1, utils::Color c2);
};

#endif