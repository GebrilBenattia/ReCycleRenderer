#pragma once

#include <RendererContext.hpp>

class Renderer
{
private:

public:

	static inline RENDERING_CONTEXT activeContext = RENDERING_CONTEXT::VULKAN;

	static inline RendererContext* context = nullptr;

	void SelectActiveContext();
	void CreateActiveContext();
	void Init();
	
	void Update();
};