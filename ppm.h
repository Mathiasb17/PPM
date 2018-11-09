#pragma once

#include "image.h"

BEGIN_NAMESPACE_TINYPIC

#define TINYPIC_PPMTYPE "PpmType"

enum enumPpmType
{
	P3 = 0,
	P6
};

class PPM : public Image
{
public:
	PPM ();
	PPM (std::uint32_t width, std::uint32_t height);
	virtual ~PPM ();

	void setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) final;
	void getPixel(std::uint32_t x, std::uint32_t y, std::uint8_t &r, std::uint8_t &g, std::uint8_t &b) const final;

	void save(const std::string filename, const imageFileProperties fileProps) const final;

private:
	void saveP3Format(std::string filename) const;
	void saveP6Format(std::string filename) const;
};

END_NAMESPACE_TINYPIC
