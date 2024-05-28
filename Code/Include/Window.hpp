#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:

public:

	GLFWwindow* window = nullptr;

	int width, height;

	Window();
	Window(const int _Width, const int _Height);

	void Create();
	void Destroy();
};

