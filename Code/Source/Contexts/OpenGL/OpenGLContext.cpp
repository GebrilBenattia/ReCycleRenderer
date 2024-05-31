#include "OpenGLContext.hpp"

OpenGLContext::OpenGLContext()
{
	Create();
}

OpenGLContext::OpenGLContext(const int _Width, const int _Height)
{
	Create(_Width, _Height);
}

OpenGLContext::~OpenGLContext()
{
	Destroy();
}

void OpenGLContext::Create(std::optional<const int> _Width, std::optional<const int> _Height)
{
	if (m_Window) {
		delete m_Window;
	}
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void OpenGLContext::Init()
{
}

void OpenGLContext::Update()
{
	while (!glfwWindowShouldClose(m_Window->window)) {
		glfwPollEvents();

	}
}

void OpenGLContext::Destroy()
{
	m_Window->Destroy();
}