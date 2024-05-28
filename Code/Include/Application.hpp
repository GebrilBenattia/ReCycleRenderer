#pragma once

#include "Renderer.hpp"

class Application
{
private:

public:

	Renderer* r;

	Application();
	~Application();

	void Init();
	void Update();
	void Shutdown();
};