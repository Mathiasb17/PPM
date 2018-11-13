#pragma once

#include <string>
#include <map>
#include <fstream>

#include  "common.h"

#define NAMESPACE_TINYPIC_BEGIN namespace tinypic {
#define NAMESPACE_TINYPIC_END }

NAMESPACE_TINYPIC_BEGIN

typedef std::map<std::uint32_t, std::uint8_t> imageFileProperties;
typedef std::array<std::uint16_t, 3> RGBPixel;
typedef std::array<std::uint16_t, 1> GrayScalePixel;

typedef std::array<bool, 1> BinaryPixel;

template <class T>
class Image
{
public:
	Image ();
	Image (std::uint32_t width, std::uint32_t height);
	virtual ~Image ();

	std::uint32_t getWidth() const;
	std::uint32_t getHeight() const;

	virtual void setPixel(const std::uint32_t x, const std::uint32_t y, const T & pixel) = 0;
	virtual void getPixel(const std::uint32_t x, const std::uint32_t y, T & pixel) const = 0;

	virtual void save(const std::string & filename, imageFileProperties & fileProps) const = 0;

protected:
	virtual void writeHeader(std::fstream & file, const imageFileProperties & fileProps) const = 0;
	virtual void checkImageFileProperties(imageFileProperties & fileProps) const = 0;

protected:
	std::uint32_t m_width;
	std::uint32_t m_height;
};

//forward declaration of image base class
template class Image<RGBPixel>;
template class Image<GrayScalePixel>;
template class Image<BinaryPixel>;
 
NAMESPACE_TINYPIC_END
