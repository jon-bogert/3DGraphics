#pragma once
#include <vector>;
#include "Matrix4.h"

class MatrixStack
{
	std::vector<Matrix4> mMatrices;
	Matrix4 mCombinedTransfrom;

public:
	static MatrixStack* Get();

private:
	MatrixStack() {}

public:
	void OnNewFrame();
	void PushTranslation(const Vector3 d);
	void PushRotationX(const float rad);
	void PushRotationY(const float rad);
	void PushRotationZ(const float rad);
	void PushScaling(const Vector3 s);
	void PopMatrix();

	Matrix4 GetTransform() const { return mCombinedTransfrom; }

private:
	void GenerateCombinedMatrix();
};

