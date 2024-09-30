#pragma once

#include <IRendererContext.hpp>
#include <glad/glad.h>
#include <memory>

#ifdef APIENTRY
#undef APIENTRY	// #include <glad/glad.h> include a header that defines it, so to get rid of the warning when building undef it because GLFW defines it too
#endif

class OpenGLContext : public IRendererContext
{
private:

public:

	OpenGLContext();
	~OpenGLContext();

	// Initializes the OpenGL API context
	void Init() override;

	// Destroys the OpenGL API context (e.g. cleaning, destroying allocated stuff)
	void Destroy() override;
};