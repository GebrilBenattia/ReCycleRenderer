#include "Window.hpp"

Window::Window()
	:width(600), height(600)
{
	Create();
}

Window::Window(const int _Width, const int _Height)
	:width(_Width), height(_Height)
{
	Create();
}

void Window::Create()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "ReCycleRenderer", nullptr, nullptr);
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}