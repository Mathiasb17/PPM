#include <tinypic/image.h>

NAMESPACE_TINYPIC_BEGIN

template <class T>
Image<T>::Image() :
	m_width(640U),
	m_height(480U)
{

}

template <class T>
Image<T>::Image(std::uint32_t width, std::uint32_t height) :
	m_width(width),
	m_height(height)
{

}

template <class T>
Image<T>::~Image()
{

}

template <class T>
std::uint32_t Image<T>::getWidth() const
{
	return m_width;
}

template <class T>
std::uint32_t Image<T>::getHeight() const
{
	return m_height;
}

NAMESPACE_TINYPIC_END
