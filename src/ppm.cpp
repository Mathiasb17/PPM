#include <tinypic/ppm.h>

#include <iostream>
#include <fstream>
#include <cstring>

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
void PPM<T>::save(const std::string & filename, imageFileProperties & fileProps) const
{
	checkImageFileProperties(fileProps);

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
	file << this->getMagicNumber(fileProps) << std::endl;
	file << this->m_width << " " << this->m_height << std::endl;
	file << this->getMaxChroma(fileProps) << std::endl;
}

template<class T>	
void PPM<T>::checkImageFileProperties(imageFileProperties & fileProps) const
{
	if(fileProps.find(TINYPIC_PPM_TYPE) == fileProps.end()) //TYPE not found, setting default
	{
		std::cout << __func__ << " warning : TINYPIC_PPM_TYPE has not been defined in file properties, setting to default" << MACRONAME(TINYPIC_PPM_TYPE_ASCII) << std::endl;
		fileProps.insert(std::make_pair(TINYPIC_PPM_TYPE, TINYPIC_PPM_TYPE_ASCII));
	}
	if(fileProps.find(TINYPIC_PPM_MAXCHROMA) == fileProps.end())
	{
		if(std::is_same<T, RGBPixel>())
		{
			std::cout << __func__ << " warning : TINYPIC_PPM_MAXCHROMA has not been defined in file properties, setting to default" << MACRONAME(TINYPIC_PPM_MAXCHROMA_RGB_DEFAULT) << std::endl;
			fileProps.insert(std::make_pair(TINYPIC_PPM_MAXCHROMA, TINYPIC_PPM_MAXCHROMA_RGB_DEFAULT));
		}
		else if(std::is_same<T, GrayScalePixel>())
		{
			std::cout << __func__ << " warning : TINYPIC_PPM_MAXCHROMA has not been defined in file properties, setting to default" << MACRONAME(TINYPIC_PPM_MAXCHROMA_GRAYSCALE_DEFAULT) << std::endl;
			fileProps.insert(std::make_pair(TINYPIC_PPM_MAXCHROMA, TINYPIC_PPM_MAXCHROMA_GRAYSCALE_DEFAULT));
		}
		else //binary pixel
		{
			//do nothing !
		}
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
const std::string PPM<T>::getMagicNumber(const imageFileProperties & fileProps) const
{
	std::string res;

	if(std::is_same<T, RGBPixel>())
	{
		res = fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P6" : "P3";
	}
	else if(std::is_same<T, GrayScalePixel>())
	{
		res = fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P5" : "P2";
	}
	else //binary pixel
	{
		res = fileProps.at(TINYPIC_PPM_TYPE) == TINYPIC_PPM_TYPE_BINARY ? "P4" : "P1";
	}

	return res;
}

template<class T>
const std::string PPM<T>::getMaxChroma(const imageFileProperties & fileProps) const
{
	if(std::is_same<T, BinaryPixel>()) // no max chroma in black and white images
	{
		if(fileProps.find(TINYPIC_PPM_MAXCHROMA) != fileProps.end())
		{
			std::cout << __func__ << " : TINYPIC_PPM_MAXCHROMA property will be ignored in PBM (black and white) mode." << std::endl;
		}
		return "";
	}
	else
	{
		return std::to_string(fileProps.at(TINYPIC_PPM_MAXCHROMA));
	}
}

NAMESPACE_TINYPIC_END
