#pragma once

#include <RendererContext.hpp>

class Renderer
{
private:

public:

	RENDERING_CONTEXT activeContext = RENDERING_CONTEXT::VULKAN;

	RendererContext* context = nullptr;

	void Init();
	void Update();
    void Cleanup();
};