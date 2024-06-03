#pragma once

#include <RendererContext.hpp>
#include <RHI.hpp>

class Renderer
{
private:

public:

	static inline RENDERING_CONTEXT activeContext = RENDERING_CONTEXT::VULKAN; //TODO MOVE IN APPLICATION (THE APP JOB TO KNOW WHICH API TO CHOOSE NOT THE RENDERER) AND ADD A POINTER TO THE APP HERE

	static inline RendererContext* context = nullptr;
	static inline RHI* rhi = nullptr;

	void SelectActiveContext();
	void CreateActiveContext();
	void Init();
	
	void Update();
};