#include "Graphics.h"

#include "DepthBuffer.h"
#include "MaterialManager.h"
#include "Viewport.h"
#include "Clipper.h"

void Graphics::NewFrame()
{
	DepthBuffer::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
}