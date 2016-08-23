#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <string>

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

private:
	int m_width;
	int m_height;

	uint8_t* m_image;
};

} /* ppm */ 

#endif /* ifndef PPM_H */
