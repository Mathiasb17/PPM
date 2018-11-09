#include "ppm.h"

#include <iostream>
#include <fstream>

NAMESPACE_TINYPIC_BEGIN

PPM::PPM ():
	RGBImage ()
{
	m_image = new std::uint8_t[m_width*m_height*3];
}

PPM::PPM (std::uint32_t width, std::uint32_t height):
	RGBImage (width, height)
{
	m_image = new std::uint8_t[m_width*m_height*3];
}

PPM::~PPM()
{
	delete [] m_image;
}

void PPM::setPixel(std::uint32_t x, std::uint32_t y, const RGBPixel & rgb)
{
	m_image[m_width*y*3 + x*3] = std::get<0>(rgb);
	m_image[m_width*y*3 + x*3+1] = std::get<1>(rgb);
	m_image[m_width*y*3 + x*3+2] = std::get<2>(rgb);
}

void PPM::getPixel(std::uint32_t x, std::uint32_t y, RGBPixel & rgb) const
{
	std::get<0>(rgb) = m_image[m_width*y*3 + x*3];
	std::get<1>(rgb) = m_image[m_width*y*3 + x*3+1];
	std::get<2>(rgb) = m_image[m_width*y*3 + x*3+2];
}

void PPM::save(const std::string & filename, const imageFileProperties & fileProps) const
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

void PPM::saveP3Format(const std::string & filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out);

		f << "P3" << std::endl;
		f << m_width << " " << m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
		{
			f << static_cast<std::int32_t>(m_image[i]) << " ";
		}
		f.close();
	}
	catch(const std::exception & e)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void PPM::saveP6Format(const std::string & filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out | std::ios_base::binary);

		f << "P6" << std::endl;
		f << m_width << " " << m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < m_width * m_height * 3; ++i)
		{
			f.write(reinterpret_cast<char*>(&m_image[i]), sizeof(std::uint8_t));
		}

		f.close();
	}
	catch(const std::exception & e)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

NAMESPACE_TINYPIC_END
