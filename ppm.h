#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <string>
#include <cstdint>

namespace ppm
{

typedef unsigned int uint;

class PPM
{
public:
	PPM ();
	PPM (uint width, uint height);
	virtual ~PPM();

	void saveP3Format(std::string path);
	void saveP6Format(std::string path);

	void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void getPixel(int x, int y, uint8_t &r, uint8_t &g, uint8_t &b) const;

	//tests
	void redImage();
	void greenImage();
	void blueImage();
	void horizontalLine(uint y);
	void verticalLine(uint x);

private:
	uint m_width;
	uint m_height;

	uint8_t* m_image;
};

} /* ppm */ 

#endif /* ifndef PPM_H */
