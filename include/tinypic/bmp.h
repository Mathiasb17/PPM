#pragma once

#include "image.h"

#define NAMESPACE_TINYPIC_BMP_BEGIN namespace bmp{
#define NAMESPACE_TINYPIC_BMP_END }

NAMESPACE_TINYPIC_BEGIN
NAMESPACE_TINYPIC_BMP_BEGIN

template <class T>
class BMP : public Image<T>
{
public:
	BMP ();
	BMP (std::uint32_t width, std::uint32_t height);
	virtual ~BMP ();

	std::uint32_t getWidth() const;
	std::uint32_t getHeight() const;

	virtual void setPixel(const std::uint32_t x, const std::uint32_t y, const T & pixel) = 0;
	virtual void getPixel(const std::uint32_t x, const std::uint32_t y, T & pixel) const = 0;

	virtual void save(const std::string & filename, const imageFileProperties & fileProps) const = 0;

protected:
	virtual void writeHeader(std::fstream & file, const imageFileProperties & fileProps) const = 0;
	virtual void checkImageFileProperties(imageFileProperties & fileProps) const = 0;

private:
	T* m_image;
};

NAMESPACE_TINYPIC_BMP_END
NAMESPACE_TINYPIC_END
