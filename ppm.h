#pragma once

#include "rgbimage.h"

NAMESPACE_TINYPIC_BEGIN

#define TINYPIC_PPMTYPE "PpmType"

enum enumPpmType
{
	P3 = 0,
	P6
};

enum PBMPixel
{
	BLACK = 0,
	WHITE = 1
};

//forward declaration of specific Image base classes
template class Image<RGBPixel>;
template class Image<PBMPixel>;

class PPM : public RGBImage
{
public:
	PPM ();
	PPM (std::uint32_t width, std::uint32_t height);
	virtual ~PPM ();

	void setPixel(std::uint32_t x, std::uint32_t y, const RGBPixel & rgb) final;
	void getPixel(std::uint32_t x, std::uint32_t y, RGBPixel & rgb) const final;

	void save(const std::string & filename, const imageFileProperties & fileProps) const final;

private:
	void saveP3Format(const std::string & filename) const;
	void saveP6Format(const std::string & filename) const;

private:
	std::uint8_t* m_image;
};

NAMESPACE_TINYPIC_END
