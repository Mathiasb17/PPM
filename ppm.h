#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <string>
#include <cstdint>

namespace ppm
{

class PPM
{
public:
	PPM ();
	PPM (std::uint32_t width, std::uint32_t height);
	virtual ~PPM();

	void saveP3Format(std::string path);
	void saveP6Format(std::string path);

	void setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
	void getPixel(std::uint32_t x, std::uint32_t y, std::uint8_t &r, std::uint8_t &g, std::uint8_t &b) const;

	//tests
	void redImage();
	void greenImage();
	void blueImage();
	void horizontalLine(std::uint32_t y);
	void verticalLine(std::uint32_t x);

private:
	std::uint32_t m_width;
	std::uint32_t m_height;

	std::uint8_t* m_image;
};

} /* ppm */ 

#endif /* ifndef PPM_H */
