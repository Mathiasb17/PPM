#include <tinypic/bmp.h>

NAMESPACE_TINYPIC_BEGIN
NAMESPACE_TINYPIC_BMP_BEGIN

template<class T>
BMP<T>::BMP () :
	Image<T>()
{
	m_image = new T[this->m_width * this->m_height];
}

template <class T>
BMP<T>::BMP (std::uint32_t width, std::uint32_t height) :
	Image<T>(width, height)
{
	m_image = new T[this->m_width * this->m_height];
}

template <class T>
BMP<T>::~BMP ()
{
}

template <class T>
std::uint32_t BMP<T>::getWidth() const
{
	return this->m_width;
}

template <class T>
std::uint32_t BMP<T>::getHeight() const
{
	return this->m_height;
}

template <class T>
void BMP<T>::setPixel(const std::uint32_t x, const std::uint32_t y, const T & pixel)
{
	UNUSED(x);
	UNUSED(y);
	UNUSED(pixel);
}

template <class T>
void BMP<T>::getPixel(const std::uint32_t x, const std::uint32_t y, T & pixel) const
{
	UNUSED(x);
	UNUSED(y);
	UNUSED(pixel);
}

template <class T>
void BMP<T>::save(const std::string & filename, const imageFileProperties & fileProps) const
{

}

template <class T>
void BMP<T>::writeHeader(std::fstream & file, const imageFileProperties & fileProps) const
{

}

template <class T>
void BMP<T>::checkImageFileProperties(imageFileProperties & fileProps) const
{

}

NAMESPACE_TINYPIC_BMP_END
NAMESPACE_TINYPIC_END
