#include <Window.hpp>
#include <stdexcept>
#include <glad/glad.h>

Window::Window(const RENDERING_CONTEXT& _ActiveContext, const int& _Width, const int& _Height)
	:m_Window(nullptr, glfwDestroyWindow) // Initializes with nullptr and custom deleter
{
	m_WindowAttributes.width = _Width;
	m_WindowAttributes.height = _Height;

	switch (_ActiveContext)
	{
	case OPENGL:
		m_WindowAttributes.title = "ReCycleRenderer - OpenGL";
		CreateForOpenGL();
		break;
	case VULKAN:
		m_WindowAttributes.title = "ReCycleRenderer - Vulkan";
		CreateForVulkan();
		break;
	case DIRECT3D11:
		m_WindowAttributes.title = "ReCycleRenderer - DirectX";
		CreateForDirectX();
		break;
	case DIRECT3D12:
		m_WindowAttributes.title = "ReCycleRenderer - DirectX";
		CreateForDirectX();
		break;
	default:
		break;
	}
}

void Window::CreateForOpenGL()
{
	// Initializes the GLFW library to manage windows and input events.
	glfwInit();

	// Requests an OpenGL context with major version 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

	// Requests an OpenGL context with minor version 6.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Requests a core profile for OpenGL to avoid deprecated features.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Takes ownership of the newly created GLFW window and ensure any previously managed window is destroyed.
	m_Window.reset(glfwCreateWindow(m_WindowAttributes.width, m_WindowAttributes.height, m_WindowAttributes.title.c_str(), nullptr, nullptr));
	if (!m_Window) {
		throw std::runtime_error("failed to create OpenGL window");
		glfwTerminate();
	}

	// Makes the newly created window's context current for OpenGL rendering commands.
	glfwMakeContextCurrent(m_Window.get());

	glfwSetFramebufferSizeCallback(m_Window.get(), FramebufferResizeCallback);
}

void Window::CreateForVulkan()
{
	// Initializes the GLFW library to manage windows and input events.
	glfwInit();

	// Specifies that no OpenGL or OpenGL ES context should be created for this window.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Takes ownership of the newly created GLFW window and ensure any previously managed window is destroyed.
	m_Window.reset(glfwCreateWindow(m_WindowAttributes.width, m_WindowAttributes.height, m_WindowAttributes.title.c_str(), nullptr, nullptr));
	if (!m_Window) {
		throw std::runtime_error("failed to create Vulkan window");
		glfwTerminate();
	}
}

void Window::CreateForDirectX()
{
	// Initializes the GLFW library to manage windows and input events.
	glfwInit();

	// Specifies that no OpenGL or OpenGL ES context should be created for this window.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Takes ownership of the newly created GLFW window and ensure any previously managed window is destroyed.
	m_Window.reset(glfwCreateWindow(m_WindowAttributes.width, m_WindowAttributes.height, m_WindowAttributes.title.c_str(), nullptr, nullptr));
	if (!m_Window) {
		throw std::runtime_error("failed to create DirectX window");
		glfwTerminate();
	}
}

void Window::FramebufferResizeCallback(GLFWwindow* _Window, int _Width, int _Height)
{
	glViewport(0, 0, _Width, _Height);
}

void Window::Destroy()
{
	// Terminates GLFW and release any resources allocated by the library.
	glfwTerminate();
}