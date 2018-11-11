#pragma once

#include "image.h"

#define TINYPIC_PPM_TYPE 0
#define TINYPIC_PPM_MAXCHROMA 1

#define TINYPIC_PPM_TYPE_BINARY 0
#define TINYPIC_PPM_TYPE_ASCII 1

#define TINYPIC_PPM_TYPE_DEFAULT ASCII
#define TINYPIC_PPM_MAXCHROMA_GRAYSCALE_DEFAULT 255
#define TINYPIC_PPM_MAXCHROMA_RGB_DEFAULT 255

NAMESPACE_TINYPIC_BEGIN

template <class T>	
class PPM : public Image<T>
{
public:
	PPM ();
	PPM (std::uint32_t width, std::uint32_t height);
	virtual ~PPM ();

	void setPixel(const std::uint32_t x, const std::uint32_t y, const T & pixel) final;
	void getPixel(const std::uint32_t x, const std::uint32_t y, T & pixel) const final;

	void save(const std::string & filename, imageFileProperties & fileProps) const final;

protected:
	virtual void writeHeader(std::fstream & file, const imageFileProperties & fileProps) const final;
	virtual void checkImageFileProperties(imageFileProperties & fileProps) const final;

private:
	void saveAscii(const std::string & filename, const imageFileProperties & fileProps) const;
	void saveBinary(const std::string & filename, const imageFileProperties & fileProps) const;

	const std::string getMagicNumber(const imageFileProperties & fileProps) const;
	const std::string getMaxChroma(const imageFileProperties & fileProps) const;

private:
	T* m_image;
};

//forward declaration of specific Image base classes
template class PPM<RGBPixel>;
template class PPM<GrayScalePixel>;
template class PPM<BinaryPixel>;

NAMESPACE_TINYPIC_END
