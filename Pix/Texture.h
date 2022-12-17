#pragma once

#include <XEngine.h>

enum class AddressMode : int
{
	Clamp,
	Wrap
};

class Texture // only load 24 bit bmp's
{
	std::string mFileName;
	std::unique_ptr<X::Color[]> mPixels;
	int mWidth = 0;
	int mHeight = 0;

public:
	void Load(const std::string& path);
	const std::string& GetFileName() const;
	X::Color GetPixel(float u, float v, AddressMode mode) const;
};