#include "ModelCache.h"

ModelCache* ModelCache::Get()
{
    static ModelCache instance;
    return &instance;
}

void ModelCache::Clear()
{
    mModels.clear();
}

const Model* ModelCache::GetModel(const std::string& fileName)
{
    auto iter = std::find_if(mModels.begin(), mModels.end(), [fileName](auto& model) {return model->GetFileName() == fileName; });

    //Model was found
    if (iter != mModels.end())
        return iter->get();

    // Go get model if not found
    auto& model = mModels.emplace_back(std::make_shared<Model>());
    model->Load(fileName);

    return model.get();
}
