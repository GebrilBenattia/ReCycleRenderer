#pragma once

#define GLFW_INCLUDE_NONE //We have to make sure GLFW doesn't include OpenGL to fix this error : "glad.h(27,1): error C1189: #error: OpenGL header already included, remove this include, glad already provides it"
#include <GLFW/glfw3.h>

#ifdef APIENTRY
#undef APIENTRY	// #include <d3d11> and <d312> in Direct3D11Context and Direct3D12Context include a header that defines it, so to get rid of the warning when building undef it because GLFW defines it too, C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\minwindef.h(130,1): warning C4005: 'APIENTRY': macro redefinition
#endif

#include <IRendererContext.hpp>

#include <string>
#include <memory>

struct WindowAttributes
{
	std::string title;
	int width = 0;
	int height = 0;
	bool framebufferResized = false;
};

class Window
{
private:

	// Unique pointer with custom deleter
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> m_Window;
	WindowAttributes m_WindowAttributes;

public:

	Window(const RENDERING_CONTEXT& _ActiveContext, const int& _Width, const int& _Height);

	// Creates a window that complies with OpenGL requirements
	void CreateForOpenGL();

	// Creates a window that complies with Vulkan requirements
	void CreateForVulkan();

	// Creates a window that complies with DirectX requirements.
	void CreateForDirectX();

	// Called each time the window is supposed to resize
	static void FramebufferResizeCallback(GLFWwindow* _Window, int _Width, int _Height);
	
	// Terminates the GLFW context (window destruction is handled by the std::unique_ptr custom deleter) 
	void Destroy();

	// Adding const after the method to make it Read-Only so it does not modify any members of the class

	// Read-Only Method that returns a GFLWwindow* which cannot be reassigned but its value can be modified
	[[nodiscard]] GLFWwindow* const GetWindow() const { return m_Window.get(); }

	// Read-Only Method that returns const WindowAttributes (e.g. holding title, width, height, etc...)
	[[nodiscard]] const WindowAttributes& GetWindowAttributes() const { return m_WindowAttributes; }
};