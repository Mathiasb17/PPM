#include "ppm.h"

#include <fstream>

namespace ppm
{

PPM::PPM ():
	m_width(640U),
	m_height(480U)
{
	m_image = new std::uint8_t[m_width*m_height*3];
}

PPM::PPM (std::uint32_t width, std::uint32_t height):
	m_width(width),
	m_height(height)
{
	m_image = new std::uint8_t[m_width*m_height*3];
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

	for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
	{
		f << (std::int32_t)m_image[i] << " ";
	}

	f.close();
}


void PPM::saveP6Format(std::string path)
{
	std::fstream f;
	f.open(path.c_str(), std::ios_base::out | std::ios_base::binary);

	f << "P6" << std::endl;
	f << m_width<< " " << m_height << std::endl;
	f << "255" << std::endl;

	for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
	{
		f.write((char*)&m_image[i], sizeof(uint8_t));
	}

	f.close();
}

void PPM::setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	m_image[m_width*y*3 + x*3] = r;
	m_image[m_width*y*3 + x*3+1] = g;
	m_image[m_width*y*3 + x*3+2] = b;
}

void PPM::getPixel(std::uint32_t x, std::uint32_t y, std::uint8_t &r, std::uint8_t &g, std::uint8_t &b) const
{
	r = m_image[m_width*y*3 + x*3];
	g = m_image[m_width*y*3 + x*3+1];
	b = m_image[m_width*y*3 + x*3+2];
}

void PPM::redImage()
{
	for (std::uint32_t i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 0) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::greenImage()
{
	for (std::uint32_t i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 1) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::blueImage()
{
	for (std::uint32_t i = 0; i < m_width*m_height*3; ++i)
	{
		if (i%3 == 2) 
			m_image[i] = 255;
		else
			m_image[i] = 0;
	}	
}

void PPM::horizontalLine(std::uint32_t y)
{
	for (std::uint32_t i = 0; i < m_width; ++i)
	{
		setPixel(i, y, 255, 255, 255);
	}
}

void PPM::verticalLine(std::uint32_t x)
{
	for (std::uint32_t i = 0; i < m_height; ++i)
	{
		setPixel(x, i, 255, 255, 255);
	}
}

} /* ppm */ 
