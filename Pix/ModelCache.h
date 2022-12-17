#pragma once
#include "Model.h"

class ModelCache
{
	std::vector <std::shared_ptr<Model>> mModels;

public:
	static ModelCache* Get();
private:
	ModelCache() {}

public:
	~ModelCache() {}

	void Clear();
	const Model* GetModel(const std::string& fileName);
};

