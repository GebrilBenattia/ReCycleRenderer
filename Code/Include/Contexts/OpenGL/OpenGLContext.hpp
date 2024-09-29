#pragma once

#include <RendererContext.hpp>
#include <glad/glad.h>

#ifdef APIENTRY
#undef APIENTRY	// #include <glad/glad.h> include a header that defines it, so to get rid of the warning when building undef it because GLFW defines it too
#endif

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