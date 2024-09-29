#include <OpenGLContext.hpp>
#include <glad/glad.h>
#include <stdexcept>
#include <InputManager.hpp>

OpenGLContext::OpenGLContext()
{
	Create();
}

OpenGLContext::OpenGLContext(const int& _Width, const int& _Height)
{
	Create(_Width, _Height);
}

OpenGLContext::~OpenGLContext()
{
	Destroy();
}

void OpenGLContext::Create(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
	if (m_Window) {
		delete m_Window;
	}
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void OpenGLContext::Init()
{
	// Retrieving OpenGL functions pointers based on GLFW provided context
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0, 0, m_Window->width, m_Window->height);
}

void OpenGLContext::Update()
{
	InputManager inputManager(m_Window->window);

	// Loop until GLFW has been instructed to close
	while (!glfwWindowShouldClose(m_Window->window)) {
		// Checks if any event has been triggered (keyboard inputs, mouse events), update the window state and calls the corresponding functions (callbacks)
		glfwPollEvents();

		inputManager.HandleInput();

		// Clear color of the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clear the color buffer every frame
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the back color buffer of the window to the front and shows it as output
		glfwSwapBuffers(m_Window->window);
	}
}

void OpenGLContext::Destroy()
{
	m_Window->Destroy();
}