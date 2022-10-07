#include "MatrixStack.h"

#include "Clipper.h"
#include "Rasterizer.h"

MatrixStack* MatrixStack::Get()
{
	static MatrixStack sInstance;
	return &sInstance;
}

void MatrixStack::OnNewFrame()
{
	mMatrices.clear();
	mTransform = Matrix4::Identity();
}

void MatrixStack::PushTranslation(Vector3 d)
{
	auto matrix = Matrix4::Translation(d);
	mMatrices.push_back(matrix);
	mTransform = matrix * mTransform;
}

void MatrixStack::PushRotationX(float radian)
{
	auto matrix = Matrix4::RotationX(radian);
	mMatrices.push_back(matrix);
	mTransform = matrix * mTransform;
}

void MatrixStack::PushRotationY(float radian)
{
	auto matrix = Matrix4::RotationY(radian);
	mMatrices.push_back(matrix);
	mTransform = matrix * mTransform;
}

void MatrixStack::PushRotationZ(float radian)
{
	auto matrix = Matrix4::RotationZ(radian);
	mMatrices.push_back(matrix);
	mTransform = matrix * mTransform;
}

void MatrixStack::PushScaling(Vector3 s)
{
	auto matrix = Matrix4::Scaling(s);
	mMatrices.push_back(matrix);
	mTransform = matrix * mTransform;
}

void MatrixStack::PopMatrix()
{
	if (!mMatrices.empty())
	{
		auto matrix = mMatrices.back();
		mMatrices.pop_back();
		mTransform = Inverse(matrix) * mTransform;
	}
}
