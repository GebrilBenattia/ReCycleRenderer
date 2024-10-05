#include <OpenGLRHI.hpp>
#include <glad/glad.h>
#include <iostream>

void OpenGLRHI::Update()
{
	// TODO : Create a .lib for glad to remove glad.c from the included files
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}