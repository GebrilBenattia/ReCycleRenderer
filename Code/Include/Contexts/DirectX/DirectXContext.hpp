#pragma once

#include <RendererContext.hpp>

class DirectXContext : public RendererContext
{
private:

	static inline Window* m_Window = nullptr;

public:

	DirectXContext();
	DirectXContext(const int _Width, const int _Height);
	~DirectXContext();

	void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt) override;
	void Init() override;
	void Update() override;
	void Destroy() override;
};