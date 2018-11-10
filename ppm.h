#pragma once

#include "image.h"

NAMESPACE_TINYPIC_BEGIN

#define TINYPIC_PPMTYPE "PpmType"

enum enumPpmType
{
	ASCII = 0,
	BINARY
};

template <class T, class U>	
class PPM : public Image<T, U>
{
public:
	PPM ();
	PPM (std::uint32_t width, std::uint32_t height);
	virtual ~PPM ();

	void setPixel(std::uint32_t x, std::uint32_t y, const T & pixel) final;
	void getPixel(std::uint32_t x, std::uint32_t y, T & pixel) const final;

	void save(const std::string & filename, const imageFileProperties & fileProps) const final;

private:
	void saveAscii(const std::string & filename) const;
	void saveBinary(const std::string & filename) const;

private:
	U* m_image;
};

//forward declaration of specific Image base classes
template class PPM<RGBPixel, std::uint8_t>;
template class PPM<GrayScalePixel, std::uint16_t>;
template class PPM<BinaryPixel, BlackOrWhite>;

NAMESPACE_TINYPIC_END
