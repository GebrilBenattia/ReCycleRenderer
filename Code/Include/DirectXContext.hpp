#pragma once

#include <RendererContext.hpp>

class DirectXContext : public RendererContext
{
private:

	static Window* m_Window;

public:

	DirectXContext();
	DirectXContext(const int _Width, const int _Height);
	~DirectXContext();

	void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt) override;
	void InitDirectX();
	void Update() override;
	void Destroy() override;
};