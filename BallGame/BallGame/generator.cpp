#include "generator.h"
#include <cmath>
#include <time.h>

Generator::Generator() {
	srand(time(0));
	perlin.SetOctaveCount(6);
	perlin.SetFrequency(2);
	colorMapBuilder.SetSourceModule(perlin);
	colorMapBuilder.SetDestNoiseMap(colorMap);
	colorMapBuilder.SetDestSize(256, 256);
	renderer.SetSourceNoiseMap(colorMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(186, 85, 211, 255));
	renderer.AddGradientPoint(1.0000, utils::Color(148, 0, 211, 255));
	//renderer.EnableLight();
	//renderer.SetLightContrast(3.0); // Triple the contrast
	//renderer.SetLightBrightness(2.0); // Double the brightness
}

void Generator::generate(string fileName) {
	int x = rand() % 1024;
	int y = rand() % 1024;
	colorMapBuilder.SetBounds(x, x + 4, y, y + 4);
	colorMapBuilder.Build();
	renderer.Render();
	writer.SetSourceImage(image);
	writer.SetDestFilename(fileName.c_str());
	writer.WriteDestFile();
}

void Generator::set2Color(utils::Color c1, utils::Color c2) {
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, c1);
	renderer.AddGradientPoint(1.0000, c2);
}
