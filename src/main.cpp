#include <tinypic/ppm.h>

#include <iostream>
#include <limits>

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	std::cout << "begin test" << std::endl;

	tinypic::imageFileProperties fileProps;
	fileProps[TINYPIC_PPM_TYPE] = TINYPIC_PPM_TYPE_ASCII;
	fileProps[TINYPIC_PPM_MAXCHROMA] = TINYPIC_PPM_MAXCHROMA_RGB_DEFAULT;

	tinypic::PPM<tinypic::RGBPixel> p;

	for(std::uint32_t i = 0; i < p.getWidth(); ++i)
	{
		for(std::uint32_t j = 0; j < p.getHeight(); ++j)
		{
			p.setPixel(i, j, {0, 255, 0});
		}
	}

	for(std::uint32_t i = 0; i < p.getWidth(); ++i)
	{
		p.setPixel(i, 150, {0, 0, 0});
	}

	for(std::uint32_t i = 0; i < p.getHeight(); ++i)
	{
		p.setPixel(150, i, {0, 0, 0});
	}

	p.save("p3.ppm", fileProps);

	std::cout << "end test" << std::endl;

	return 0;
}
