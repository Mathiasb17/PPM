#pragma once

#include <string>
#include <map>

#define NAMESPACE_TINYPIC_BEGIN namespace tinypic {
#define NAMESPACE_TINYPIC_END }

NAMESPACE_TINYPIC_BEGIN

typedef std::map<std::basic_string<char>, std::uint8_t> imageFileProperties;
typedef std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> RGBPixel;

template <class T>
class Image
{
public:
	Image ();
	Image (std::uint32_t width, std::uint32_t height);
	virtual ~Image ();

	virtual void setPixel(std::uint32_t x, std::uint32_t y, const T & pixel) = 0;
	virtual void getPixel(std::uint32_t x, std::uint32_t y, T & pixel) const = 0;

	virtual void save(const std::string & filename, const imageFileProperties & fileProps) const = 0;

	void horizontalLine(std::uint32_t y, const T & pixel);
	void verticalLine(std::uint32_t x, const T & pixel);

protected:
	std::uint32_t m_width;
	std::uint32_t m_height;
};

NAMESPACE_TINYPIC_END
