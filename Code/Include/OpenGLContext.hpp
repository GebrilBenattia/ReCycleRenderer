#pragma once

#include <RendererContext.hpp>

class OpenGLContext : public RendererContext
{
private:

	static Window* m_Window;

public:

	OpenGLContext();
	OpenGLContext(const int _Width, const int _Height);
	~OpenGLContext();

	void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt) override;
	void InitOpenGL();
	void Update() override;
	void Destroy() override;
};