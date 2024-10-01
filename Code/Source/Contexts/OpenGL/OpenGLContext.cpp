#include <OpenGLContext.hpp>
#include <GLFW/glfw3.h>
#include <stdexcept>

OpenGLContext::OpenGLContext()
{
	Init();
}

OpenGLContext::~OpenGLContext()
{
	Destroy();
}

void OpenGLContext::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0, 0, 900, 700);
}

void OpenGLContext::Destroy()
{
}