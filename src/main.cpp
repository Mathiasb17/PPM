#include <tinypic/ppm.h>

#include <iostream>
#include <limits>

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	std::cout << "begin test" << std::endl;

	tinypic::imageFileProperties fileProps;
	fileProps[TINYPIC_PPM_TYPE] = 72U;

	tinypic::ppm::PPM<tinypic::GrayScalePixel> p;

	for(std::uint32_t i = 0; i < p.getWidth(); ++i)
	{
		for(std::uint32_t j = 0; j < p.getHeight(); ++j)
		{
			p.setPixel(i, j, {200});
		}
	}

	for(std::uint32_t i = 0; i < p.getWidth(); ++i)
	{
		p.setPixel(i, 150, {100});
	}

	for(std::uint32_t i = 0; i < p.getHeight(); ++i)
	{
		p.setPixel(150, i, {50});
	}

	p.save("p3.ppm", fileProps);

	std::cout << "end test" << std::endl;

	return 0;
}
