#pragma once

#include <RendererContext.hpp>
#include <d3d12.h>

class Direct3D12Context : public RendererContext
{
private:

	Window* m_Window = nullptr;

public:

	Direct3D12Context();
	Direct3D12Context(const int& _Width, const int& _Height);
	~Direct3D12Context();

	void Create(const std::optional<const int>& _Width = std::nullopt, const std::optional<const int>& _Height = std::nullopt) override;
	void Init() override;
	void Update() override;
	void Destroy() override;
};