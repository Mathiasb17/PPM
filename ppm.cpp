#include "ppm.h"

#include <iostream>
#include <fstream>

NAMESPACE_TINYPIC_BEGIN

template <class T, class U>	
PPM<T, U>::PPM ():
	Image<T, U> ()
{
	m_image = new U[this->m_width * this->m_height * sizeof(T)/sizeof(U)];
}

template<class T, class U>	
PPM<T, U>::PPM (std::uint32_t width, std::uint32_t height):
	Image<T, U> (width, height)
{
	m_image = new U[this->m_width * this->m_height * sizeof(T)/sizeof(U)];
}

template<class T, class U>	
PPM<T, U>::~PPM()
{
	delete [] m_image;
}

template<class T, class U>	
void PPM<T, U>::setPixel(std::uint32_t x, std::uint32_t y, const T & pixel)
{
	std::uint16_t nbPixelComponents = std::tuple_size<T>::value;
	for(std::uint16_t i = 0; i < nbPixelComponents; ++i)
	{
		m_image[this->m_width*y*nbPixelComponents + x*nbPixelComponents+i] = pixel[i];
	}
}

template<class T, class U>	
void PPM<T, U>::getPixel(std::uint32_t x, std::uint32_t y, T & pixel) const
{
	std::uint16_t nbPixelComponents = std::tuple_size<T>::value;
	for(std::uint16_t i = 0; i < nbPixelComponents; ++i)
	{
		pixel[i] = m_image[this->m_width*y*nbPixelComponents + x*nbPixelComponents+i];
	}
}

template<class T, class U>	
void PPM<T, U>::save(const std::string & filename, const imageFileProperties & fileProps) const
{
	switch (fileProps.at(TINYPIC_PPMTYPE))
	{
		case ASCII:
			this->saveAscii(filename);
			break;
		case BINARY:
			this->saveBinary(filename);
			break;
		default:
			std::cerr << __func__ << " warning : entering default case." << std::endl;
			this->saveAscii(filename);
	}
}

template<class T, class U>	
void PPM<T, U>::saveAscii(const std::string & filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out);

		f << "P3" << std::endl;
		f << this->m_width << " " << this->m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < this->m_width * this->m_height * 3; ++i)
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

template<class T, class U>	
void PPM<T, U>::saveBinary(const std::string & filename) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out | std::ios_base::binary);

		f << "P6" << std::endl;
		f << this->m_width << " " << this->m_height << std::endl;
		f << "255" << std::endl;

		for (std::uint32_t i = 0; i < this->m_width * this->m_height * 3; ++i)
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
