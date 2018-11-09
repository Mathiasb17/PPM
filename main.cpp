#include "ppm.h"

#include <iostream>

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	std::cout << "begin test" << std::endl;

	tinypic::imageFileProperties fileProps;
	fileProps[TINYPIC_PPMTYPE] = tinypic::P3;

	tinypic::PPM p;
	p.redImage();
	p.horizontalLine(100, {0, 255, 0});
	p.verticalLine(200, {0, 255, 0});
	p.save("p3.ppm", fileProps);

	std::cout << "end test" << std::endl;

	return 0;
}
