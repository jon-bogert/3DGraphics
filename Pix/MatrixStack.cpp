#include "MatrixStack.h"
#include "MathHelper.h"

MatrixStack* MatrixStack::Get()
{
    static MatrixStack instance;
    return &instance;
}

void MatrixStack::OnNewFrame()
{
    mMatrices.clear();
    mCombinedTransfrom = Matrix4::Identity();
}

void MatrixStack::PushTranslation(const Vector3 d)
{
    Matrix4 newMatix = Matrix4::Translation(d);
    mMatrices.push_back(newMatix);
    mCombinedTransfrom = newMatix * mCombinedTransfrom;
}

void MatrixStack::PushRotationX(const float rad)
{
    Matrix4 newMatix = Matrix4::RotationX(rad);
    mMatrices.push_back(newMatix);
    mCombinedTransfrom = newMatix * mCombinedTransfrom;
}

void MatrixStack::PushRotationY(const float rad)
{
    Matrix4 newMatix = Matrix4::RotationY(rad);
    mMatrices.push_back(newMatix);
    mCombinedTransfrom = newMatix * mCombinedTransfrom;
}

void MatrixStack::PushRotationZ(const float rad)
{
    Matrix4 newMatix = Matrix4::RotationZ(rad);
    mMatrices.push_back(newMatix);
    mCombinedTransfrom = newMatix * mCombinedTransfrom;
}

void MatrixStack::PushScaling(const Vector3 s)
{
    Matrix4 newMatix = Matrix4::Scaling(s);
    mMatrices.push_back(newMatix);
    mCombinedTransfrom = newMatix * mCombinedTransfrom;
}

void MatrixStack::PopMatrix()
{
    Matrix4 last = mMatrices.back();
    mMatrices.pop_back();
    mCombinedTransfrom = MathHelper::Inverse(last) * mCombinedTransfrom;
}

void MatrixStack::GenerateCombinedMatrix()
{
    mCombinedTransfrom = Matrix4::Identity();
    for (Matrix4 m : mMatrices)
    {
        mCombinedTransfrom = m * mCombinedTransfrom;
    }
}
