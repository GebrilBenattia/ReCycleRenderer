#pragma once

#include <RendererContext.hpp>
#include <d3d11.h>

#ifdef max
#undef max // causes a redefinition error in Renderer.cpp because it's defined in a header that <d3d11> include 
#endif

class Direct3D11Context : public RendererContext
{
private:

	Window* m_Window = nullptr;

public:

	Direct3D11Context();
	Direct3D11Context(const int& _Width, const int& _Height);
	~Direct3D11Context();

	void Create(const std::optional<const int>& _Width = std::nullopt, const std::optional<const int>& _Height = std::nullopt) override;
	void Init() override;
	void Update() override;
	void Destroy() override;
};