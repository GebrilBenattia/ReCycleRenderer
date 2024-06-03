#include "OpenGLContext.hpp"
#include <glad/glad.h>

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
	gladLoadGL();

	glViewport(0, 0, m_Window->width, m_Window->height);
}

void OpenGLContext::Update()
{
	while (!glfwWindowShouldClose(m_Window->window)) {
		glfwPollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window->window);
	}
}

void OpenGLContext::Destroy()
{
	m_Window->Destroy();
}