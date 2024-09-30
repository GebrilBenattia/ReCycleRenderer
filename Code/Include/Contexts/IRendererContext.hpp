#pragma once

enum RENDERING_CONTEXT
{
	OPENGL,
	VULKAN,
	DIRECT3D11,
	DIRECT3D12
};

class IRendererContext
{
private:

public:

	// Initializes the Graphics API context
	virtual void Init() = 0;

	// Destroys the Graphics API context (e.g. cleaning, destroying allocated stuff)
	virtual void Destroy() = 0;
};