#include "ppm.h"

#include <iostream>

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	std::cout << "begin test" << std::endl;

	tinypic::imageFileProperties fileProps;
	fileProps[TINYPIC_PPMTYPE] = tinypic::BINARY;
	tinypic::PPM<tinypic::RGBPixel, std::uint8_t> p;

	for(std::uint32_t i = 0; i < p.getWidth(); ++i)
	{
		for(std::uint32_t j = 0; j < p.getHeight(); ++j)
		{
			p.setPixel(i, j, {0, 255, 0});
		}
	}

	p.save("p3.ppm", fileProps);

	std::cout << "end test" << std::endl;

	return 0;
}
