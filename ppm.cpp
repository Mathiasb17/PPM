#include "ppm.h"

#include <iostream>
#include <fstream>

BEGIN_NAMESPACE_TINYPIC

PPM::PPM ():
	Image()
{

}

PPM::PPM (std::uint32_t width, std::uint32_t height):
	Image(width, height)
{

}

PPM::~PPM()
{

}

void PPM::saveP3Format(const std::string filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out);

		f << "P3" << std::endl;
		f << m_width<< " " << m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
		{
			f << static_cast<std::int32_t>(m_image[i]) << " ";
		}
		f.close();
	}
	catch(std::ios_base::failure)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
	}
}

void PPM::saveP6Format(const std::string filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out | std::ios_base::binary);

		f << "P6" << std::endl;
		f << m_width<< " " << m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
		{
			f.write(reinterpret_cast<char*>(&m_image[i]), sizeof(uint8_t));
		}

		f.close();
	}
	catch(std::ios_base::failure)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
	}
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

void PPM::save(const std::string filename, const imageFileProperties fileProps) const
{
	switch (fileProps.at(TINYPIC_PPMTYPE))
	{
		case P3:
			this->saveP3Format(filename);
			break;
		case P6:
			this->saveP6Format(filename);
			break;
		default:
			std::cerr << __func__ << " warning : entering default case." << std::endl;
			this->saveP3Format(filename);
	}
}

END_NAMESPACE_TINYPIC
