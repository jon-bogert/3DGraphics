#include "Graphics.h"

#include "DepthBuffer.h"
#include "MaterialManager.h"
#include "Viewport.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

void Graphics::NewFrame()
{
	DepthBuffer::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
}