#include "CmdModel.h"
#include "ModelCache.h"
#include "PrimativeManager.h"

bool CmdModel::Execute(const std::vector<std::string>& params)
{
    if (params.size() <= 0)
        return false;

    auto model = ModelCache::Get()->GetModel(params[0]);
    auto pm = PrimativeManager::Get();

    for (int i = 0; i < model->GetVertexCount(); ++i)
    {
        pm->AddVertex(model->GetVertex(i));
    }

    return true;
}
