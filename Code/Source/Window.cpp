#include "Window.hpp"
#include <Renderer.hpp>

Window::Window(const int _Width, const int _Height)
	:width(_Width), height(_Height)
{
	Create();
}

void Window::Create()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(width, height, "ReCycleRenderer", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto renderer = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	renderer->framebufferResized = true;
}