#include "image.h"

NAMESPACE_TINYPIC_BEGIN

template <class T, class U>
Image<T, U>::Image() :
	m_width(640U),
	m_height(480U)
{

}

template <class T, class U>
Image<T, U>::Image(std::uint32_t width, std::uint32_t height) :
	m_width(width),
	m_height(height)
{

}

template <class T, class U>
Image<T, U>::~Image()
{

}

template <class T, class U>
std::uint32_t Image<T, U>::getWidth() const
{
	return m_width;
}

template <class T, class U>
std::uint32_t Image<T, U>::getHeight() const
{
	return m_height;
}

template <class T, class U>
void Image<T, U>::horizontalLine(std::uint32_t y, const T & pixel)
{
	for (std::uint32_t i = 0; i < m_width; ++i)
	{
		setPixel(i, y, pixel);
	}
}

template <class T, class U>
void Image<T, U>::verticalLine(std::uint32_t x, const T & pixel)
{
	for (std::uint32_t i = 0; i < m_height; ++i)
	{
		setPixel(x, i, pixel);
	}
}

NAMESPACE_TINYPIC_END
