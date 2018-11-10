#pragma once

#include <string>
#include <map>

#define NAMESPACE_TINYPIC_BEGIN namespace tinypic {
#define NAMESPACE_TINYPIC_END }

NAMESPACE_TINYPIC_BEGIN

typedef std::map<std::basic_string<char>, std::uint8_t> imageFileProperties;
typedef std::array<std::uint8_t, 3> RGBPixel;
typedef std::array<std::int16_t, 1> GrayScalePixel;

enum BlackOrWhite
{
	BLACK = 0,
	WHITE = 1
};
typedef std::array<BlackOrWhite, 1> BinaryPixel;

template <class T, class U>
class Image
{
public:
	Image ();
	Image (std::uint32_t width, std::uint32_t height);
	virtual ~Image ();

	std::uint32_t getWidth() const;
	std::uint32_t getHeight() const;

	virtual void setPixel(std::uint32_t x, std::uint32_t y, const T & pixel) = 0;
	virtual void getPixel(std::uint32_t x, std::uint32_t y, T & pixel) const = 0;

	virtual void save(const std::string & filename, const imageFileProperties & fileProps) const = 0;

	void horizontalLine(std::uint32_t y, const T & pixel);
	void verticalLine(std::uint32_t x, const T & pixel);

protected:
	std::uint32_t m_width;
	std::uint32_t m_height;
};

//forward declaration of image base class
template class Image<RGBPixel, std::uint8_t>;
template class Image<GrayScalePixel, std::uint16_t>;
template class Image<BinaryPixel, BlackOrWhite>;

NAMESPACE_TINYPIC_END
