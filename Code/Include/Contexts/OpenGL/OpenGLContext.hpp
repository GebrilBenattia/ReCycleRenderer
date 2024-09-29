#pragma once

#include <RendererContext.hpp>

class OpenGLContext : public RendererContext
{
private:

	Window* m_Window = nullptr;

public:

	OpenGLContext();
	OpenGLContext(const int& _Width, const int& _Height);
	~OpenGLContext();

	void Create(const std::optional<const int>& _Width = std::nullopt, const std::optional<const int>& _Height = std::nullopt) override;
	void Init() override;
	void Update() override;
	void Destroy() override;
};