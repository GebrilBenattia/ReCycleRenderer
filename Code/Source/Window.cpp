#include "Window.hpp"
#include <Renderer.hpp>
#include <stdexcept>

Window::Window(const int _Width, const int _Height)
	:width(_Width), height(_Height)
{
	switch (Renderer::activeContext)
	{
	case OPENGL:
		CreateForOpenGL();
		break;
	case VULKAN:
		CreateForVulkan();
		break;
	case DIRECT3D11:
		CreateForDirectX();
		break;
	case DIRECT3D12:
		CreateForDirectX();
		break;
	default:
		break;
	}
}

void Window::CreateForOpenGL()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "ReCycleRenderer", nullptr, nullptr);
	if (!window) {
		throw std::runtime_error("failed to create OpenGL window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window); // It's used to associate the OpenGL context of a window with the current thread, allowing OpenGL rendering commands to be executed within that context.
}

void Window::CreateForVulkan()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(width, height, "ReCycleRenderer", nullptr, nullptr);
	if (!window) {
		throw std::runtime_error("failed to create Vulkan window");
		glfwTerminate();
	}
	glfwSetWindowUserPointer(window, this);
}

void Window::CreateForDirectX()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(width, height, "ReCycleRenderer", nullptr, nullptr);
	if (!window) {
		throw std::runtime_error("failed to create DirectX window");
		glfwTerminate();
	}
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}