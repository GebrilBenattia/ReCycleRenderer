#pragma once

#include <Window.hpp>
#include <optional>

enum RENDERING_CONTEXT
{
	OPENGL,
	VULKAN,
	DIRECT3D11,
	DIRECT3D12
};

class RendererContext
{
private:

public:

	virtual void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt) = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};