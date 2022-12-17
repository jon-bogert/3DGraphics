#pragma once
#include "Texture.h"

class TextureCache
{
	std::vector<std::shared_ptr<Texture>> mTextures;
	const Texture* mCurrentTexture = nullptr;
	AddressMode mAddressMode = AddressMode::Clamp;

public:
	static TextureCache* Get();

private:
	TextureCache() {}

public:
	void Clear();
	void SetTexture(const std::string& fileName);
	void SetAddressMode(AddressMode mode);

	X::Color SampleColor(X::Color uv) const;

};

