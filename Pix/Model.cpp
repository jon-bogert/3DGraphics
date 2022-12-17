#include "Model.h"
#include "MathHelper.h"
#include <iostream>

void Model::Load(const std::string& fileName)
{
	mFileName = fileName;
	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<uint32_t> normalsCount;
	std::vector<uint32_t> positionsIndecies;

	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(), "r");
	if (!file)
	{
		std::cout << "ERR: Cannot open model file at: " << fileName << std::endl;
		fclose(file);
		return;
	}

	while(true)
	{
		char buffer[128];
		int result = fscanf_s(file, "%s", buffer, (uint32_t)std::size(buffer));
		if (result == EOF)
			break;

		if (strcmp(buffer, "v") == 0)
		{
			float x{}, y{}, z{};
			fscanf_s(file, "%f %f %f\n", &x, &y, &z);
			positions.push_back({ x, y, z });
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[3];
			if (fscanf_s(file, "%d//%*d %d//%*d %d//%*d\n", &v[0], &v[1], &v[2]) != 3)
			{
				std::cout << "Unexpected format for file: " << fileName << std::endl;
				fclose(file);
				return;
			}

			positionsIndecies.push_back(v[0]);
			positionsIndecies.push_back(v[1]);
			positionsIndecies.push_back(v[2]);
		}
	}
	mVertecies.resize(positionsIndecies.size());
	normals.resize(positionsIndecies.size());
	normalsCount.resize(positionsIndecies.size());
	for (size_t i = 2; i < positionsIndecies.size(); i += 3)
	{
		uint32_t index0 = positionsIndecies[i - 2] - 1;
		uint32_t index1 = positionsIndecies[i - 1] - 1;
		uint32_t index2 = positionsIndecies[i] - 1;
		Vector3 pos0 = positions[index0];
		Vector3 pos1 = positions[index1];
		Vector3 pos2 = positions[index2];
		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((pos1 - pos0), (pos2 - pos0)));
		normals[index0] = normals[index0] + faceNorm;
		normals[index1] = normals[index1] + faceNorm;
		normals[index2] = normals[index2] + faceNorm;
		++normalsCount[index0];
		++normalsCount[index1];
		++normalsCount[index2];
	}
	for (size_t i = 0; i < normals.size(); ++i)
	{
		if (normalsCount[i] > 0)
		{
			normals[i] = MathHelper::Normalize((normals[i] / (float)normalsCount[i]));
		}
		else
		{
			normals[i] = Vector3(0, 0, 1);
		}
	}
	for (size_t i = 0; i < positionsIndecies.size(); ++i)
	{
		mVertecies[i].position = positions[positionsIndecies[i] - 1];
		mVertecies[i].normal = normals[positionsIndecies[i] - 1];
		mVertecies[i].color = X::Colors::White;
	}
	fclose(file);
}

const std::string& Model::GetFileName() const
{
	return mFileName;
}

const Vertex& Model::GetVertex(int index) const
{
	return mVertecies[index];
}

int Model::GetVertexCount() const
{
	return static_cast<int>(mVertecies.size());
}
