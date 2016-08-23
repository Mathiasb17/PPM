#include "ppm.h"

#include <fstream>

namespace ppm
{

PPM::PPM ():
	m_width(640),
	m_height(480)
{
	m_image = new uint8_t[m_width*m_height*3];
}

PPM::PPM (uint width, uint height):
	m_width(width),
	m_height(height)
{
	m_image = new uint8_t[m_width*m_height*3];
}

PPM::~PPM()
{
	delete [] m_image;
}

void PPM::saveP3Format(std::string path)
{
	std::fstream f;
	f.open(path.c_str(), std::ios_base::out);

	f << "P3" << std::endl;
	f << m_width<< " " << m_height << std::endl;
	f << "255" << std::endl;

	for (uint i = 0; i < m_width * m_height * 3; ++i)
	{
		f << (int)m_image[i] << " ";
	}

	f.close();
}


void PPM::saveP6Format(std::string path)
{
	std::fstream f;
	f.open(path.c_str(), std::ios_base::out);

	f << "P6" << std::endl;
	f << m_width<< " " << m_height << std::endl;
	f << "255" << std::endl;

	for (uint i = 0; i < m_width * m_height * 3; ++i)
	{
		f.write((char*)&m_image[i], sizeof(uint8_t));
	}

	f.close();
}

void PPM::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	m_image[m_width*y*3 + x*3] = r;
	m_image[m_width*y*3 + x*3+1] = g;
	m_image[m_width*y*3 + x*3+2] = b;
}

void PPM::getPixel(int x, int y, uint8_t &r, uint8_t &g, uint8_t &b) const
{
	r = m_image[m_width*y*3 + x*3];
	g = m_image[m_width*y*3 + x*3+1];
	b = m_image[m_width*y*3 + x*3+2];
}

void PPM::redImage()
{
	for (uint i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 0) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::greenImage()
{
	for (uint i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 1) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::blueImage()
{
	for (uint i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 2) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::horizontalLine(uint y)
{
	for (uint i = 0; i < m_width; ++i)
	{
		for (uint j = 0; j < m_height; ++j)
		{
			if (j == y)
				setPixel(i, j, 255, 255, 255);
		}
	}
}

void PPM::verticalLine(uint x)
{
	for (uint i = 0; i < m_width; ++i)
	{
		for (uint j = 0; j < m_height; ++j)
		{
			if (i == x)
				setPixel(i, j, 255, 255, 255);
		}
	}
}
	
} /* ppm */ 
