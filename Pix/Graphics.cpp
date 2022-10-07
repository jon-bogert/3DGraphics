#include "Graphics.h"

#include "Camera.h"
#include "Clipper.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "MatrixStack.h"
#include "PrimitiveManager.h"
#include "RayTracer.h"
#include "Viewport.h"

void Graphics::NewFrame()
{
	Camera::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	DepthBuffer::Get()->OnNewFrame();
	LightManager::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	PrimitiveManager::Get()->OnNewFrame();
	RayTracer::Get()->OnNewFrame();
	Viewport::Get()->OnNewFrame();
}