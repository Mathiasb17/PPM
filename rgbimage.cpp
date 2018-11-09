#include "rgbimage.h"

NAMESPACE_TINYPIC_BEGIN

RGBImage::RGBImage() :
	Image()
{

}

RGBImage::RGBImage(std::uint32_t width, std::uint32_t height) :
	Image(width, height)
{

}

RGBImage::~RGBImage()
{

}

void RGBImage::horizontalLine(std::uint32_t y, const RGBPixel & pixel)
{
	Image::horizontalLine(y, pixel);
}

void RGBImage::verticalLine(std::uint32_t x, const RGBPixel & pixel)
{
	Image::verticalLine(x, pixel);
}

void RGBImage::redImage()
{
	for (std::uint32_t i = 0; i < m_width; ++i)
	{
		for (std::uint32_t j = 0; j < m_height; ++j)
		{
			this->setPixel(i, j, {255, 0, 0});
		}
	}	
}

void RGBImage::greenImage()
{
	for (std::uint32_t i = 0; i < m_width; ++i)
	{
		for (std::uint32_t j = 0; j < m_height; ++j)
		{
			this->setPixel(i, j, {0, 255, 0});
		}
	}	
}

void RGBImage::blueImage()
{
	for (std::uint32_t i = 0; i < m_width; ++i)
	{
		for (std::uint32_t j = 0; j < m_height; ++j)
		{
			this->setPixel(i, j, {0, 0, 255});
		}
	}	
}

NAMESPACE_TINYPIC_END
