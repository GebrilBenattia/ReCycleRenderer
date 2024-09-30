#include <Window.hpp>
#include <Renderer.hpp>
#include <stdexcept>

Window::Window(const RENDERING_CONTEXT& _ActiveContext, const int& _Width, const int& _Height)
	:width(_Width), height(_Height), window(nullptr, glfwDestroyWindow) // Initializes with nullptr and custom deleter
{
	switch (_ActiveContext)
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
	// Initializes the GLFW library to manage windows and input events.
	glfwInit();

	// Requests an OpenGL context with major version 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

	// Requests an OpenGL context with minor version 6.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Requests a core profile for OpenGL to avoid deprecated features.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Takes ownership of the newly created GLFW window and ensure any previously managed window is destroyed.
	window.reset(glfwCreateWindow(width, height, "ReCycleRenderer - OpenGL", nullptr, nullptr));
	if (!window) {
		throw std::runtime_error("failed to create OpenGL window");
		glfwTerminate();
	}

	// Makes the newly created window's context current for OpenGL rendering commands.
	glfwMakeContextCurrent(window.get());
}

void Window::CreateForVulkan()
{
	// Initializes the GLFW library to manage windows and input events.
	glfwInit();

	// Specifies that no OpenGL or OpenGL ES context should be created for this window.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Takes ownership of the newly created GLFW window and ensure any previously managed window is destroyed.
	window.reset(glfwCreateWindow(width, height, "ReCycleRenderer - Vulkan", nullptr, nullptr));
	if (!window) {
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
	window.reset(glfwCreateWindow(width, height, "ReCycleRenderer - DirectX", nullptr, nullptr));
	if (!window) {
		throw std::runtime_error("failed to create DirectX window");
		glfwTerminate();
	}
}

void Window::Destroy()
{
	// Terminates GLFW and release any resources allocated by the library.
	glfwTerminate();
}