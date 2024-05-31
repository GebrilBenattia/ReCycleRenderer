#pragma once

#include <GLFW/glfw3.h>
#include <optional>

class Window
{
private:

public:

	GLFWwindow* window = nullptr;

	int width, height;

	bool framebufferResized = false;

	Window(const int _Width, const int _Height);

	void Create();
	void Destroy();

	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
};