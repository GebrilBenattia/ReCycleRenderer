#pragma once

#define GLFW_INCLUDE_NONE //We have to make sure GLFW doesn't include OpenGL to fix this error : "glad.h(27,1): error C1189: #error: OpenGL header already included, remove this include, glad already provides it"
#include <GLFW/glfw3.h>

#ifdef APIENTRY
#undef APIENTRY	// #include <d3d11> and <d312> in Direct3D11Context and Direct3D12Context include a header that defines it, so to get rid of the warning when building undef it because GLFW defines it too, C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared\minwindef.h(130,1): warning C4005: 'APIENTRY': macro redefinition
#endif

class Window
{
private:

public:

	GLFWwindow* window = nullptr;

	int width, height;

	bool framebufferResized = false;

	Window(const int _Width, const int _Height);

	void CreateForOpenGL();
	void CreateForVulkan();
	void CreateForDirectX();
	void Destroy();
};