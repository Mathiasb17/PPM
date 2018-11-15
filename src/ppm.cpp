#include <tinypic/ppm.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

NAMESPACE_TINYPIC_BEGIN

template <class T>	
PPM<T>::PPM ():
	Image<T> ()
{
	m_image = new T[this->m_width * this->m_height];
}

template<class T>	
PPM<T>::PPM (std::uint32_t width, std::uint32_t height):
	Image<T> (width, height)
{
	m_image = new T[this->m_width * this->m_height];
}

template<class T>	
PPM<T>::~PPM()
{
	delete [] m_image;
}

template<class T>	
void PPM<T>::setPixel(const std::uint32_t x, const std::uint32_t y, const T & pixel)
{
	std::memcpy(&(m_image[this->m_width*y + x][0]), &pixel[0], sizeof(T));
}

template<class T>	
void PPM<T>::getPixel(const std::uint32_t x, const std::uint32_t y, T & pixel) const
{
	std::memcpy(&pixel[0], &(m_image[this->m_width*y + x][0]), sizeof(T));
}

template<class T>	
void PPM<T>::save(const std::string & filename, const imageFileProperties & fileProps) const
{
	checkImageFileProperties(const_cast<imageFileProperties &>(fileProps));

	switch (fileProps.at(TINYPIC_PPM_TYPE))
	{
		case TINYPIC_PPM_TYPE_ASCII:
			this->saveAscii(filename, fileProps);
			break;
		case TINYPIC_PPM_TYPE_BINARY:
			this->saveBinary(filename, fileProps);
			break;
		default:
			std::cerr << __func__ << " warning : entering default case." << std::endl;
			this->saveAscii(filename, fileProps);
	}
}

template<class T>	
void PPM<T>::writeHeader(std::fstream & file, const imageFileProperties & fileProps) const
{
	file << this->getMagicNumber(const_cast<imageFileProperties &>(fileProps)) << std::endl;
	file << this->m_width << " " << this->m_height << std::endl;
	file << this->getMaxChroma(const_cast<imageFileProperties &>(fileProps)) << std::endl;
}

template<class T>	
void PPM<T>::checkImageFileProperties(imageFileProperties & fileProps) const
{
	//check ppm type
	if(fileProps.find(TINYPIC_PPM_TYPE) == fileProps.end()) //TYPE not found, setting default
	{
		std::cout << __func__ << " warning : TINYPIC_PPM_TYPE has not been defined in file properties, setting to default " << MACRONAME(TINYPIC_PPM_TYPE_ASCII) << std::endl;
		fileProps[TINYPIC_PPM_TYPE] = TINYPIC_PPM_TYPE_ASCII;
	}
	else
	{
		//TODO check the content of TINY_PPM_TYPE
	}

	//check ppm max chroma
	if(fileProps.find(TINYPIC_PPM_MAXCHROMA) != fileProps.end())
	{
		getMaxChroma(fileProps);
	}
	else // max chroma not defined
	{
		std::cout << __func__ << " warning : TINYPIC_PPM_MAXCHROMA has not been defined in file properties, setting to default " << MACRONAME(TINYPIC_PPM_TYPE_DEFAULT) << std::endl;
		fileProps[TINYPIC_PPM_MAXCHROMA] = TINYPIC_PPM_MAXCHROMA_DEFAULT;
	}
}

template<class T>	
void PPM<T>::saveAscii(const std::string & filename, const imageFileProperties & fileProps) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out);

		writeHeader(f, fileProps);

		for (std::uint32_t i = 0; i < this->m_width * this->m_height; ++i)
		{
			for (std::uint32_t j = 0; j < sizeof(T)/sizeof(m_image[0][0]); ++j)
			{
				f << static_cast<std::int32_t>(m_image[i][j]) << " ";
			}
		}
		f.close();
	}
	catch(const std::exception & e)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

template<class T>	
void PPM<T>::saveBinary(const std::string & filename, const imageFileProperties & fileProps) const
{
	try
	{
		std::fstream f;
		f.open(filename.c_str(), std::ios_base::out | std::ios_base::binary);

		writeHeader(f, fileProps);

		for (std::uint32_t i = 0; i < this->m_width * this->m_height; ++i)
		{
			for (std::uint32_t j = 0; j < sizeof(m_image)/sizeof(m_image[0]); ++j)
			{
				f.write(reinterpret_cast<char*>(&m_image[i][j]), sizeof(std::uint8_t));
			}
		}

		f.close();
	}
	catch(const std::exception & e)
	{
		std::cerr << __func__ << " : error while saving file " << filename << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

template<class T>
const std::string PPM<T>::getMagicNumber(imageFileProperties & fileProps) const
{
	UNUSED(fileProps);
}

template<>
const std::string PPM<RGBPixel>::getMagicNumber(imageFileProperties & fileProps) const
{
	return fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P6" : "P3";
}

template<>
const std::string PPM<GrayScalePixel>::getMagicNumber(imageFileProperties & fileProps) const
{
	return fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P5" : "P2";
}

template<>
const std::string PPM<BinaryPixel>::getMagicNumber(imageFileProperties & fileProps) const
{
	return fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P4" : "P1";
}

template<class T>
const std::string PPM<T>::getMaxChroma(imageFileProperties & fileProps) const
{
	if(fileProps.at(TINYPIC_PPM_MAXCHROMA) < 0)
	{
		std::cout << __func__ << " : TINYPIC_PPM_MAXCHROMA cannot be inferior to 0, using default value " << MACRONAME(TINYPIC_PPM_MAXCHROMA_DEFAULT) << std::endl;
		fileProps[TINYPIC_PPM_MAXCHROMA] = TINYPIC_PPM_MAXCHROMA;
	}

	std::uint16_t max = std::numeric_limits<std::uint16_t>::max();
	if(fileProps.at(TINYPIC_PPM_MAXCHROMA) > max)
	{
		std::cout << __func__ << " : TINYPIC_PPM_MAXCHROMA cannot be greater than " << max << ". value will be clamped to" << max << std::endl;
		fileProps[TINYPIC_PPM_MAXCHROMA] = max;
	}

	return std::to_string(fileProps.at(TINYPIC_PPM_MAXCHROMA));
}

template<>
const std::string PPM<BinaryPixel>::getMaxChroma(imageFileProperties & fileProps) const
{
	if(fileProps.find(TINYPIC_PPM_MAXCHROMA) != fileProps.end())
	{
		std::cout << __func__ << " : TINYPIC_PPM_MAXCHROMA property will be ignored in PBM (black and white) mode." << std::endl;
	}
	return "";
}

NAMESPACE_TINYPIC_END
